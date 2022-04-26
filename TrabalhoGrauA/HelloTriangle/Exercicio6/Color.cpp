#include "Color.h"

Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color() {
}

float* Color::getPoints() {
	float* points = new float[3];

	points[0] = r;
	points[1] = g;
	points[2] = b;

	return points;
}


float Color::getR() {
	return this->r;
}

float Color::getG() {
	return this->g;
}

float Color::getB() {
	return this->b;
}
