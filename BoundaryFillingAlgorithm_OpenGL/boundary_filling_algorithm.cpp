#include "boundary_filling_algorithm.h"
#include "bresenham_circle.h"

#include <iostream>

std::vector<Point> boundary_filling_algorithm(
    const Point& start,
    const unsigned int WIDTH,
    const unsigned int HEIGHT,
    const std::vector<Point>& boundary)
{
    
    std::vector<Point> fill;

    bool foundInFill, foundInBoundary;
    
    // Checking if start point is in fill or boundary and storing results in boolean variables
	foundInFill     = std::find(fill.begin(), fill.end(), start) != fill.end();
	foundInBoundary = std::find(boundary.begin(), boundary.end(), start) != boundary.end();

    if (!(foundInFill || foundInBoundary)){
        fill.push_back(start);

		// Recursive calls for 4-connected neighbors
        boundary_filling_algorithm(Point(start.getX() + 1, start.getY()), WIDTH, HEIGHT, boundary);  // Right
        boundary_filling_algorithm(Point(start.getX() - 1, start.getY()), WIDTH, HEIGHT, boundary);  // Left
        boundary_filling_algorithm(Point(start.getX(), start.getY() + 1), WIDTH, HEIGHT, boundary);  // Top
		boundary_filling_algorithm(Point(start.getX(), start.getY() - 1), WIDTH, HEIGHT, boundary);  // Bottom
    }

    return fill;
}