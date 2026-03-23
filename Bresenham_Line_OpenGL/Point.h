#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Point {
private:
	GLfloat x, y;

public:
	Point(GLfloat, GLfloat);
	void displayPoint  ()		 const;
	void normalizePoint(GLfloat, GLfloat);

	// Getters
	GLfloat getX() const;
	GLfloat getY() const;

	// Setters
	void setX(GLfloat);
	void setY(GLfloat);

	// Overloading == and != operators
	bool operator==(const Point&) const;
	bool operator!=(const Point&) const;
};