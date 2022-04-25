#include "Point.h"

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->initialX = x;
	this->initialY = y;
}

Point::Point() {
}

float Point::getX() {
	return this->x;
}

float Point::getY() {
	return this->y;
}

float Point::getZ() {
	return this->z;
}

void Point::setX(float x) {
	this->x = x;
}

void Point::setY(float y) {
	this->y = y;
}

void Point::setZ(float z) {
	this->z = z;
}

float Point::getInitialX() {
	return this->initialX;
}

float Point::getInitialY() {
	return this->initialY;
}

float* Point::getPoints() {
	float* points = new float[3];

	points[0] = x; 
	points[1] = y;
	points[2] = z;
		
	return points;
}

void Point::initializateX() {
	this->x = this->getInitialX();
}

void Point::increaseX() {
	setX(x + 0.1);
}

void Point::increaseY() {
	setY(y + 0.1);
}

void Point::increaseZ() {
	setZ(z + 0.1);
}

void Point::initializateY() {
	this->y = this->getInitialY();
}
