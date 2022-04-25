#include "Cube.h"

Cube::Cube(Square frontSquare, Square backSquare, Square leftSquare, Square rightSquare, Square topSquare, Square bottomSquare) {
	this->frontSquare = frontSquare;
	this->backSquare = backSquare;
	this->leftSquare = leftSquare;
	this->rightSquare = rightSquare;
	this->topSquare = topSquare;
	this->bottomSquare = bottomSquare;
}

Cube::Cube() {
}

Square Cube::getFrontSquare() {
	return frontSquare;
}

Square Cube::getBackSquare() {
	return backSquare;
}

Square Cube::getLeftSquare() {
	return leftSquare;
}

Square Cube::getRightSquare() {
	return rightSquare;
}

Square Cube::getTopSquare() {
	return topSquare;
}

Square Cube::getBottomSquare() {
	return bottomSquare;
}

float* Cube::getPoints() {
	float* frontPoints = frontSquare.getPoints();
	float* backPoints = backSquare.getPoints();
	float* leftPoints = leftSquare.getPoints();
	float* rightPoints = rightSquare.getPoints();
	float* topPoints = topSquare.getPoints();
	float* bottomPoints = bottomSquare.getPoints();

	float* points = new float[216];

	for (int i = 0; i < 36; i++) {
		points[i] = frontPoints[i];
		points[i + 36] = backPoints[i];
		points[i + 72] = leftPoints[i];
		points[i + 108] = rightPoints[i];
		points[i + 144] = topPoints[i];
		points[i + 180] = bottomPoints[i];
	}

	return points;
}

void Cube::initializateX() {
	frontSquare.initializateX();
	backSquare.initializateX();
	leftSquare.initializateX();
	rightSquare.initializateX();
	topSquare.initializateX();
	bottomSquare.initializateX();
}

void Cube::increaseX() {
	frontSquare.increaseX();
	backSquare.increaseX();
	leftSquare.increaseX();
	rightSquare.increaseX();
	topSquare.increaseX();
	bottomSquare.increaseX();
}

void Cube::increaseY() {
	frontSquare.increaseY();
	backSquare.increaseY();
	leftSquare.increaseY();
	rightSquare.increaseY();
	topSquare.increaseY();
	bottomSquare.increaseY();
}

void Cube::increaseZ() {
	frontSquare.increaseZ();
	backSquare.increaseZ();
	leftSquare.increaseZ();
	rightSquare.increaseZ();
	topSquare.increaseZ();
	bottomSquare.increaseZ();
}

void Cube::initializateY() {
	frontSquare.initializateY();
	backSquare.initializateY();
	leftSquare.initializateY();
	rightSquare.initializateY();
	topSquare.initializateY();
	bottomSquare.initializateY();
}
