#include "Point.h"
#include "normalize.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Point::Point(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}

void Point::displayPoint() const {
	std::cout << "(" << this->x << ", " << this->y << ")\n";
}

GLfloat Point::getX() const {
	return this->x;
}

GLfloat Point::getY() const {
	return this->y;
}

void Point::setX(GLfloat x) {
	this->x = x;
}

void Point::setY(GLfloat y) {
	this->y = y;
}

void Point::normalizePoint(GLfloat normalizationFactorX, GLfloat normalizationFactorY) {
	this->x = normalize(this->x, normalizationFactorX);
	this->y = normalize(this->y, normalizationFactorY);
}

bool Point::operator==(const Point& other) const {
	if (this->x == other.getX() && this->y == other.getY()) {
		return true;
	}
	else {
		return false;
	}
}

bool Point::operator!=(const Point& other) const {
	if (this->x != other.getX() || this->y != other.getY()) {
		return true;
	}
	else {
		return false;
	}
}