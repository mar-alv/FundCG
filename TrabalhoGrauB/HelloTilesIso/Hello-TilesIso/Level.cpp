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
	int range = 1 - 0 + 1;
	int num = rand() % range + 0;
	int plantType;

	switch (num) {
	case PlantTypeEnum::BERRY:
		plantType = PlantTypeEnum::BERRY;
		break;
	case PlantTypeEnum::WHEAT:
		plantType = PlantTypeEnum::WHEAT;
		break;
	}

	Plant plant = Plant(x, y, plantType, shaderPlant, actualRowPosition, actualColumnPosition);

	plant.initializeTexture();

	plants.push_back(plant);
}

void Level::render() {
	renderTiles();
	renderPlants();
	renderEnemies();
}

void Level::renderTiles() {
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

void Level::renderPlants() {
	shaderPlant->Use();

	for (int i = 0; i < plants.size(); i++) {
		if (!plants[i].getIsFarmed() && !plants[i].getIsDestroyed()) {
			plants[i].render();
		}
	}
}

void Level::renderEnemies() {
	shaderPlant->Use();

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].render();
	}
}

void Level::spawnEnemy() {
	Enemy enemy = Enemy(shaderPlant);

	enemies.push_back(enemy);
}

void Level::makeEnemiesMoveOrAttack() {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].getActualTileType() != GridTypeEnum::DIRT) {
			enemies[i].move();
			enemies[i].stayInsideGrid(gridRowsCount, gridColumnsCount);
		}
		else {
			for (int j = 0; j < plants.size(); j++) {
				if (plants[j].getActualRowPosition() == enemies[i].getActualRowPosition() && plants[j].getActualColumnPosition() == enemies[i].getActualColumnPosition()) {
					if (!plants[j].getIsFarmed() && !plants[j].getIsDestroyed()) {
						enemies[i].attack(plants[j]);

						plants[j].getTexture().setIFrame();
						
						if (plants[j].getTexture().getIFrame() <= 0) {
							plants[j].setIsDestroyed(true);
						}
					}
					else if (plants[j].getIsDestroyed() || plants[j].getIsFarmed()) {
						enemies[i].move();
						enemies[i].stayInsideGrid(gridRowsCount, gridColumnsCount);
					}
				}
			}
		}
	}
}

bool Level::checkIfPlayerWon() {
	int farmedPlantsCounter = 0;

	for (int i = 0; i < plants.size(); i++) {
		if (plants[i].getIsFarmed()) {
			farmedPlantsCounter++;
		}
	}

	if (farmedPlantsCounter >= plants.size() / 2) {
		return true;
	}

	return false;
}

bool Level::checkIfPlayerLost() {
	int destroyedPlantsCounter = 0;

	for (int i = 0; i < plants.size(); i++) {
		if (plants[i].getIsDestroyed()) {
			destroyedPlantsCounter++;
		}
	}

	if (destroyedPlantsCounter >= plants.size() / 2) {
		return true;
	}

	return false;

}

void Level::killEnemy(int playerX, int playerY) {
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		if (it->getActualRowPosition() == playerX && it->getActualColumnPosition() == playerY) {
			enemies.erase(it);
			
			break;
		}
	}
}

void Level::updateEnemyActualTileType() {
	for (int i = 0; i < gridRowsCount; i++) {
		for (int j = 0; j < gridColumnsCount; j++) {
			for (int k = 0; k < enemies.size(); k++) {
				if (enemies[k].getActualRowPosition() == i && enemies[k].getActualColumnPosition() == j) {
					enemies[k].setActualTileType(grid[i][j].getType());
				}
			}
		}
	}
}

void Level::growPlant(int x, int y) {
	for (std::vector<Plant>::iterator it = plants.begin(); it != plants.end(); it++) {
		if (it->getActualColumnPosition() == x && it->getActualRowPosition() == y) {
			if (!it->getIsFarmed() && !it->getIsDestroyed()) {
				it->grow();
			}
			
			if (it->getIsFarmed()) {
				Texture texture = Texture();

				const std::string gridTexturePath = GRIDS_SPRITES_PATH + "0" + TEXTURE_FILE_FORMAT;

				GLuint textureId = texture.load(gridTexturePath);

				grid[it->getActualColumnPosition()][it->getActualRowPosition()].setTextureId(textureId);

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
