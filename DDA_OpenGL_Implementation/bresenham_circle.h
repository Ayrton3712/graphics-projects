#pragma once

#include "Point.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void BresenhamCircle(GLfloat x0, GLfloat r, std::vector<Point>& points);
