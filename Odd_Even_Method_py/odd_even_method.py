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

def render_polygon_with_test(screen, vertices, test_point=None, pixel_size=4):
    """ Render the polygon on the pygame screen and test if a point is inside """
    screen.fill(WHITE)
    
    # Draw the polygon boundary
    boundary_pixels = draw_polygon(vertices)
    for px, py in boundary_pixels:
        pygame.draw.rect(screen, BLUE, (px * pixel_size, py * pixel_size, pixel_size, pixel_size))
    
    # Draw vertices
    for vx, vy in vertices:
        pygame.draw.rect(screen, RED, (vx * pixel_size - 2, vy * pixel_size - 2, 4, 4))
    
    # Draw test point and ray if provided
    if test_point:
        tx, ty = test_point
        is_inside = odd_even_method(test_point, vertices)
        
        # Color based on inside/outside
        point_color = GREEN if is_inside else RED
        
        # Draw the test point
        pygame.draw.rect(screen, point_color, (tx * pixel_size - 2, ty * pixel_size - 2, 4, 4))
        
        # Draw the ray to the right
        pygame.draw.line(screen, CYAN, (tx * pixel_size, ty * pixel_size), (800, ty * pixel_size), 1)
        
        return is_inside
    
    return None

def main():
    pygame.init()
    
    # Window setup
    WIDTH, HEIGHT = 800, 600
    PIXEL_SIZE = 4  # Each logical pixel is 4x4 screen pixels
    
    # Logical dimensions (in pixels)
    LOGICAL_WIDTH = WIDTH // PIXEL_SIZE
    LOGICAL_HEIGHT = HEIGHT // PIXEL_SIZE
    
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Odd-Even Method")
    clock = pygame.time.Clock()
    
    polygon_vertices = [
        (20, 20),
        (60, 20),
        (80, 30),
        (70, 70),
        (30, 75),
        (10, 50),
    ]
    
    # Initial test point, changed with cursor in the window
    test_point = (40, 40)
    
    font = pygame.font.Font(None, 24)
    
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEMOTION:
                # Update test point based on mouse position
                mouse_x, mouse_y = pygame.mouse.get_pos()
                test_point = (mouse_x // PIXEL_SIZE, mouse_y // PIXEL_SIZE)
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
        
        # Render
        is_inside = render_polygon_with_test(screen, polygon_vertices, test_point, PIXEL_SIZE)
        
        # Draw information
        status_text = "INSIDE" if is_inside else "OUTSIDE"
        status_color = GREEN if is_inside else RED
        
        info_text = font.render(f"Point: ({test_point[0]}, {test_point[1]}) - {status_text}", True, status_color)
        screen.blit(info_text, (10, 10))
        
        help_text = font.render("Move mouse to test points. Press ESC to exit.", True, BLACK)
        screen.blit(help_text, (10, 35))
        
        pygame.display.flip()
        clock.tick(60)
    
    pygame.quit()

if __name__ == "__main__":
    main()