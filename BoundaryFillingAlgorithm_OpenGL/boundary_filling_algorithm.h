#pragma once

#include "Point.h"
#include <vector>

// Function prototype for the boundary filling algorithm
// Returns a vector of Points that represent the filled area
// Takes a starting point and a fill color as an array
std::vector<Point> boundary_filling_algorithm(const Point&, float[]);