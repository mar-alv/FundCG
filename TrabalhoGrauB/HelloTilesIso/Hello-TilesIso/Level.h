#pragma once
#include <vector>
#include "Plant.h"
#include "Texture.h"
#include "TileIso.h"
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
	std::vector<std::vector<TileIso>> grid;

public:
	Level(Shader* shaderTile, Shader* shaderPlant, char levelNumber);

	int getGridRowsCount();
	int getGridColumnsCount();
	std::vector<std::vector<TileIso>> getGrid();

	void render();
	void initialize();
	void renderTile();
	void renderPlant();
	void growPlant(int x, int y);
	void addPlant(int x, int y, int actualRowPosition, int actualColumnPosition);
};
