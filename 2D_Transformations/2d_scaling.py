import numpy as np


def scale(points, sx, sy):
    """
    Apply 2D scaling using homogeneous coordinates.

    Scaling matrix:
        | sx  0   0 |
        | 0   sy  0 |
        | 0   0   1 |
    """
    matrix = np.array([
        [sx, 0,  0],
        [0,  sy, 0],
        [0,  0,  1]
    ])
    result = []
    for x, y in points:
        p = matrix @ np.array([x, y, 1])
        result.append((float(p[0]), float(p[1])))
    return result
