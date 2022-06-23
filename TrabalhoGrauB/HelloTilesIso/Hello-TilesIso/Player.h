#pragma once
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Constants.h"
#include "GridTypeEnum.h"
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
	bool hasWatered;
	bool isAttacking;
	int actualTileType;
	bool isCarryingWater;
	int actualRowPosition;
	Texture actualTexture;
	int actualColumnPosition;
	glm::vec2 actualPosition;
	static int actualDirection;
	std::vector<Texture> textures;
	
public:
	Player();

	bool getHasWatered();
	int getActualRowPosition();
	Texture getActualTexture();
	int getActualColumnPosition();

	void setShader(Shader* shader);
	void setHasWatered(bool hasWatered);
	void setActualTileType(int actualTileType);

	void move();
	void render();
	void attack();
	void update();
	void waterPlant();
	void collectWater();
	void updateShader();
	void updateTexture();
	void updatePosition();
	void updateTextureFrame();
	void initializeTextures();
	void updateModelOnShader();
	void updateOffsetsOnShader();
	void calculateActualPosition();
	void addTexture(Texture texture);
	void onKeyPress(int key, int action);
	void onActionKeyPress(int key, int action);
	void onMovementKeyPress(int key, int action);
	void stayInsideGrid(int gridRowsCount, int gridColumnsCount);
};
