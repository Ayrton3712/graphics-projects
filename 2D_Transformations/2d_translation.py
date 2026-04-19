import numpy as np


def translate(points, tx, ty):
    """
    Apply 2D translation using homogeneous coordinates.

    Translation matrix:
        | 1  0  tx |
        | 0  1  ty |
        | 0  0   1 |
    """
    matrix = np.array([
        [1, 0, tx],
        [0, 1, ty],
        [0, 0,  1]
    ])
    result = []
    for x, y in points:
        p = matrix @ np.array([x, y, 1])
        result.append((float(p[0]), float(p[1])))
    return result
