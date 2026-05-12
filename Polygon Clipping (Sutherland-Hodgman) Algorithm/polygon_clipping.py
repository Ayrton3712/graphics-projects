import matplotlib.pyplot as plt
from matplotlib.patches import Polygon as MplPolygon

def inside(point, edge_start, edge_end):
    x1, y1 = edge_start
    x2, y2 = edge_end
    px, py = point
    return (x2 - x1) * (py - y1) - (y2 - y1) * (px - x1) < 0

def intersection(s, e, edge_start, edge_end):
    x1, y1 = edge_start
    x2, y2 = edge_end
    x3, y3 = s
    x4, y4 = e

    denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)

    t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom
    x = x1 + t * (x2 - x1)
    y = y1 + t * (y2 - y1)
    return (x, y)

def sutherland_hodgman(subject_polygon, clip_polygon):
    output = list(subject_polygon)

    for i in range(len(clip_polygon)):
        if not output:
            break

        edge_start = clip_polygon[i]
        edge_end = clip_polygon[(i + 1) % len(clip_polygon)]
        input_list = output
        output = []

        for j in range(len(input_list)):
            s = input_list[j - 1]
            e = input_list[j]

            if inside(e, edge_start, edge_end):
                if not inside(s, edge_start, edge_end):
                    output.append(intersection(s, e, edge_start, edge_end))
                output.append(e)
            elif inside(s, edge_start, edge_end):
                output.append(intersection(s, e, edge_start, edge_end))

    return output

def plot_polygons(subject, clip_window, clipped):
    fig, ax = plt.subplots(figsize=(8, 7))
    ax.set_title("Polygon Clipping (Sutherland-Hodgman) algorithm", fontsize=14)
    ax.set_aspect("equal")

    def closed(pts):
        return list(pts) + [pts[0]]

    subj_xs, subj_ys = zip(*closed(subject))
    clip_xs, clip_ys = zip(*closed(clip_window))

    ax.plot(subj_xs, subj_ys, "b--", linewidth=1.5, label="Subject polygon")
    ax.plot(clip_xs, clip_ys, "r--", linewidth=1.5, label="Clip window")

    if clipped:
        clipped_patch = MplPolygon(
            clipped, closed=True, facecolor="green",
            edgecolor="darkgreen", linewidth=2, alpha=0.5,
            label="Clipped polygon"
        )
        ax.add_patch(clipped_patch)

        for px, py in clipped:
            ax.annotate(f"({px:.1f}, {py:.1f})", (px, py),
                        textcoords="offset points", xytext=(5, 5), fontsize=8)

    ax.legend(loc="upper right")
    ax.margins(0.15)
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    subject_polygon = [(130, 150), (175, 210), (225, 175), (210, 160)]
    clip_window = [(150, 150), (150, 200), (200, 200), (200, 150)]

    clipped = sutherland_hodgman(subject_polygon, clip_window)

    print("Clipped polygon vertices:")
    for v in clipped:
        print(f"  ({v[0]:.4f}, {v[1]:.4f})")

    plot_polygons(subject_polygon, clip_window, clipped)