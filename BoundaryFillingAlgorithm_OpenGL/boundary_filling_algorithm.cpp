#include "boundary_filling_algorithm.h"
#include "bresenham_circle.h"

#include <iostream>

// General boundary fill for any shape with a well-defined boundary
void boundary_filling_algorithm(
    const Point& start,
    const std::vector<Point>& boundary,
    std::vector<Point>& fill)
{

    bool foundInFill, foundInBoundary;

    // Checking if start point is in fill or boundary and storing results in boolean variables
	foundInFill     = std::find(fill.begin(), fill.end(), start) != fill.end();
	foundInBoundary = std::find(boundary.begin(), boundary.end(), start) != boundary.end();

    if (!(foundInFill || foundInBoundary)) {
        fill.push_back(start);
        
        // Recursive calls for 4-connected neighbors
        boundary_filling_algorithm(Point(start.getX() + 1, start.getY()), boundary, fill);  // Right
        boundary_filling_algorithm(Point(start.getX() - 1, start.getY()), boundary, fill);  // Left
        boundary_filling_algorithm(Point(start.getX(), start.getY() + 1), boundary, fill);  // Top
        boundary_filling_algorithm(Point(start.getX(), start.getY() - 1), boundary, fill);  // Bottom
    }
}

// Boundary fill for a circle with a start point at the center
void boundary_filling_algorithm(
    const Point& start,
    const std::vector<Point>& boundary,
    std::vector<Point>& fill,
    GLfloat radius)
{
    // First check if the distance from the origin to start is not greater than the radius
	GLfloat distanceFromOrigin = std::sqrt(std::pow(start.getX(), 2) + std::pow(start.getY(), 2));

    if (distanceFromOrigin > radius) {
		return; // If the point is outside the circle, we stop the recursion
    }
    
    bool foundInFill, foundInBoundary;

    // Checking if start point is in fill or boundary and storing results in boolean variables
    foundInFill = std::find(fill.begin(), fill.end(), start) != fill.end();
    foundInBoundary = std::find(boundary.begin(), boundary.end(), start) != boundary.end();

    if (!(foundInFill || foundInBoundary)) {
        if (distanceFromOrigin == radius) {
            return;
        }
        else {
            fill.push_back(start);
            
            // Recursive call for 4-connected neighbors
            boundary_filling_algorithm(Point(start.getX() + 1, start.getY()), boundary, fill, radius);  // Right
            boundary_filling_algorithm(Point(start.getX() - 1, start.getY()), boundary, fill, radius);  // Left
            boundary_filling_algorithm(Point(start.getX(), start.getY() + 1), boundary, fill, radius);  // Top
            boundary_filling_algorithm(Point(start.getX(), start.getY() - 1), boundary, fill, radius);  // Bottom
        }
    }
}