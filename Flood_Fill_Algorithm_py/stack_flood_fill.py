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

# Function that implements the stack-based flood fill algorithm
def stack_flood_fill(x, y, new_color, old_color):
    # Stack created as a list, will store points as tuples. Initially, it contains the start point (x, y)
    stack = [(x, y)]

    while stack:
        cx, cy = stack.pop()

        if cx < 0 or cx >= grid.shape[0] or cy < 0 or cy >= grid.shape[1]:
            continue
        if grid[cx, cy] != old_color:
            continue

        grid[cx, cy] = new_color

        stack.append((cx + 1, cy))
        stack.append((cx - 1, cy))
        stack.append((cx, cy + 1))
        stack.append((cx, cy - 1))


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

stack_flood_fill(2, 2, 'G', 'B')

# Printing grid after flood fill
print("Grid AFTER flood fill:")
print_grid(grid)