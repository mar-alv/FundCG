#pragma once
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Constants.h"
#include "GridTypeEnum.h"
#include "PlayerActionEnum.h"
#include "GridDirectionsEnum.h"
#include "PlayerTextureDirectionFacingEnum.h"

class Enemy
{
private:
	GLuint VAO;
	float actualX;
	float actualY;
	Shader* shader;
	glm::mat4 model;
	Texture texture;
	GLuint textureId;
	int actualTileType;
	int actualDirection;
	int actualRowPosition;
	int actualColumnPosition;
	glm::vec2 actualPosition;

public:
	Enemy();

	int getActualRowPosition();
	int getActualColumnPosition();

	void setShader(Shader* shader);
	void setActualTileType(int actualTileType);

	void move();
	void render();
	void attack();
	void update();
	void updateShader();
	void updatePosition();
	void initializeTexture();
	void updateModelOnShader();
	void updateOffsetsOnShader();
	void calculateActualPosition();
	void stayInsideGrid(int gridRowsCount, int gridColumnsCount);
};
