#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Constants.h"
#include "GridDirectionsEnum.h"

class Player
{
private:
	GLuint VAO;
	float actualX;
	float actualY;
	Shader* shader;
	glm::mat4 model;
	Texture texture;
	GLuint textureId;
	glm::vec2 actualPosition;
	int actualRowPosition;
	int actualColumnPosition;
	static int actualDirection;
	
public:
	Player();

	void move();
	void render();
	void updateShader();
	void initializeTexture();
	void updateModelOnShader();
	void updateOffsetsOnShader();
	void calculateActualPosition();

	Texture getTexture();
	int getActualRowPosition();
	int getActualColumnPosition();

	void setShader(Shader* shader);

	void onMovementKeyPress(int key, int action);
	void stayInsideGrid(int gridRowsCount, int gridColumnsCount);
};
