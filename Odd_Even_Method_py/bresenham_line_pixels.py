def bresenham_line(x1, y1, x2, y2):
    """
    Bresenham's line drawing algorithm.
    
    Args:
        x1, y1: Starting point coordinates
        x2, y2: Ending point coordinates
    
    Returns:
        List of tuples representing pixel coordinates along the line
    """
    pixels = []
    
    # Calculate differences
    dy = y2 - y1
    dx = x2 - x1
    
    # Handle division by zero
    if dx == 0:
        m = float('inf')
    else:
        m = dy / dx
    
    # Calculate initial decision parameter
    P_initial = (2 * abs(dy)) - abs(dx)
    
    # Direction variables
    sy = 1 if y1 < y2 else -1
    sx = 1 if x1 < x2 else -1
    
    xi = x1
    yi = y1
    Pi = P_initial
    
    pixels.append((xi, yi))  # Add starting point
    
    # Check slope to determine which axis to step along
    if abs(m) < 1 or dx == 0:  # |m| < 1, step along x-axis
        if dx == 0:  # Vertical line
            while yi != y2:
                yi += sy
                pixels.append((xi, yi))
        else:
            while xi != x2:
                if Pi < 0:
                    xi += sx
                    Pi = Pi + (2 * abs(dy))
                else:
                    xi += sx
                    yi += sy
                    Pi = Pi + (2 * abs(dy)) - (2 * abs(dx))
                pixels.append((xi, yi))
    else:  # |m| >= 1, step along y-axis
        while yi != y2:
            if Pi < 0:
                yi += sy
                Pi = Pi + (2 * abs(dx))
            else:
                xi += sx
                yi += sy
                Pi = Pi + (2 * abs(dx)) - (2 * abs(dy))
            pixels.append((xi, yi))
    
    return pixels