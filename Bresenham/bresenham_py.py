def Bresenham(x1, y1, x2, y2):
    # Calculating dy, dx, m, and initial decision parameter
    dy = y2 - y1
    dx = x2 - x1
    m = dy / dx
    P_initial = (2 * abs(dy)) - abs(dx)

    # Defining parameters
    xi = x1
    yi = y1
    Pi = P_initial
    xi_next = x1
    yi_next = yi
    i = 0

    # Defining direction variables
    sy = 1 if y1 < y2 else -1
    sx = 1 if x1 < x2 else -1
    
    # Checking slope
    if (abs(m) < 1):
        while (xi_next != x2 and yi_next != y2):
            # print(f"Iteration {i}: P = {Pi}, x_i = {xi}, y_i = {yi}, x_(i+1) = {xi_next}, y_(i+1) = {yi_next}")
            if Pi < 0:
                xi_next = xi_next + sx
                Pi = Pi + (2 * abs(dy))
            else:
                xi_next = xi_next + sx
                yi_next = yi_next + sy
                Pi = Pi + (2 * abs(dy)) - (2 * abs(dx))
            i += 1

            print(f"Next point: ({xi_next}, {yi_next})")
    else:
        while (xi_next != x2 and yi_next != y2):
            # print(f"Iteration {i}: P = {Pi}, x_i = {xi}, y_i = {yi}, x_(i+1) = {xi_next}, y_(i+1) = {yi_next}")
            if Pi < 0:
                yi_next = yi_next + sy
                Pi = Pi + (2 * abs(dx))
            else:
                xi_next = xi_next + sx
                yi_next = yi_next + sy
                Pi = Pi + (2 * abs(dx)) - (2 * abs(dy))
            i += 1
            print(f"Next point: ({xi_next}, {yi_next})")

    # print(f" Final Iteration: P = {Pi}, x_i = {xi}, y_i = {yi}, x_(i+1) = {xi_next}, y_(i+1) = {yi_next}")

    print(f"Final point: ({xi_next}, {yi_next})")

Bresenham(0, 3, 4, 0)