#include "Level.h"

Level::Level(Shader* shaderTile, Shader* shaderPlant, char levelNumber) {
	this->shaderTile = shaderTile;
	this->shaderPlant = shaderPlant;
	this->levelNumber = (int)levelNumber;

	initialize();
}

void Level::initialize() {
	ifstream levelFile;

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

			const std::string gridTexturePath = GRIDS_SPRITES_PATH + tileType + TEXTURE_FILE_FORMAT;

			GLuint textureId = texture.load(gridTexturePath);

			TileIso tile = TileIso((int)tileType - '0', VAO, shaderTile, textureId);

			if (tile.getType() == GridTypeEnum::DIRT) {
				float x = XI + XI / 6.0 + (j - i) * TILE_WIDTH / 2.0;
				float y = YI + (j + i) * TILE_HEIGHT / 2.0;

				addPlant(x, y, i, j);
			}

			tile.inicializar();

			temporaryGrid.push_back(tile);
		}
		grid.push_back(temporaryGrid);
	}

	levelFile.close();
}

void Level::addPlant(int x, int y, int actualRowPosition, int actualColumnPosition) {
	Plant plant = Plant(x, y, PlantTypeEnum::BERRY, shaderPlant, actualRowPosition, actualColumnPosition);

	plant.initializeTexture();

	plants.push_back(plant);
}

void Level::render() {
	renderTile();
	renderPlant();
}

void Level::renderTile() {
	shaderTile->Use();

	glm::mat4 model;

	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnsCount; j++) {
			getGrid()[i][j].setModel(model);

			model = getGrid()[i][j].translate(i, j);

			getGrid()[i][j].render(model);
		}
	}

}

void Level::renderPlant() {
	shaderPlant->Use();

	for (int i = 0; i < plants.size(); i++) {
		plants[i].render();
	}
}

void Level::growPlant(int x, int y) {
	for (std::vector<Plant>::iterator it = plants.begin(); it != plants.end(); it++) {
		if (it->getActualColumnPosition() == x && it->getActualRowPosition() == y) {
			if (!it->getIsFarmed()) {
				it->grow();
			}
			else {
				plants.erase(it);
				break;
			}
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
