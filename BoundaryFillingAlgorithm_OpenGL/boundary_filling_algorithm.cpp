#include "boundary_filling_algorithm.h"
#include "bresenham_circle.h"

std::vector<Point> boundary_filling_algorithm(const Point& start, GLfloat fillColor[4], const unsigned int WIDTH, const unsigned int HEIGHT, const std::vector<Point>& boundary) {
	// The code below would be a plausible approach if we didn't have to start at the start point.
	//// Outer loop: Traverses the x-axis from the leftmost corner to the rightmost corner of the viewport
	//for (int i = -(WIDTH / 2); i < WIDTH / 2; i++) {
	//	// Inner loop: Traverses the y-axis from the topmost corner to the bottommost corner of the viewport
	//	for (int j = -(HEIGHT / 2); j < HEIGHT / 2; j++) {
	//		if (Point(i, ) =)
	//	}
	//}

	std::vector<Point> fill; // Vector that will store the points to be filled

	Point currentPoint = start; // Initialize the current point to the starting point
	
	std::vector<Point> adjacentPoints = {
		Point(currentPoint.getX(),		currentPoint.getY() + 1),
		Point(currentPoint.getX() + 1,	currentPoint.getY()),
		Point(currentPoint.getX() - 1,	currentPoint.getY()),
		Point(currentPoint.getX(),		currentPoint.getY() - 1)
	};

	/*Point upwardPoint	(currentPoint.getX(),		currentPoint.getY() + 1),
		  rightPoint	(currentPoint.getX() + 1,	currentPoint.getY()),
		  leftPoint		(currentPoint.getX() - 1,	currentPoint.getY()),
		  bottomPoint	(currentPoint.getX(),		currentPoint.getY() - 1);*/
	
	// Starting at the given start point. We will assume that it is not a boundary point.
	
	//bool found = std::find(boundary.begin(), boundary.end(), currentPoint) != boundary.end();
	// Flags to be used in each comparison
	bool foundInFill;
	bool foundInBoundary;
		
	// Adding each adjacent point to the fill vector if it is not already in the fill vector and not in the boundary vector
	for (int i = 0; i < adjacentPoints.size(); i++) {
		foundInFill = std::find(fill.begin(), fill.end(), adjacentPoints[i]) != fill.end();
		foundInBoundary = std::find(boundary.begin(), boundary.end(), adjacentPoints[i]) != boundary.end();
		if (!foundInFill && !foundInBoundary) {
			fill.push_back(adjacentPoints[i]);
		}
	}
	// This should produce the first filled points around the pixel given by the start point. We can then repeat the process for each of the points in the fill vector until we have filled all the points that are not in the boundary vector.
	// Problem from now: Where do you move?

	return fill;
}

// Test main function
// It works!!
//int main() {
//	std::vector<Point> boundary;
//	BresenhamCircle(0, 5, boundary);
//	std::vector<Point> fill = boundary_filling_algorithm(Point(0, 0), nullptr, 800, 600, boundary);
//
//	for (Point p : fill) {
//		p.displayPoint();
//	}
//}