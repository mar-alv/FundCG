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
	void spawnEnemy();
	void renderTiles();
	void renderPlants();
	void renderEnemies();
	bool checkIfPlayerWon();
	bool checkIfPlayerLost();
	void growPlant(int x, int y);
	void makeEnemiesMoveOrAttack();
	void updateEnemyActualTileType();
	void killEnemy(int playerX, int playerY);
	void addPlant(int x, int y, int actualRowPosition, int actualColumnPosition);
};
