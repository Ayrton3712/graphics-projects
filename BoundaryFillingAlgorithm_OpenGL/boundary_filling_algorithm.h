#pragma once

#include "Point.h"
#include <vector>

// Function prototype for the boundary filling algorithm
// Returns a vector of Points that represent the filled area
// Takes a starting point and a fill color as an array
// For this to work the boundary must be completely defined and the starting point must be inside the boundary, no check is performed for now
void boundary_filling_algorithm(const Point&, const std::vector<Point>&, std::vector<Point>&);

// Overloaded function to pass the radius of a circle and ensure fill points do not surpass boundary
void boundary_filling_algorithm(const Point&, const std::vector<Point>&, std::vector<Point>&, GLfloat);