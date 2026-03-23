#include "dda.h"
#include "Point.h"

#include <vector>
#include <iostream>

std::vector<Point> DDA(const Point& A, const Point& B) {
    // Declaring variables to be used
    float dy, dx, m;
    std::vector<Point> points;

    // Calculating dy and dx
    dy = B.getY() - A.getY();
    dx = B.getX() - A.getX();

    // Calculating slope
    m = dy / dx;

    Point initialPoint(A.getX(), A.getY()),
          endPoint(B.getX(), B.getY());

    std::cout << "Initial point: (" << initialPoint.getX() << ", " << initialPoint.getY() << ")\n";
    points.push_back(initialPoint);

    // Looping through x coordinates starting at the initial point until the end point
    for (int i = 1; i < (int)dx; i++) {
        float previous_y = points[i - 1].getY();
        float next_x = initialPoint.getX() + i;
        float next_y = initialPoint.getY() + m * i;

		std::cout << "Next point: (" << next_x << ", " << next_y << ")" << std::endl;
        points.push_back(Point(next_x, next_y));
    }

    std::cout << "End point: (" << endPoint.getX() << ", " << endPoint.getY() << ")\n";
    points.push_back(endPoint);

    return points;
}