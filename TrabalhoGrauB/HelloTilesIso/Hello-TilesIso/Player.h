#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Constants.h"
#include "GridDirectionsEnum.h"

class Player
{
private:
	int actualX;
	int actualY;

	Shader* shader;

	GLuint VAO;
	GLuint textureId;

	Texture texture;

	glm::vec2 actualPosition;

	static int actualDirection;
	
public:
	Player();

	void move();
	void render();
	void initializeTexture();

	int getActualX();
	int getActualY();
	Texture getTexture();

	void setShader(Shader* shader);

	void onMovementKeyPress(int key, int action);

	void stayInsideGrid(int gridRowsCount, int gridColumnsCount);
};
