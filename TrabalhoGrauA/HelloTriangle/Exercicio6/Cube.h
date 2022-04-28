#pragma once
#include "Square.h"

class Cube
{
private:
	Square frontSquare;
	Square backSquare;
	Square leftSquare;
	Square rightSquare;
	Square topSquare;
	Square bottomSquare;

public:
	Cube(Square frontSquare, Square backSquare, Square leftSquare, Square rightSquare, Square topSquare, Square bottomSquare);
	Cube();

	Square getFrontSquare();
	Square getBackSquare();

	Square getLeftSquare();
	Square getRightSquare();
	Square getTopSquare();
	Square getBottomSquare();
	float* getPoints();

	void increaseX();
	void increaseY();
	void increaseZ();

	void initializateX();
	void initializateY();

	void changeColor(Color color);
};
