def Bresenham(x1, y1, x2, y2):
    # Calculating slope
    m = (y2 - y1)/(x2 - x1)

    # Calculating initial decision parameter
    dy = y2 - y1
    dx = x2 - x1

    P_initial = (2 * dy) - dx

    # Defining parameters
    xi = x1
    yi = y1
    Pi = P_initial
    xi_next = x1
    yi_next = yi
    i = 0
    # Checking slope
    if (m < 1):
        while (xi_next != x2 and yi_next != y2):
            print(f"Iteration {i}: P = {Pi}, x_i = {xi}, y_i = {yi}, x_(i+1) = {xi_next}, y_(i+1) = {yi_next}")
            if Pi < 0:
                xi_next = xi_next + 1
                Pi = Pi + (2 * dy)
            else:
                xi_next = xi_next + 1
                yi_next = yi_next + 1
                Pi = Pi + (2 * dy) - (2 * dx)
            i += 1
    else:
        while (xi_next != x2 and yi_next != y2):
            print(f"Iteration {i}: P = {Pi}, x_i = {xi}, y_i = {yi}, x_(i+1) = {xi_next}, y_(i+1) = {yi_next}")
            if Pi < 0:
                yi_next = yi_next + 1
                Pi = Pi + (2 * dx)
            else:
                xi_next = xi_next + 1
                yi_next = yi_next + 1
                Pi = Pi + (2 * dx) - (2 * dy)
            i += 1

    print(f" Final Iteration: P = {Pi}, x_i = {xi}, y_i = {yi}, x_(i+1) = {xi_next}, y_(i+1) = {yi_next}")

    print(f"Final point: ({xi_next}, {yi_next})")

Bresenham(8, 5, 12, 8)