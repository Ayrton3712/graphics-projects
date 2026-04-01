#include "bresenham_circle.h"
#include "Point.h"

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void BresenhamCircle(GLfloat x0, GLfloat r, std::vector<Point>& points) {
    // Calculating decision parameter
    GLfloat P = 3 - (2 * r);

    // Declaring variables to be used in the algorithm
    GLfloat next_x = x0, next_y = r;

    // Pushing initial point
    points.push_back(Point(x0, r));

    // Quad 1
    int i = 1; // Counter
    while (!(next_x >= next_y || next_x == next_y)) {
        // Checking decision parameter and performing corresponding operations
        if (P < 0) {
            next_x = next_x + 1;

            points.push_back(Point(next_x, next_y));

            P = P + (4 * next_x) + 6;
        }
        else {
            next_x = next_x + 1;
            next_y = next_y - 1;

            points.push_back(Point(next_x, next_y));

            P = P + (4 * (next_x - next_y)) + 10;
        }

        //std::cout << "Iteration " << i << ": " << "Next x: " << next_x << ", Next y: " << next_y << std::endl;
        ++i;
    }
    points.pop_back(); // Removing the extra point pushed

    // One octal completed

    // Traversing the vector in reverse order to mirror points for octal
    for (int i = points.size() - 1; i >= 0; i--) {
        points.push_back(Point(points[i].getY(), points[i].getX()));
    }

    // Quad 1 completed

    int points_in_quad1 = points.size();

    // Quad 2
    for (int i = 0; i < points_in_quad1; i++) {
        points.push_back(Point(points[i].getX(), -points[i].getY()));
    }

    // Quad 3
    for (int i = 0; i < points_in_quad1; i++) {
        points.push_back(Point(-points[i].getX(), -points[i].getY()));
    }

    // Quad 4
    for (int i = 0; i < points_in_quad1; i++) {
        points.push_back(Point(-points[i].getX(), points[i].getY()));
    }
}