import pygame
from bresenham_line_pixels import bresenham_line

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
CYAN = (0, 255, 255)

def draw_polygon(vertices):
    """ Draw a polygon by connecting vertices using Bresenham's line algorithm """
    boundary_pixels = set()
    
    # Connect each vertex to the next (and last to first)
    for i in range(len(vertices)):
        x1, y1 = vertices[i]
        x2, y2 = vertices[(i + 1) % len(vertices)]
        
        # Get pixels along the line from vertex i to vertex i+1
        line_pixels = bresenham_line(x1, y1, x2, y2)
        boundary_pixels.update(line_pixels)
    
    return boundary_pixels

def odd_even_method(point, vertices, max_width=800):
    """ Odd-Even method to determine if a point is inside a polygon """
    px, py = point
    crossing_count = 0
    
    # Cast a ray from the point to the right (horizontally)
    # We will check intersections with each edge of the polygon
    
    for i in range(len(vertices)):
        # Get the current edge
        x1, y1 = vertices[i]
        x2, y2 = vertices[(i + 1) % len(vertices)]
        
        # Check if the ray crosses this edge
        # The ray is a horizontal line at y = py, extending to the right (x > px)
        
        # Edge must span the y-coordinate of the point
        if (y1 <= py < y2) or (y2 <= py < y1):
            # Calculate the x-coordinate where the edge crosses the horizontal ray
            # Using line equation: y - y1 = m(x - x1), where m = (y2 - y1) / (x2 - x1)
            # Solving for x when y = py:
            # py - y1 = m(x - x1)
            # x = x1 + (py - y1) / m
            
            if x2 != x1:  # Avoid division by zero
                x_intersect = x1 + (py - y1) * (x2 - x1) / (y2 - y1)
                
                # Check if intersection is to the right of the point
                if x_intersect > px:
                    crossing_count += 1
    
    # Odd count = inside, Even count = outside
    return crossing_count % 2 == 1

