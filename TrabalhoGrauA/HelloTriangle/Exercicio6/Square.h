#pragma once
#include "Triangle.h"

class Square {
private:
	Triangle topTriangle;
	Triangle bottomTriangle;

public:
	Square(Triangle topTriangle, Triangle bottomTriangle);
	Square();

	Triangle getTopTriangle();
	Triangle getBottomTriangle();
	
	float* getPoints();
	
	void increaseX();
	void increaseY();
	void increaseZ();

	void initializateX();
	void initializateY();

	void changeColor(Color color);
};
