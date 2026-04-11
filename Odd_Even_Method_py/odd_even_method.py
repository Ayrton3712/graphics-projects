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

