#include "Level.h"
#include "GridTypeEnum.h"

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

	Texture texture = Texture(1, 1);

	GLuint VAO = texture.setup();

	for (int i = 0; i < gridRowsCount; i++) {
		std::vector<TileIso> temporaryGrid;

		for (int j = 0; j < gridColumnsCount; j++) {
			char tileType;

			levelFile >> tileType;

			const std::string gridTexturePath = GRIDS_SPRITES_PATH + tileType + tileFileFormat;

			GLuint textureId = texture.load(gridTexturePath);

			TileIso tile = TileIso((int)tileType - '0', VAO, shader, textureId);

			tile.inicializar();

			temporaryGrid.push_back(tile);
		}
		grid.push_back(temporaryGrid);
	}

	levelFile.close();
}

void Level::render() {
	shader->Use();

	glm::mat4 model;

	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnsCount; j++) {
			getGrid()[i][j].setModel(model);
			
			model = getGrid()[i][j].translate(i, j);
			
			getGrid()[i][j].render(model);
		}
	}
}

std::vector<std::vector<TileIso>> Level::getGrid() {
	return grid;
}

int Level::getGridRowsCount() {
	return gridRowsCount;
}

int Level::getGridColumnsCount() {
	return gridColumnsCount;
}
