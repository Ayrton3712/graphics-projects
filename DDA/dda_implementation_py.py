# Implementation of DDA in Python

class Point():
    def __init__(self, x_coord, y_coord):
        self.x_coord = x_coord
        self.y_coord = y_coord
    
    def display(self):
        print(f"({self.x_coord}, {self.y_coord})")

# Function to calculate all intermediate points between initial and end point
def DDA(initial_point, end_point):
    pass

print("Enter two points:")
point1 = Point(input("x1: "), input("y1: "))
point2 = Point(input("x2: "), input("y2: "))

print("Points entered:")
point1.display()
point2.display()