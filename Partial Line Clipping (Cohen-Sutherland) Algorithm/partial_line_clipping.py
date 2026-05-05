import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import seaborn as sns

# 4-bit outcode constants
INSIDE = 0  # 0000
LEFT   = 1  # 0001
RIGHT  = 2  # 0010
BOTTOM = 4  # 0100
TOP    = 8  # 1000


def compute_region_code(x, y, xmin, xmax, ymin, ymax):
    code = INSIDE
    if x < xmin:
        code |= LEFT
    elif x > xmax:
        code |= RIGHT
    if y < ymin:
        code |= BOTTOM
    elif y > ymax:
        code |= TOP
    return code


def cohen_sutherland_clip(x1, y1, x2, y2, xmin, xmax, ymin, ymax):
    x1, y1, x2, y2 = float(x1), float(y1), float(x2), float(y2)
    code1 = compute_region_code(x1, y1, xmin, xmax, ymin, ymax)
    code2 = compute_region_code(x2, y2, xmin, xmax, ymin, ymax)

    while True:
        if not (code1 | code2):        # trivially accept: both inside
            return (x1, y1, x2, y2)
        if code1 & code2:              # trivially reject: same outside region
            return None

        outside_code = code1 if code1 else code2
        dx = np.float64(x2 - x1)
        dy = np.float64(y2 - y1)

        if outside_code & TOP:
            x = x1 + dx * (ymax - y1) / dy
            y = float(ymax)
        elif outside_code & BOTTOM:
            x = x1 + dx * (ymin - y1) / dy
            y = float(ymin)
        elif outside_code & RIGHT:
            y = y1 + dy * (xmax - x1) / dx
            x = float(xmax)
        else:                           # LEFT
            y = y1 + dy * (xmin - x1) / dx
            x = float(xmin)

        if outside_code == code1:
            x1, y1 = float(x), float(y)
            code1 = compute_region_code(x1, y1, xmin, xmax, ymin, ymax)
        else:
            x2, y2 = float(x), float(y)
            code2 = compute_region_code(x2, y2, xmin, xmax, ymin, ymax)


def _window_patch(ax, xmin, xmax, ymin, ymax, labeled=True):
    ax.add_patch(patches.Rectangle(
        (xmin, ymin), xmax - xmin, ymax - ymin,
        linewidth=2, edgecolor="#1f77b4", facecolor="none",
        linestyle="--", label="Clipping window" if labeled else "_nolegend_",
        zorder=3,
    ))


def plot_clipping(lines, xmin, xmax, ymin, ymax):
    sns.set_theme(style="whitegrid")

    results = [
        cohen_sutherland_clip(x1, y1, x2, y2, xmin, xmax, ymin, ymax)
        for x1, y1, x2, y2 in lines
    ]

    def categorize(orig, result):
        if result is None:
            return "rejected"
        return "accepted" if np.allclose(orig, result, atol=1e-6) else "clipped"

    categories = [categorize(row, res) for row, res in zip(lines, results)]

    color_map = {"accepted": "#2ca02c", "clipped": "#ff7f0e", "rejected": "#d62728"}
    label_map = {"accepted": "Fully inside", "clipped": "Partially clipped", "rejected": "Fully outside"}

    fig, (ax_before, ax_after) = plt.subplots(1, 2, figsize=(12, 6))

    # --- Before Clipping ---
    seen = set()
    for (x1, y1, x2, y2), cat in zip(lines, categories):
        color = color_map[cat]
        lbl = label_map[cat] if cat not in seen else "_nolegend_"
        seen.add(cat)
        ax_before.plot([x1, x2], [y1, y2], color=color, linewidth=2, label=lbl, zorder=2)
        ax_before.plot([x1, x2], [y1, y2], "o", color=color, markersize=5, zorder=2)

    _window_patch(ax_before, xmin, xmax, ymin, ymax)
    ax_before.set(xlim=(-5, 105), ylim=(-5, 105), aspect="equal",
                  xlabel="x", ylabel="y", title="Before Clipping")
    ax_before.title.set(fontsize=14, fontweight="bold")
    ax_before.legend(loc="upper left")

    # --- After Clipping ---
    seen = set()
    for (x1, y1, x2, y2), result, cat in zip(lines, results, categories):
        if result is None:
            continue
        rx1, ry1, rx2, ry2 = result
        color = color_map[cat]
        lbl = label_map[cat] if cat not in seen else "_nolegend_"
        seen.add(cat)
        ax_after.plot([rx1, rx2], [ry1, ry2], color=color, linewidth=2, label=lbl, zorder=2)
        ax_after.plot([rx1, rx2], [ry1, ry2], "o", color=color, markersize=5, zorder=2)

    _window_patch(ax_after, xmin, xmax, ymin, ymax)
    ax_after.set(xlim=(-5, 105), ylim=(-5, 105), aspect="equal",
                 xlabel="x", ylabel="y", title="After Clipping")
    ax_after.title.set(fontsize=14, fontweight="bold")
    ax_after.legend(loc="upper left")

    fig.suptitle("Partial Line Clipping", fontsize=16, fontweight="bold")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    xmin, xmax, ymin, ymax = 20, 80, 20, 80

    lines = np.array([
        [ 30,  40,  70,  60],   # fully inside
        [  0,  50,  60,  50],   # crosses left boundary
        [ 50,  70, 100,  30],   # crosses right boundary
        [ 40,  10,  60,  90],   # crosses both bottom and top
        [-10,  30,  10,  70],   # fully outside (left region, trivially rejected)
        [  0,   0, 100, 100],   # diagonal clipped on both ends
    ], dtype=float)

    plot_clipping(lines, xmin, xmax, ymin, ymax)

