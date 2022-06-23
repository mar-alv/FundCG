#include "Player.h"

int Player::actualDirection = GridDirectionsEnum::CENTER;

Player::Player() {
	actualX = 0.0;
	actualY = 0.0;
	actualRowPosition = 0;
	actualColumnPosition = 0;
}

void Player::move() {
	updatePosition();
	updateTextureFrame();

	actualDirection = GridDirectionsEnum::CENTER;
}

void Player::updatePosition() {
	switch (actualDirection) {
	case GridDirectionsEnum::NORTH:
		actualColumnPosition--;
		actualRowPosition--;
		break;
	case GridDirectionsEnum::SOUTH:
		actualColumnPosition++;
		actualRowPosition++;
		break;
	case GridDirectionsEnum::EAST:
		actualColumnPosition++;
		actualRowPosition--;
		break;
	case GridDirectionsEnum::WEST:
		actualColumnPosition--;
		actualRowPosition++;
		break;
	case GridDirectionsEnum::NORTH_EAST:
		actualRowPosition--;
		break;
	case GridDirectionsEnum::NORTH_WEST:
		actualColumnPosition--;
		break;
	case GridDirectionsEnum::SOUTH_EAST:
		actualColumnPosition++;
		break;
	case GridDirectionsEnum::SOUTH_WEST:
		actualRowPosition++;
		break;
	}
}

void Player::updateTextureFrame() {
	switch (actualDirection) {
	case GridDirectionsEnum::EAST:
	case GridDirectionsEnum::NORTH_EAST:
	case GridDirectionsEnum::SOUTH_EAST:
		actualTexture.setIAnims(PlayerTextureDirectionFacingEnum::RIGHT);
		break;
	case GridDirectionsEnum::WEST:
	case GridDirectionsEnum::SOUTH_WEST:
	case GridDirectionsEnum::NORTH_WEST:
		actualTexture.setIAnims(PlayerTextureDirectionFacingEnum::LEFT);
		break;
	case GridDirectionsEnum::SOUTH:
		actualTexture.setIAnims(PlayerTextureDirectionFacingEnum::BACK);
		break;
	case GridDirectionsEnum::NORTH:
		actualTexture.setIAnims(PlayerTextureDirectionFacingEnum::FRONT);
		break;
	}
}

void Player::stayInsideGrid(int gridRowsCount, int gridColumnsCount) {
	if (actualRowPosition < 0) {
		actualRowPosition = 0;
	}
	if (actualColumnPosition < 0) {
		actualColumnPosition = 0;
	}
	if (actualRowPosition > gridRowsCount - 1) {
		actualRowPosition = gridRowsCount - 1;
	}
	if (actualColumnPosition > gridColumnsCount - 1) {
		actualColumnPosition = gridColumnsCount - 1;
	}
}

void Player::onKeyPress(int key, int action) {
	onActionKeyPress(key, action);
	onMovementKeyPress(key, action);
}

void Player::onMovementKeyPress(int key, int action) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GridDirectionsEnum::NORTH:
			actualDirection = GridDirectionsEnum::NORTH;
			break;
		case GridDirectionsEnum::SOUTH:
			actualDirection = GridDirectionsEnum::SOUTH;
			break;
		case GridDirectionsEnum::EAST:
			actualDirection = GridDirectionsEnum::EAST;
			break;
		case GridDirectionsEnum::WEST:
			actualDirection = GridDirectionsEnum::WEST;
			break;
		case GridDirectionsEnum::NORTH_EAST:
			actualDirection = GridDirectionsEnum::NORTH_EAST;
			break;
		case GridDirectionsEnum::NORTH_WEST:
			actualDirection = GridDirectionsEnum::NORTH_WEST;
			break;
		case GridDirectionsEnum::SOUTH_EAST:
			actualDirection = GridDirectionsEnum::SOUTH_EAST;
			break;
		case GridDirectionsEnum::SOUTH_WEST:
			actualDirection = GridDirectionsEnum::SOUTH_WEST;
			break;
		}
	}
}

void Player::onActionKeyPress(int key, int action) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case PlayerActionEnum::ATTACKING:
			attack();
			break;
		case PlayerActionEnum::WATERING_PLANT:
			waterPlant();
			collectWater();
			break;
		}
	}
}

void Player::attack() {
	isAttacking = true;
}

void Player::waterPlant() {
	if (isCarryingWater && actualTileType == GridTypeEnum::DIRT) {
		hasWatered = true;
	}

	isCarryingWater = false;
}

void Player::collectWater() {
	if (actualTileType == GridTypeEnum::WATER) {
		isCarryingWater = true;
	}
}

void Player::initializeTextures() {
	Texture idleTexture = Texture(4, 4, PLAYER_SPRITES_PATH + PLAYER_SPRITE_IDLE_FILE_NAME);
	Texture attackingTexture = Texture(2, 4, PLAYER_SPRITES_PATH + PLAYER_SPRITE_ATTACKING_FILE_NAME);
	Texture wateringPlantTexture = Texture(2, 4, PLAYER_SPRITES_PATH + PLAYER_SPRITE_WATERING_PLANT_FILE_NAME);

	addTexture(idleTexture);
	addTexture(attackingTexture);
	addTexture(wateringPlantTexture);

	actualTexture = idleTexture;
}

void Player::addTexture(Texture texture) {
	textures.push_back(texture);
}

void Player::render() {
	calculateActualPosition();
	update();
	actualTexture.updateActualFrame();

	glBindTexture(GL_TEXTURE_2D, actualTexture.getTextureId());
	glBindVertexArray(actualTexture.getVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Player::update() {
	updateTexture();
	updateShader();
}

void Player::updateTexture() {
	if (isCarryingWater && actualTexture.getTextureId() != textures[2].getTextureId()) {
		actualTexture = textures[2];
	}
	else if (isAttacking && actualTexture.getTextureId() != textures[1].getTextureId()) {
		actualTexture = textures[1];
	}
	else if (!isCarryingWater && !isAttacking && actualTexture.getTextureId() != textures[0].getTextureId()) {
		actualTexture = textures[0];
	}
}

void Player::updateShader() {
	shader->Use();

	updateModelOnShader();
	updateOffsetsOnShader();
}

void Player::calculateActualPosition() {
	actualX = XI + XI / 10.0 + (actualColumnPosition - actualRowPosition) * TILE_WIDTH / 2.0;
	actualY = YI + YI / 6.0 + (actualColumnPosition + actualRowPosition) * TILE_HEIGHT / 2.0;
}

void Player::updateModelOnShader() {
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(actualX, actualY, 0.0));
	model = glm::scale(model, glm::vec3(200.0, 200.0, 1.0));

	shader->setMat4("model", glm::value_ptr(model));
}

void Player::updateOffsetsOnShader() {
	float offsetx = actualTexture.getDX() * actualTexture.getIFrame();
	float offsety = actualTexture.getDY() * actualTexture.getIAnims();

	shader->setVec2("offsets", offsetx, offsety);
}

bool Player::getHasWatered() {
	return hasWatered;
}

int Player::getActualRowPosition() {
	return actualRowPosition;
}

int Player::getActualColumnPosition() {
	return actualColumnPosition;
}

Texture Player::getActualTexture() {
	return actualTexture;
}

void Player::setShader(Shader* shader) {
	this->shader = shader;
}

void Player::setHasWatered(bool hasWatered) {
	this->hasWatered = hasWatered;
}

void Player::setActualTileType(int actualTileType) {
	this->actualTileType = actualTileType;
}
