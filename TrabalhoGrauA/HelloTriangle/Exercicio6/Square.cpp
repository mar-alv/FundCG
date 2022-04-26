#include "Square.h"

Square::Square(Triangle topTriangle, Triangle bottomTriangle) {
	this->topTriangle = topTriangle;
	this->bottomTriangle = bottomTriangle;
}

Square::Square() {
}

Triangle Square::getTopTriangle() {
	return topTriangle;
}

Triangle Square::getBottomTriangle() {
	return bottomTriangle;
}

float* Square::getPoints() {
	float* topPoints = topTriangle.getPoints();
	float* bottomPoints = bottomTriangle.getPoints();

	float* points = new float[36];

	for (int i = 0; i < 18; i++) {
		points[i] = topPoints[i];
		points[i + 18] = bottomPoints[i];
	}

	return points;
}

void Square::initializateX() {
	topTriangle.initializateX();
	bottomTriangle.initializateX();
}

void Square::increaseX() {
	topTriangle.increaseX();
	bottomTriangle.increaseX();
}

void Square::increaseY() {
	topTriangle.increaseY();
	bottomTriangle.increaseY();
}

void Square::increaseZ() {
	topTriangle.increaseZ();
	bottomTriangle.increaseZ();
}

void Square::initializateY() {
	topTriangle.initializateY();
	bottomTriangle.initializateY();
}

void Square::changeColor(Color color) {
	topTriangle.changeColor(color);
	bottomTriangle.changeColor(color);
}
