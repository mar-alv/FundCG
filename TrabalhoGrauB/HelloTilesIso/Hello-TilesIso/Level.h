#pragma once
#include <vector>
#include "Texture.h"
#include "TileIso.h"
#include "GridTypeEnum.h"

class Level
{
private:
	int levelNumber;
	int gridRowsCount;
	int gridColumnsCount;

	Shader* shader;

	std::vector<TileIso> tileset;

public:
	Level(Shader* shader, char levelNumber);

	void renderGridMap();

	int getGridRowsCount();
	int getGridColumnsCount();
	
	std::vector<TileIso> getTileset();
};
