#pragma once
#include "Sprite.h"
#include "GridDirectionsEnum.h"

class Player
{
private:
	int actualX;
	int actualY;

	Sprite sprite;
	glm::vec2 actualPosition;

	static int actualDirection;
	
public:
	Player();

	void move();

	int getActualX();
	int getActualY();

	void onMovementKeyPress(int key, int action);

	void stayInsideGrid(int gridRowsCount, int gridColumnsCount);
};
