#pragma once
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Constants.h"
#include "PlayerActionEnum.h"
#include "GridDirectionsEnum.h"
#include "PlayerTextureDirectionFacingEnum.h"

class Player
{
private:
	float actualX;
	float actualY;
	Shader* shader;
	glm::mat4 model;
	bool isAttacking;
	bool isCarryingWater;
	int actualRowPosition;
	Texture actualTexture;
	bool isWateringPlants;
	bool isCollectingWater;
	int actualColumnPosition;
	glm::vec2 actualPosition;
	static int actualDirection;
	std::vector<Texture> textures;
	
public:
	Player();

	void move();
	void render();
	void updateShader();
	void updateTexture();
	void initializeTextures();
	void updateModelOnShader();
	void updateOffsetsOnShader();
	void calculateActualPosition();

	int getActualRowPosition();
	Texture getActualTexture();
	int getActualColumnPosition();

	void setShader(Shader* shader);

	void attack();
	void waterPlant();
	void collectWater();
	void onKeyPress(int key, int action);
	void onActionKeyPress(int key, int action);
	void onMovementKeyPress(int key, int action);
	void stayInsideGrid(int gridRowsCount, int gridColumnsCount);
};
