import numpy as np


def rotate(points, theta_degrees):
    """
    Rotate 2D points by theta degrees about the origin.
    Positive theta = counterclockwise, negative = clockwise.

    If a point's original angle with the x-axis is alpha,
    the new angle after rotation is alpha + theta.

    Rotation matrix:
        | cos(θ)  -sin(θ)  0 |
        | sin(θ)   cos(θ)  0 |
        |   0        0     1 |
    """
    theta = np.radians(theta_degrees)
    cos_t = np.cos(theta)
    sin_t = np.sin(theta)
    matrix = np.array([
        [cos_t, -sin_t, 0],
        [sin_t,  cos_t, 0],
        [0,      0,     1]
    ])
    result = []
    for x, y in points:
        p = matrix @ np.array([x, y, 1])
        result.append((float(p[0]), float(p[1])))
    return result
