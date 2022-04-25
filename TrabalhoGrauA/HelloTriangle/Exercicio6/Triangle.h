#pragma once
#include "Color.h"
#include "Point.h"

class Triangle {
private:
	Point top;
	Point left;
	Point right;
	Color color;

public:
	Triangle(Point top, Point left, Point right);
	Triangle();

	Point getTop();
	Point getLeft();
	Point getRight();

	void increaseX();
	void increaseY();
	void increaseZ();
	
	float* getPoints();

	void initializateX();
	void initializateY();
};
