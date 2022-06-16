#pragma once
#include "Texture.h"
#include "Constants.h"
#include "GridDirectionsEnum.h"

class Player
{
private:
	int actualX;
	int actualY;

	Texture texture;

	glm::vec2 actualPosition;

	static int actualDirection;
	
public:
	Player();

	void move();

	int getActualX();
	int getActualY();
	Texture getTexture();

	void onMovementKeyPress(int key, int action);

	void stayInsideGrid(int gridRowsCount, int gridColumnsCount);
};
