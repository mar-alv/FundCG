#include "Level.h"

Level::Level(Shader* shader, char levelNumber) {
	this->levelNumber = (int)levelNumber;

	this->shader = shader;

	ifstream file;

	const std::string fileType = ".txt";
	const std::string fileCompletePath = LEVELS_PATH + levelNumber + fileType;

	file.open(fileCompletePath);

	std::string rowCount;
	std::string columnCount;

	file >> rowCount >> columnCount;

	gridRowsCount = stoi(rowCount);
	gridColumnsCount = stoi(columnCount);

	Texture t = Texture();
	GLuint testeVAO = t.setup(1, 1);

	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnsCount; j++) {
			TileIso tile;

			glm::vec4 corDoTile;

			char tileType;

			file >> tileType;

			tile.setShader(shader);

			switch ((int)tileType - '0') {
			case GridTypeEnum::DIRT:
				break;
			case GridTypeEnum::DEEP_WATER:
				break;
			case GridTypeEnum::GRASS:
				break;
			case GridTypeEnum::LAVA:
				break;
			case GridTypeEnum::SAND:
				break;
			case GridTypeEnum::STONE:
				break;
			case GridTypeEnum::WATER:
				break;
			}

			tile.inicializar(testeVAO);
			tileset.push_back(tile);
		}
	}

	file.close();
}

void Level::render() {
	shader->Use();

	float xi = 640 - 64;
	float yi = 80;

	glm::mat4 model;

	int actualGrid = 0;

	Texture t = Texture();
	GLuint testeID = t.load(GRIDS_PATH + "1.png");

	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnsCount; j++) {
			float x = xi + (j - i) * GRIDS_WIDTH / 2.0;
			float y = yi + (j + i) * GRIDS_HEIGHT / 2.0;

			model = glm::mat4();
			model = glm::translate(model, glm::vec3(x, y, 0.0));

			getTileset()[actualGrid].draw(model, testeID);

			actualGrid++;
		}
	}
}

std::vector<TileIso> Level::getTileset() { 
	return tileset; 
}

int Level::getGridRowsCount() {
	return gridRowsCount;
}

int Level::getGridColumnsCount() {
	return gridColumnsCount;
}
