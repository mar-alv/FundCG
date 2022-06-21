#include "Player.h"

int Player::actualDirection = GridDirectionsEnum::CENTER;

Player::Player() {
	actualX = 0.0;
	actualY = 0.0;
	actualRowPosition = 0;
	texture = Texture(4, 4);
	actualColumnPosition = 0;
}

void Player::move() {
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

	updateTexture();

	actualDirection = GridDirectionsEnum::CENTER;
}

void Player::updateTexture() {
	switch (actualDirection) {
	case GridDirectionsEnum::EAST:
	case GridDirectionsEnum::NORTH_EAST:
	case GridDirectionsEnum::SOUTH_EAST:
		texture.setIAnims(PlayerTextureDirectionFacingEnum::RIGHT);
		break;
	case GridDirectionsEnum::WEST:
	case GridDirectionsEnum::SOUTH_WEST:
	case GridDirectionsEnum::NORTH_WEST:
		texture.setIAnims(PlayerTextureDirectionFacingEnum::LEFT);
		break;
	case GridDirectionsEnum::SOUTH:
		texture.setIAnims(PlayerTextureDirectionFacingEnum::BACK);
		break;
	case GridDirectionsEnum::NORTH:
		texture.setIAnims(PlayerTextureDirectionFacingEnum::FRONT);
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

void Player::initializeTexture() {
	VAO = texture.setup();
	textureId = texture.load(PLAYER_SPRITE_PATH);
}

void Player::render() {
	calculateActualPosition();
	updateShader();
	texture.updateActualFrame();

	glBindTexture(GL_TEXTURE_2D, textureId);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
	float offsetx = texture.getDX() * texture.getIFrame();
	float offsety = texture.getDY() * texture.getIAnims();

	shader->setVec2("offsets", offsetx, offsety);
}

int Player::getActualRowPosition() {
	return actualRowPosition;
}

int Player::getActualColumnPosition() {
	return actualColumnPosition;
}

Texture Player::getTexture() {
	return texture;
}

void Player::setShader(Shader* shader) {
	this->shader = shader;
}
