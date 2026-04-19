import numpy as np


def shear(points, shx, shy):
    """
    Apply 2D shearing using homogeneous coordinates.
    shx shears horizontally (x' = x + shx * y).
    shy shears vertically   (y' = y + shy * x).

    Shearing matrix:
        |  1   shx  0 |
        | shy   1   0 |
        |  0    0   1 |
    """
    matrix = np.array([
        [1,   shx, 0],
        [shy, 1,   0],
        [0,   0,   1]
    ])
    result = []
    for x, y in points:
        p = matrix @ np.array([x, y, 1])
        result.append((float(p[0]), float(p[1])))
    return result
