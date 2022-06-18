#pragma once
#include <vector>
#include "Texture.h"
#include "TileIso.h"
#include "GridTypeEnum.h"

class Level
{
private:
	Shader* shader;
	int levelNumber;
	int gridRowsCount;
	int gridColumnsCount;
	std::vector<TileIso> grid;

public:
	Level(Shader* shader, char levelNumber);

	int getGridRowsCount();
	int getGridColumnsCount();
	std::vector<TileIso> getGrid();

	void render();
	void initialize();
};
