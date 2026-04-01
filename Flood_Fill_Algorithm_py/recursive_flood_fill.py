import numpy as np

# Dictionary storing character-ANSI color key-value pairs
COLORS = {
    'B': '\033[44m',  # blue background
    'R': '\033[41m',  # red background
    'G': '\033[42m',  # green background
}
RESET = '\033[0m' # Fallback white color

# Function to print a grid with ANSI colors
def print_grid(grid):
    for row in grid:
        line = ''
        for cell in row:
            color = COLORS.get(cell, '\033[47m')
            line += f'{color}  {RESET}'
        print(line)
    print()

# Flood fill function
def flood_fill(x, y, newColor, oldColor):
    # Checking bounds
    if x < 0 or x >= grid.shape[0] or y < 0 or y >= grid.shape[1]:
        return
    
    # Base case
    if grid[x, y] == oldColor:
        grid[x, y] = newColor
        flood_fill(x + 1, y, newColor, oldColor)
        flood_fill(x, y + 1, newColor, oldColor)
        flood_fill(x - 1, y, newColor, oldColor)
        flood_fill(x, y - 1, newColor, oldColor)

# Example grid with a hard-coded boundary stored in an np array
grid = np.array([['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
                ['B', 'R', 'R', 'R', 'R', 'B', 'B', 'B', 'B', 'B'],
                ['B', 'R', 'B', 'B', 'B', 'R', 'B', 'B', 'B', 'B'],
                ['B', 'R', 'B', 'B', 'B', 'R', 'R', 'R', 'R', 'B'],
                ['B', 'R', 'B', 'B', 'B', 'B', 'B', 'B', 'R', 'B'],
                ['B', 'R', 'B', 'B', 'B', 'B', 'B', 'B', 'R', 'B'],
                ['B', 'R', 'B', 'B', 'B', 'B', 'B', 'B', 'R', 'B'],
                ['B', 'B', 'R', 'B', 'B', 'B', 'B', 'R', 'B', 'B'],
                ['B', 'B', 'R', 'B', 'B', 'B', 'R', 'B', 'B', 'B'],
                ['B', 'B', 'B', 'R', 'R', 'R', 'B', 'B', 'B', 'B'],
                ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B']])
   
# Printing grid before flood fill
print("Grid BEFORE flood fill:")
print_grid(grid)

flood_fill(2, 2, 'G', 'B')

# Printing grid after flood fill
print("Grid AFTER flood fill:")
print_grid(grid)