#include "Level.h"

Level::Level(Shader* shader, char levelNumber) {
	this->shader = shader;
	this->levelNumber = (int)levelNumber;

	initialize();
}

void Level::initialize() {
	ifstream levelFile;

	const std::string tileFileFormat = ".png";
	const std::string levelFileFormat = ".txt";
	const std::string fileCompletePath = LEVELS_PATH + std::to_string(levelNumber - '0') + levelFileFormat;

	levelFile.open(fileCompletePath);

	std::string rowCount;
	std::string columnCount;

	levelFile >> rowCount >> columnCount;

	gridRowsCount = stoi(rowCount);
	gridColumnsCount = stoi(columnCount);

	Texture texture = Texture();

	GLuint VAO = texture.setup(1, 1);

	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnsCount; j++) {
			char tileType;

			levelFile >> tileType;

			const std::string gridTexturePath = GRIDS_PATH + tileType + tileFileFormat;

			GLuint textureId = texture.load(gridTexturePath);

			TileIso tile = TileIso((int)tileType - '0', VAO, shader, textureId);

			tile.inicializar();

			grid.push_back(tile);
		}
	}

	levelFile.close();
}

void Level::render() {
	shader->Use();

	glm::mat4 model;

	int actualGrid = 0;

	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnsCount; j++) {
			getGrid()[actualGrid].setModel(model);
			
			model = getGrid()[actualGrid].translate(i, j);
			
			getGrid()[actualGrid].render(model);

			actualGrid++;
		}
	}
}

std::vector<TileIso> Level::getGrid() { 
	return grid;
}

int Level::getGridRowsCount() {
	return gridRowsCount;
}

int Level::getGridColumnsCount() {
	return gridColumnsCount;
}
