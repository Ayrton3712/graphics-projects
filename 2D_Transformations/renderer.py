import pygame
import importlib
import sys
import os
import math

# ---------------------------------------------------------------------------
# Import transformation modules (names start with a digit, so use importlib)
# ---------------------------------------------------------------------------
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
translation_mod = importlib.import_module("2d_translation")
rotation_mod = importlib.import_module("2d_rotation")
scaling_mod = importlib.import_module("2d_scaling")
reflection_mod = importlib.import_module("2d_reflection")
shearing_mod = importlib.import_module("2d_shearing")

# ---------------------------------------------------------------------------
# Window & layout
# ---------------------------------------------------------------------------
WIDTH, HEIGHT = 1000, 750
FPS = 60

TOP_H = 55
CTRL_Y = TOP_H
CTRL_H = 70
DRAW_Y = CTRL_Y + CTRL_H        # 125
DRAW_H = 515
BOT_Y = DRAW_Y + DRAW_H         # 640
BOT_H = HEIGHT - BOT_Y          # 110

ORIGIN_X = WIDTH // 2
ORIGIN_Y = DRAW_Y + DRAW_H // 2
SCALE = 30                       # pixels per world unit

# ---------------------------------------------------------------------------
# Cold colour palette
# ---------------------------------------------------------------------------
C_BG       = (12, 16, 32)
C_PANEL    = (16, 22, 42)
C_GRID     = (22, 32, 55)
C_AXIS     = (65, 105, 145)
C_TEXT     = (175, 195, 215)
C_LABEL    = (140, 165, 190)
C_BTN      = (30, 58, 105)
C_BTN_HOV  = (42, 78, 135)
C_BTN_ACT  = (55, 110, 165)
C_BTN_TXT  = (195, 215, 235)
C_TRACK    = (22, 38, 65)
C_SLD_FILL = (40, 95, 125)
C_HANDLE   = (85, 170, 200)
C_ORIG     = (45, 85, 145, 90)
C_ORIG_LN  = (65, 115, 185)
C_TRANS    = (55, 170, 180, 100)
C_TRANS_LN = (85, 210, 220)
C_REFL_ON  = (45, 130, 120)
C_SEP      = (28, 40, 65)

# ---------------------------------------------------------------------------
# Coordinate helpers
# ---------------------------------------------------------------------------

def w2s(wx, wy):
    """World → screen."""
    return (int(ORIGIN_X + wx * SCALE), int(ORIGIN_Y - wy * SCALE))


def draw_poly_alpha(surf, colour, pts_world):
    """Draw a filled polygon with per-pixel alpha (world coords)."""
    if len(pts_world) < 3:
        return
    sp = [w2s(x, y) for x, y in pts_world]
    xs, ys = zip(*sp)
    mn_x, mx_x, mn_y, mx_y = min(xs), max(xs), min(ys), max(ys)
    w, h = mx_x - mn_x + 1, mx_y - mn_y + 1
    if w <= 0 or h <= 0:
        return
    tmp = pygame.Surface((w, h), pygame.SRCALPHA)
    pygame.draw.polygon(tmp, colour, [(x - mn_x, y - mn_y) for x, y in sp])
    surf.blit(tmp, (mn_x, mn_y))


def draw_poly_outline(surf, colour, pts_world, width=2):
    if len(pts_world) < 3:
        return
    pygame.draw.polygon(surf, colour, [w2s(x, y) for x, y in pts_world], width)


def draw_vertices(surf, colour, pts_world, font, show_coords=False):
    for x, y in pts_world:
        sx, sy = w2s(x, y)
        pygame.draw.circle(surf, colour, (sx, sy), 4)
        if show_coords:
            lbl = font.render(f"({x:.1f}, {y:.1f})", True, colour)
            surf.blit(lbl, (sx + 6, sy - 16))


# ---------------------------------------------------------------------------
# UI widgets
# ---------------------------------------------------------------------------

class Slider:
    def __init__(self, x, y, w, lo, hi, val, label, fmt=".1f"):
        self.x, self.y, self.w = x, y, w
        self.h = 8
        self.lo, self.hi, self.val = lo, hi, val
        self.label, self.fmt = label, fmt
        self.dragging = False

    # --- events ---
    def handle_event(self, ev):
        hx = self._hx()
        h_rect = pygame.Rect(hx - 8, self.y - 4, 16, self.h + 8)
        t_rect = pygame.Rect(self.x, self.y - 4, self.w, self.h + 8)
        if ev.type == pygame.MOUSEBUTTONDOWN and ev.button == 1:
            if h_rect.collidepoint(ev.pos) or t_rect.collidepoint(ev.pos):
                self.dragging = True
                self._set(ev.pos[0])
        elif ev.type == pygame.MOUSEBUTTONUP and ev.button == 1:
            self.dragging = False
        elif ev.type == pygame.MOUSEMOTION and self.dragging:
            self._set(ev.pos[0])

    def _set(self, mx):
        t = max(0.0, min(1.0, (mx - self.x) / self.w))
        self.val = self.lo + t * (self.hi - self.lo)
        # round to display precision
        prec = int(self.fmt[1]) if len(self.fmt) >= 3 else 1
        self.val = round(self.val, prec)

    def _hx(self):
        r = (self.hi - self.lo)
        t = (self.val - self.lo) / r if r else 0
        return int(self.x + t * self.w)

    def _zero_x(self):
        if self.lo >= 0:
            return self.x
        if self.hi <= 0:
            return self.x + self.w
        t = (0 - self.lo) / (self.hi - self.lo)
        return int(self.x + t * self.w)

    # --- draw ---
    def draw(self, surf, font):
        # label + value
        txt = font.render(f"{self.label}: {self.val:{self.fmt}}", True, C_LABEL)
        surf.blit(txt, (self.x, self.y - 20))
        # track
        pygame.draw.rect(surf, C_TRACK,
                         (self.x, self.y, self.w, self.h), border_radius=4)
        # fill from zero-point to handle
        hx = self._hx()
        zx = self._zero_x()
        fl, fr = min(hx, zx), max(hx, zx)
        if fr - fl > 0:
            pygame.draw.rect(surf, C_SLD_FILL,
                             (fl, self.y, fr - fl, self.h), border_radius=4)
        # handle
        pygame.draw.circle(surf, C_HANDLE, (hx, self.y + self.h // 2), 7)


class Button:
    def __init__(self, x, y, w, h, text):
        self.rect = pygame.Rect(x, y, w, h)
        self.text = text
        self.hovered = False
        self.active = False

    def handle_event(self, ev):
        if ev.type == pygame.MOUSEMOTION:
            self.hovered = self.rect.collidepoint(ev.pos)
        if (ev.type == pygame.MOUSEBUTTONDOWN and ev.button == 1
                and self.rect.collidepoint(ev.pos)):
            return True
        return False

    def draw(self, surf, font):
        c = C_BTN_ACT if self.active else (C_BTN_HOV if self.hovered else C_BTN)
        pygame.draw.rect(surf, c, self.rect, border_radius=6)
        ts = font.render(self.text, True, C_BTN_TXT)
        surf.blit(ts, ts.get_rect(center=self.rect.center))


class ToggleButton(Button):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.toggled = False

    def draw(self, surf, font):
        c = C_REFL_ON if self.toggled else (C_BTN_HOV if self.hovered else C_BTN)
        pygame.draw.rect(surf, c, self.rect, border_radius=6)
        ts = font.render(self.text, True, C_BTN_TXT)
        surf.blit(ts, ts.get_rect(center=self.rect.center))


# ---------------------------------------------------------------------------
# Grid / axes
# ---------------------------------------------------------------------------

def draw_grid_and_axes(surf, font):
    lw = -ORIGIN_X / SCALE
    rw = (WIDTH - ORIGIN_X) / SCALE
    tw = (ORIGIN_Y - DRAW_Y) / SCALE
    bw = -(DRAW_Y + DRAW_H - ORIGIN_Y) / SCALE

    # grid lines
    for xi in range(math.floor(lw), math.ceil(rw) + 1):
        sx = ORIGIN_X + xi * SCALE
        pygame.draw.line(surf, C_GRID, (sx, DRAW_Y), (sx, DRAW_Y + DRAW_H))
    for yi in range(math.floor(bw), math.ceil(tw) + 1):
        sy = ORIGIN_Y - yi * SCALE
        pygame.draw.line(surf, C_GRID, (0, sy), (WIDTH, sy))

    # axes
    pygame.draw.line(surf, C_AXIS, (0, ORIGIN_Y), (WIDTH, ORIGIN_Y), 2)
    pygame.draw.line(surf, C_AXIS, (ORIGIN_X, DRAW_Y), (ORIGIN_X, DRAW_Y + DRAW_H), 2)

    # arrowheads
    pygame.draw.polygon(surf, C_AXIS, [
        (WIDTH - 5, ORIGIN_Y),
        (WIDTH - 14, ORIGIN_Y - 5),
        (WIDTH - 14, ORIGIN_Y + 5)])
    pygame.draw.polygon(surf, C_AXIS, [
        (ORIGIN_X, DRAW_Y + 5),
        (ORIGIN_X - 5, DRAW_Y + 14),
        (ORIGIN_X + 5, DRAW_Y + 14)])

    # tick labels every 2 units
    step = 2
    for xi in range(math.ceil(lw / step) * step,
                    math.floor(rw / step) * step + 1, step):
        if xi == 0:
            continue
        sx = ORIGIN_X + xi * SCALE
        pygame.draw.line(surf, C_AXIS, (sx, ORIGIN_Y - 3), (sx, ORIGIN_Y + 3))
        lbl = font.render(str(xi), True, C_LABEL)
        surf.blit(lbl, (sx - lbl.get_width() // 2, ORIGIN_Y + 6))

    for yi in range(math.ceil(bw / step) * step,
                    math.floor(tw / step) * step + 1, step):
        if yi == 0:
            continue
        sy = ORIGIN_Y - yi * SCALE
        pygame.draw.line(surf, C_AXIS, (ORIGIN_X - 3, sy), (ORIGIN_X + 3, sy))
        lbl = font.render(str(yi), True, C_LABEL)
        surf.blit(lbl, (ORIGIN_X + 8, sy - lbl.get_height() // 2))

    # axis labels & origin
    surf.blit(font.render("x", True, C_AXIS), (WIDTH - 18, ORIGIN_Y + 10))
    surf.blit(font.render("y", True, C_AXIS), (ORIGIN_X + 12, DRAW_Y + 6))
    surf.blit(font.render("0", True, C_LABEL), (ORIGIN_X + 6, ORIGIN_Y + 6))


def draw_legend(surf, font):
    lx, ly = WIDTH - 170, DRAW_Y + DRAW_H - 50
    pygame.draw.rect(surf, C_ORIG_LN, (lx, ly, 14, 14))
    surf.blit(font.render("Original", True, C_TEXT), (lx + 20, ly))
    pygame.draw.rect(surf, C_TRANS_LN, (lx, ly + 20, 14, 14))
    surf.blit(font.render("Transformed", True, C_TEXT), (lx + 20, ly + 20))


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("2D Transformations")
    clock = pygame.time.Clock()

    font = pygame.font.Font(None, 22)
    font_sm = pygame.font.Font(None, 19)

    # ---- mode buttons (centred at top) ----
    modes = ["2D Translation", "2D Rotation", "2D Scaling",
             "2D Reflection", "2D Shearing"]
    bw, bh, bgap = 150, 35, 15
    bsx = (WIDTH - len(modes) * bw - (len(modes) - 1) * bgap) // 2
    mode_btns = [Button(bsx + i * (bw + bgap), 10, bw, bh, m)
                 for i, m in enumerate(modes)]
    cur_mode = 0
    mode_btns[0].active = True

    # ---- dimension sliders (bottom panel) ----
    sw = 350
    w_sl = Slider(80, BOT_Y + 50, sw, 1, 10, 4, "Width")
    h_sl = Slider(WIDTH - sw - 80, BOT_Y + 50, sw, 1, 10, 3, "Height")

    # ---- transformation-specific controls ----
    # translation
    tx_sl = Slider(80, CTRL_Y + 40, sw, -10, 10, 0, "Tx")
    ty_sl = Slider(WIDTH - sw - 80, CTRL_Y + 40, sw, -10, 10, 0, "Ty")
    # rotation
    th_sl = Slider((WIDTH - sw) // 2, CTRL_Y + 40, sw, -180, 180, 0,
                   "Theta (degrees)", ".0f")
    # scaling
    sx_sl = Slider(80, CTRL_Y + 40, sw, 0.1, 3, 1, "Sx", ".2f")
    sy_sl = Slider(WIDTH - sw - 80, CTRL_Y + 40, sw, 0.1, 3, 1, "Sy", ".2f")
    # reflection
    rbw_w = 200
    rbs = (WIDTH - 2 * rbw_w - 30) // 2
    rx_btn = ToggleButton(rbs, CTRL_Y + 20, rbw_w, 32, "Reflect across x-axis")
    ry_btn = ToggleButton(rbs + rbw_w + 30, CTRL_Y + 20, rbw_w, 32,
                          "Reflect across y-axis")
    # shearing
    shx_sl = Slider(80, CTRL_Y + 40, sw, -3, 3, 0, "Shx", ".2f")
    shy_sl = Slider(WIDTH - sw - 80, CTRL_Y + 40, sw, -3, 3, 0, "Shy", ".2f")

    ctrl_sliders = {
        0: [tx_sl, ty_sl],
        1: [th_sl],
        2: [sx_sl, sy_sl],
        3: [],          # reflection uses toggle buttons
        4: [shx_sl, shy_sl],
    }
    all_sliders = [tx_sl, ty_sl, th_sl, sx_sl, sy_sl, shx_sl, shy_sl]

    # ---- main loop ----
    running = True
    while running:
        for ev in pygame.event.get():
            if ev.type == pygame.QUIT:
                running = False
            if ev.type == pygame.KEYDOWN and ev.key == pygame.K_ESCAPE:
                running = False

            # mode buttons
            for i, btn in enumerate(mode_btns):
                if btn.handle_event(ev):
                    cur_mode = i
                    for b in mode_btns:
                        b.active = False
                    btn.active = True

            # dimension sliders (always active)
            w_sl.handle_event(ev)
            h_sl.handle_event(ev)

            # current mode's controls
            if cur_mode == 3:
                if rx_btn.handle_event(ev):
                    rx_btn.toggled = not rx_btn.toggled
                if ry_btn.handle_event(ev):
                    ry_btn.toggled = not ry_btn.toggled
            else:
                for s in ctrl_sliders.get(cur_mode, []):
                    s.handle_event(ev)

            # release all slider drags on mouse-up (prevents stuck state)
            if ev.type == pygame.MOUSEBUTTONUP and ev.button == 1:
                for s in all_sliders:
                    s.dragging = False

        # ---- compute transformation ----
        pts = [(0, 0), (w_sl.val, 0), (w_sl.val, h_sl.val), (0, h_sl.val)]

        if cur_mode == 0:
            tpts = translation_mod.translate(pts, tx_sl.val, ty_sl.val)
        elif cur_mode == 1:
            tpts = rotation_mod.rotate(pts, th_sl.val)
        elif cur_mode == 2:
            tpts = scaling_mod.scale(pts, sx_sl.val, sy_sl.val)
        elif cur_mode == 3:
            tpts = list(pts)
            if rx_btn.toggled:
                tpts = reflection_mod.reflect_x(tpts)
            if ry_btn.toggled:
                tpts = reflection_mod.reflect_y(tpts)
        else:
            tpts = shearing_mod.shear(pts, shx_sl.val, shy_sl.val)

        # ---- draw ----
        screen.fill(C_BG)

        # panels
        pygame.draw.rect(screen, C_PANEL, (0, 0, WIDTH, TOP_H))
        pygame.draw.rect(screen, C_PANEL, (0, CTRL_Y, WIDTH, CTRL_H))
        pygame.draw.line(screen, C_SEP, (0, TOP_H), (WIDTH, TOP_H))
        pygame.draw.rect(screen, C_PANEL, (0, BOT_Y, WIDTH, BOT_H))
        pygame.draw.line(screen, C_SEP, (0, DRAW_Y), (WIDTH, DRAW_Y))
        pygame.draw.line(screen, C_SEP, (0, BOT_Y), (WIDTH, BOT_Y))

        # drawing area (clipped)
        clip = pygame.Rect(0, DRAW_Y, WIDTH, DRAW_H)
        screen.set_clip(clip)

        draw_grid_and_axes(screen, font_sm)
        draw_poly_alpha(screen, C_ORIG, pts)
        draw_poly_outline(screen, C_ORIG_LN, pts)
        draw_vertices(screen, C_ORIG_LN, pts, font_sm)
        draw_poly_alpha(screen, C_TRANS, tpts)
        draw_poly_outline(screen, C_TRANS_LN, tpts)
        draw_vertices(screen, C_TRANS_LN, tpts, font_sm, show_coords=True)
        draw_legend(screen, font_sm)

        screen.set_clip(None)

        # mode buttons
        for btn in mode_btns:
            btn.draw(screen, font)

        # transformation controls
        if cur_mode == 3:
            rx_btn.draw(screen, font)
            ry_btn.draw(screen, font)
        else:
            for s in ctrl_sliders.get(cur_mode, []):
                s.draw(screen, font_sm)

        # dimension sliders
        dim_lbl = font.render("Rectangle Dimensions", True, C_TEXT)
        screen.blit(dim_lbl, ((WIDTH - dim_lbl.get_width()) // 2, BOT_Y + 8))
        w_sl.draw(screen, font_sm)
        h_sl.draw(screen, font_sm)

        # window title
        pygame.display.set_caption(f"2D Transformations \u2014 {modes[cur_mode]}")
        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()


if __name__ == "__main__":
    main()
