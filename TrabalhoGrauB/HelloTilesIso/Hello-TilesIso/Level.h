#pragma once
#include <vector>
#include "TileIso.h"
#include "GridTypeEnum.h"

class Level
{
private:
	int levelNumber;
	int gridRowsCount;
	int gridColumnsCount;

	std::vector<TileIso> tileset;

public:
	Level(Shader* shader, char levelNumber);

	void renderGridMap();

	int getGridRowsCount();
	int getGridColumnsCount();
	
	std::vector<TileIso> getTileset();
};
