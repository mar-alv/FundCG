#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Constants.h"
#include "GridDirectionsEnum.h"
#include "PlayerTextureDirectionFacingEnum.h"

class Player
{
private:
	GLuint VAO;
	bool isCarryingWater;
	float actualX;
	float actualY;
	Shader* shader;
	glm::mat4 model;
	Texture texture;
	GLuint textureId;
	int actualRowPosition;
	int actualColumnPosition;
	glm::vec2 actualPosition;
	static int actualDirection;
	
public:
	Player();

	void move();
	void render();
	void updateShader();
	void updateTexture();
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
