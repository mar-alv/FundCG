#include "Level.h"

glm::vec4 normalizaRGB(glm::vec4 byteColor) {
	glm::vec4 normColor(byteColor.r / 255.0, byteColor.g / 255.0, byteColor.b / 255.0, byteColor.a / 255.0);

	return normColor;
}

Level::Level(Shader* shader, char levelNumber) {
	this->levelNumber = (int)levelNumber;

	ifstream file;

	const std::string fileType = ".txt";
	const std::string fileCompletePath = LEVELS_PATH + levelNumber + fileType;

	file.open(fileCompletePath);

	std::string rowCount;
	std::string columnCount;

	file >> rowCount >> columnCount;

	this->gridRowsCount = stoi(rowCount);
	this->gridColumnCount = stoi(columnCount);

	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnCount; j++) {
			TileIso tile;

			glm::vec4 corDoTile;

			char tileType;

			file >> tileType;

			tile.setShader(shader);

			switch ((int)tileType - '0') {
			case GridTypeEnum::DIRT:
				corDoTile.r = 155; corDoTile.g = 118; corDoTile.b = 83; corDoTile.a = 255;
				break;
			case GridTypeEnum::DEEP_WATER:
				corDoTile.r = 31; corDoTile.g = 78; corDoTile.b = 120; corDoTile.a = 255;
				break;
			case GridTypeEnum::GRASS:
				corDoTile.r = 0; corDoTile.g = 176; corDoTile.b = 80; corDoTile.a = 255;
				break;
			case GridTypeEnum::LAVA:
				corDoTile.r = 191; corDoTile.g = 143; corDoTile.b = 0; corDoTile.a = 255;
				break;
			case GridTypeEnum::SAND:
				corDoTile.r = 128; corDoTile.g = 96; corDoTile.b = 0; corDoTile.a = 255;
				break;
			case GridTypeEnum::STONE:
				corDoTile.r = 191; corDoTile.g = 191; corDoTile.b = 191; corDoTile.a = 255;
				break;
			case GridTypeEnum::WATER:
				corDoTile.r = 198; corDoTile.g = 89; corDoTile.b = 17; corDoTile.a = 255;
				break;
			}

			tile.setCor(normalizaRGB(corDoTile));
			tile.inicializar();
			tileset.push_back(tile);
		}
	}

	file.close();
}

void Level::renderGridMap() {
	float xi = 368;
	float yi = 100;

	glm::mat4 model;

	int actualGrid = 0;

	for (int i = 0; i < gridRowsCount; i++)
	{
		for (int j = 0; j < gridColumnCount; j++)
		{
			float x = xi + (j - i) * GRIDS_WIDTH / 2.0;
			float y = yi + (j + i) * GRIDS_HEIGHT / 2.0;

			model = glm::mat4();
			model = glm::translate(model, glm::vec3(x, y, 0.0));

			getTileset()[actualGrid].draw(model);

			actualGrid++;
		}
	}
}

std::vector<TileIso> Level::getTileset() { 
	return this->tileset; 
}

int Level::getGridRowsCount() {
	return this->gridRowsCount;
}

int Level::getGridColumnCount() {
	return this->gridColumnCount;
}
