#include "midpoint_circle.h"
#include "Point.h"

std::vector<Point> midpoint_circle(GLfloat xc, GLfloat yc, GLfloat r) {
    std::vector<Point> points;

    GLfloat x = 0;
    GLfloat y = r;

    // Initial decision parameter
    GLfloat P = 1.25 - r; // equivalent to (5/4) - r

    // Push the starting point (offset by center)
    points.push_back(Point(xc + x, yc + y));

    while (x < y) {
        x += 1;

        if (P < 0) {
            // Midpoint is inside the circle: move straight right
            P += 2 * x + 1;
        }
        else {
            // Midpoint is outside: move diagonally (right and down)
            y -= 1;
            P += 2 * x - 2 * y + 1;
        }

        points.push_back(Point(xc + x, yc + y));

        std::cout << "Plotted: (" << xc + x << ", " << yc + y << ")\n";
    }

    // Traversing the vector in reverse order to mirror points for octal
    for (int i = points.size() - 1; i >= 0; i--) {
        Point newPoint(points[i].getY(), points[i].getX());
        std::cout << "Plotted: ";
        newPoint.displayPoint();
        points.push_back(newPoint);
    }

    // Quad 1 completed

    int points_in_quad1 = points.size();

    // Quad 2
    for (int i = 0; i < points_in_quad1; i++) {
        Point newPoint(points[i].getX(), -points[i].getY());
        std::cout << "Plotted: ";
        newPoint.displayPoint();
        points.push_back(newPoint);
    }

    // Quad 3
    for (int i = 0; i < points_in_quad1; i++) {
        Point newPoint(-points[i].getY(), -points[i].getX());
        std::cout << "Plotted: ";
        newPoint.displayPoint();
        points.push_back(newPoint);
    }

    // Quad 4
    for (int i = 0; i < points_in_quad1; i++) {
        Point newPoint(-points[i].getY(), points[i].getX());
        std::cout << "Plotted: ";
        newPoint.displayPoint();
        points.push_back(newPoint);
    }

    return points;
}

// Test main function
//int main() {
//	std::vector<Point> points = midpoint_circle(0.0f, 0.0f, 3.0f);
//
//	return 0;
//}