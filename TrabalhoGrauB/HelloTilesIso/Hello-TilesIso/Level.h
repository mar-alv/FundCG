#pragma once
#include <vector>
#include "Plant.h"
#include "Enemy.h"
#include "Texture.h"
#include "TileIso.h"
#include "GridTypeEnum.h"
#include "PlantTypeEnum.h"

class Level
{
private:
	int levelNumber;
	int gridRowsCount;
	Shader* shaderTile;
	Shader* shaderPlant;
	int gridColumnsCount;
	std::vector<Plant> plants;
	std::vector<Enemy> enemies;
	std::vector<std::vector<TileIso>> grid;

public:
	Level(Shader* shaderTile, Shader* shaderPlant, char levelNumber);

	int getGridRowsCount();
	int getGridColumnsCount();
	std::vector<std::vector<TileIso>> getGrid();

	void render();
	void initialize();
	void moveEnemies();
	void renderTiles();
	void renderPlants();
	void renderEnemies();
	void growPlant(int x, int y);
	void initializeEnemiesTexture(Shader* shader);
	void addPlant(int x, int y, int actualRowPosition, int actualColumnPosition);
};
