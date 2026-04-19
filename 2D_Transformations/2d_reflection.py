import numpy as np


def reflect_x(points):
    """
    Reflect across the x-axis: y' = -y.

    Reflection matrix:
        | 1   0  0 |
        | 0  -1  0 |
        | 0   0  1 |
    """
    matrix = np.array([
        [1,  0, 0],
        [0, -1, 0],
        [0,  0, 1]
    ])
    result = []
    for x, y in points:
        p = matrix @ np.array([x, y, 1])
        result.append((float(p[0]), float(p[1])))
    return result


def reflect_y(points):
    """
    Reflect across the y-axis: x' = -x.

    Reflection matrix:
        | -1  0  0 |
        |  0  1  0 |
        |  0  0  1 |
    """
    matrix = np.array([
        [-1, 0, 0],
        [0,  1, 0],
        [0,  0, 1]
    ])
    result = []
    for x, y in points:
        p = matrix @ np.array([x, y, 1])
        result.append((float(p[0]), float(p[1])))
    return result
