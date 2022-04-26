#include "Triangle.h"

Triangle::Triangle(Point top, Point left, Point right) {
	this->top = top;
	this->left = left;
	this->right = right;
	this->color = Color(1.0, 1.0, 1.0);
}

Triangle::Triangle() {
}

Point Triangle::getTop() {
	return top;
}

Point Triangle::getLeft() {
	return left;
}

Point Triangle::getRight() {
	return right;
}

Color Triangle::getColor() {
	return this->color;
}

float* Triangle::getPoints() {
	float* topPoints = top.getPoints();
	float* leftPoints = left.getPoints();
	float* rightPoints = right.getPoints();
	float* colorPoints = color.getPoints();

	float* points = new float[18];

	for (int i = 0; i < 3; i++) {
		points[i] = topPoints[i];
		points[i + 3] = colorPoints[i];
		points[i + 6] = leftPoints[i];
		points[i + 9] = colorPoints[i];
		points[i + 12] = rightPoints[i];
		points[i + 15] = colorPoints[i];
	}

	return points;
}

void Triangle::initializateX() {
	top.initializateX();
	left.initializateX();
	right.initializateX();
}

void Triangle::increaseX() {
	top.increaseX();
	left.increaseX();
	right.increaseX();
}

void Triangle::increaseY() {
	top.increaseY();
	left.increaseY();
	right.increaseY();
}

void Triangle::increaseZ() {
	top.increaseZ();
	left.increaseZ();
	right.increaseZ();
}

void Triangle::initializateY() {
	top.initializateY();
	left.initializateY();
	right.initializateY();
}

void Triangle::changeColor(Color color) {
	this->color = color;

	std::cout << "TRIANGULO: " << this->color.getR() << " - " << this->color.getG() << " - " << this->color.getB() << " - " << std::endl;
}
