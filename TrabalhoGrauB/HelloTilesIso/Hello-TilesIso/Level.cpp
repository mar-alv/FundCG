#include "Level.h"

Level::Level(Shader* shader, char levelNumber) {
	this->shader = shader;
	this->levelNumber = (int)levelNumber;

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
			tile.inicializar(testeVAO);

			tile.setType((int)tileType - '0');

			switch ((int)tileType - '0') {
			case GridTypeEnum::DIRT:
				break;
			case GridTypeEnum::DEEP_WATER:
				//tile.setType(GridTypeEnum::DEEP_WATER);
				break;
			case GridTypeEnum::GRASS:
				//tile.setType(GridTypeEnum::GRASS);
				break;
			case GridTypeEnum::LAVA:
				//tile.setType(GridTypeEnum::LAVA);
				break;
			case GridTypeEnum::SAND:
				//tile.setType(GridTypeEnum::SAND);
				break;
			case GridTypeEnum::STONE:
				//tile.setType(GridTypeEnum::STONE);
				break;
			case GridTypeEnum::WATER:
				//tile.setType(GridTypeEnum::WATER);
				break;
			}

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

	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnsCount; j++) {
			float x = xi + (j - i) * GRIDS_WIDTH / 2.0;
			float y = yi + (j + i) * GRIDS_HEIGHT / 2.0;

			const std::string tilePath = GRIDS_PATH + std::to_string(tileset[actualGrid].getType()) + ".png";

			std::cout << tilePath << std::endl;

			GLuint testeID = t.load(tilePath);

			model = glm::mat4();
			model = glm::translate(model, glm::vec3(x, y, 0.0));

			getTileset()[actualGrid].render(model, testeID);

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
