#include "Level.h"

Level::Level(Shader* shader, char levelNumber) {
	this->shader = shader;
	this->levelNumber = (int)levelNumber;

	ifstream levelFile;

	const std::string tileFileFormat = ".png";
	const std::string levelFileFormat = ".txt";
	const std::string fileCompletePath = LEVELS_PATH + levelNumber + levelFileFormat;

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

			tileset.push_back(tile);
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
			model = translateTileModel(model, i, j);

			getTileset()[actualGrid].render(model);

			actualGrid++;
		}
	}
}

glm::mat4 Level::translateTileModel(glm::mat4 model, int rowIndex, int columnIndex) {
	float x = XI + (columnIndex - rowIndex) * TILE_WIDTH / 2.0;
	float y = YI + (columnIndex + rowIndex) * TILE_HEIGHT / 2.0;

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(x, y, 0.0));

	return model;
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
