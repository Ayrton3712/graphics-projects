#include "bresenham_line.h"
#include "Point.h"

#include <vector>
#include <iostream>
#include <cmath>

std::vector<Point> bresenham_line(const Point& A, const Point& B) {
	// Declaring variables
	GLfloat dy, dx, m, P, current_x, current_y;
	// Declaring vector of points to be returned
	std::vector<Point> points;

	// Pushing initial point into points
    std::cout << "Initial point: ";
    A.displayPoint();
    points.push_back(A);

    // Calculating dy, dx, and m
    dy = B.getY() - A.getY();
    dx = B.getX() - A.getX();

    // Guard against vertical lines (dx == 0) to avoid division by zero
    if (dx == 0) {
        GLfloat step = (dy > 0) ? 1.0f : -1.0f;
        GLfloat cy = A.getY();
        while (cy != B.getY()) {
            cy += step;
            points.push_back(Point(A.getX(), cy));
        }
        return points;
    }

    m = dy / dx;

	// Calculating decision parameter
	P = 2 * dy - dx;

	// Initializing current_x and current_y
	current_x = A.getX();
	current_y = A.getY();
	Point current_point(current_x, current_y);

    // Checking slope (use absolute slope comparison)
    if (std::fabs(m) < 1.0f) {
        while (current_point != B) {
            if (P < 0) {
                current_x = current_x + 1;
                P = P + 2 * dy;
            }
            else {
                current_x = current_x + 1;
                current_y = current_y + 1;
                P = P + 2 * dy - 2 * dx;
            }

            // update current_point so the loop can terminate
            current_point = Point(current_x, current_y);
            points.push_back(current_point);

            std::cout << "Next point: ";
            current_point.displayPoint();
        }
    }
    else {
        while (current_point != B) {
            if (P < 0) {
                current_y = current_y + 1;
                P = P + 2 * dx;
            }
            else {
                current_x = current_x + 1;
                current_y = current_y + 1;
                P = P + 2 * dx - 2 * dy;
            }

            // update current_point so the loop can terminate
            current_point = Point(current_x, current_y);
            points.push_back(current_point);

            std::cout << "Next point: ";
            current_point.displayPoint();
        }
    }

    // Avoid duplicating B if it was already pushed inside the loop
    if (points.empty() || points.back() != B) {
        points.push_back(B);
    }

	return points;
}