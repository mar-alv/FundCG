#pragma once
#include <vector>
#include "TileIso.h"
#include "GridTypeEnum.h"

class Level
{
private:
	int levelNumber;
	int gridRowsCount;
	int gridColumnCount;

	std::vector<TileIso> tileset;

public:
	Level(Shader* shader, char levelNumber);

	void renderGridMap();

	int getGridRowsCount();
	int getGridColumnCount();
	
	std::vector<TileIso> getTileset();
};
