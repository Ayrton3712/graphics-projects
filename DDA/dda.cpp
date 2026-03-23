#include "dda.h"
#include "Point.h"

#include <vector>

std::vector<Point> DDA(const Point& A, const Point& B){
    // Declaring variables to be used
    float dy, dx, m;
    std::vector<Point> points;

    // Calculating dy and dx
    dy = B.getY() - A.getY();
    dx = B.getX() - A.getX();

    // Calculating slope
    m = dy / dx;

    Point initialPoint(A.getX(), A.getY()),
          endPoint    (B.getX(), B.getY());

    points.push_back(initialPoint);

    // Looping through x coordinates starting at the initial point until the end point
    for (int i = 1; i < (int)dx; i++){
        float previous_y = points[i - 1].getY();
        float next_x = initialPoint.getX() + i;
        float next_y = initialPoint.getY() + m * i;

        points.push_back(Point(next_x, next_y));
    }

    points.push_back(endPoint);
        
    return points;
}

int main(){
    std::vector<Point> line = DDA(Point(2, 2), Point(6, 6));

    for (Point p : line){
        p.displayPoint();
    }

    return 0;
}