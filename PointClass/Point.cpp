#include "Point.h"

#include <iostream>

Point::Point(float x, float y){
    this -> x = x;
    this -> y = y;
}

float Point::getX() const{
    return this -> x;
}

float Point::getY() const{
    return this -> y;
}

void Point::setX(float x){
    this -> x = x;
}

void Point::setY(float y){
    this -> y = y;
}

void Point::displayPoint() const{
    std::cout << "(" << this->x << ", " << this->y << ")\n";
}