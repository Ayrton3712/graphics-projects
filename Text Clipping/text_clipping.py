import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.textpath import TextPath
from matplotlib.patches import PathPatch, Rectangle
from matplotlib.font_manager import FontProperties
from matplotlib.path import Path as MPath
from matplotlib.transforms import Bbox

TEXT = "UPTP"
SIZE = 1.4
TEXT_X, TEXT_Y = 1.2, 0.9
GAP_RATIO = 0.07

def build_char_paths(text, x, y, size):
    fp = FontProperties()
    result = []
    cx = x
    for ch in text:
        tp = TextPath((cx, y), ch, size=size, prop=fp)
        ext = tp.get_extents()
        result.append((ch, tp, ext))
        cx += ext.width + size * GAP_RATIO
    return result

def compute_window(chars):
    """Clip window where 40% of the first and last chars overflow each boundary."""
    widths = [ext.width for _, _, ext in chars]
    max_h = max(ext.height for _, _, ext in chars)
    first_ext = chars[0][2]
    last_ext = chars[-1][2]
    min_y = min(ext.y0 for _, _, ext in chars)

    wx0 = first_ext.x0 + widths[0] * 0.40
    wx1 = last_ext.x1 - widths[-1] * 0.40
    wy0 = min_y - SIZE * 0.10
    wy1 = min_y + max_h + SIZE * 0.20
    return wx0, wy0, wx1, wy1

def classify(ext, win):
    wx0, wy0, wx1, wy1 = win
    if ext.x0 >= wx0 and ext.y0 >= wy0 and ext.x1 <= wx1 and ext.y1 <= wy1:
        return "inside"
    if ext.x0 >= wx1 or ext.x1 <= wx0 or ext.y0 >= wy1 or ext.y1 <= wy0:
        return "outside"
    return "overlap"

def draw_window(ax, win):
    x0, y0, x1, y1 = win
    ax.add_patch(Rectangle(
        (x0, y0), x1 - x0, y1 - y0,
        linewidth=2, edgecolor="#0044BB", facecolor="#DDEEFF", alpha=0.40, zorder=0
    ))
    ax.text(x0, y1 + 0.08, "Clip Window",
            color="#0044BB", fontsize=8, va="bottom", fontweight="bold")

def make_clip_mpath(win):
    x0, y0, x1, y1 = win
    verts = [(x0, y0), (x1, y0), (x1, y1), (x0, y1), (x0, y0)]
    codes = [MPath.MOVETO, MPath.LINETO, MPath.LINETO, MPath.LINETO, MPath.CLOSEPOLY]
    return MPath(verts, codes)

def draw_rejected_char(ax, tp, ext):
    ax.add_patch(PathPatch(tp, facecolor="#FFAAAA", edgecolor="none", alpha=0.35))
    ax.add_patch(Rectangle(
        (ext.x0, ext.y0), ext.width, ext.height,
        linewidth=1.2, edgecolor="#CC2200", facecolor="none", linestyle="--"
    ))

def method1(ax, chars, win):
    draw_window(ax, win)
    whole = Bbox.union([ext for _, _, ext in chars])
    status = classify(whole, win)

    if status == "inside":
        for _, tp, _ in chars:
            ax.add_patch(PathPatch(tp, facecolor="black", edgecolor="none"))
    else:
        for _, tp, ext in chars:
            ax.add_patch(PathPatch(tp, facecolor="#FFAAAA", edgecolor="none", alpha=0.35))
        ax.add_patch(Rectangle(
            (whole.x0, whole.y0), whole.width, whole.height,
            linewidth=1.5, edgecolor="#CC2200", facecolor="none", linestyle="--"
        ))
        ax.text(
            (whole.x0 + whole.x1) / 2, whole.y0 - SIZE * 0.25,
            "Entire string rejected", ha="center", color="#CC2200", fontsize=7.5
        )

    ax.set_title("Method 1\nAll or None - String", fontsize=10, fontweight="bold", pad=12)

def method2(ax, chars, win):
    draw_window(ax, win)
    for _, tp, ext in chars:
        if classify(ext, win) == "inside":
            ax.add_patch(PathPatch(tp, facecolor="black", edgecolor="none"))
        else:
            draw_rejected_char(ax, tp, ext)

    ax.set_title("Method 2\nAll or None - Character", fontsize=10, fontweight="bold", pad=12)

def method3(ax, chars, win):
    draw_window(ax, win)
    clip = make_clip_mpath(win)
    for _, tp, ext in chars:
        if classify(ext, win) == "outside":
            continue
        patch = PathPatch(tp, facecolor="black", edgecolor="none")
        ax.add_patch(patch)
        patch.set_clip_path(clip, transform=ax.transData)

    ax.set_title("Method 3\nPartial Character Clipping", fontsize=10, fontweight="bold", pad=12)

def main():
    chars = build_char_paths(TEXT, TEXT_X, TEXT_Y, SIZE)
    win = compute_window(chars)

    all_exts = [ext for _, _, ext in chars]
    x_min = min(e.x0 for e in all_exts) - 0.4
    x_max = max(e.x1 for e in all_exts) + 0.4
    y_min = win[1] - 0.6
    y_max = win[3] + 0.8

    fig, axes = plt.subplots(1, 3, figsize=(16, 5))
    fig.suptitle('Text Clipping Methods', fontsize=13, fontweight="bold")

    for ax in axes:
        ax.set_xlim(x_min, x_max)
        ax.set_ylim(y_min, y_max)
        ax.set_aspect("equal")
        ax.axis("off")

    method1(axes[0], chars, win)
    method2(axes[1], chars, win)
    method3(axes[2], chars, win)

    plt.tight_layout(rect=[0, 0, 1, 0.93])
    plt.show()

if __name__ == "__main__":
    main()
