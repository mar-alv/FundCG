#include "Player.h"

int Player::actualDirection = GridDirectionsEnum::CENTER;

Player::Player() {
	actualX = 0;
	actualY = 0;

	texture = Texture();
}

void Player::move() {
	switch (actualDirection) {
	case GridDirectionsEnum::NORTH:
		actualX--;
		actualY--;
		break;
	case GridDirectionsEnum::SOUTH:
		actualX++;
		actualY++;
		break;
	case GridDirectionsEnum::EAST:
		actualX++;
		actualY--;
		break;
	case GridDirectionsEnum::WEST:
		actualX--;
		actualY++;
		break;
	case GridDirectionsEnum::NORTH_EAST:
		actualY--;
		break;
	case GridDirectionsEnum::NORTH_WEST:
		actualX--;
		break;
	case GridDirectionsEnum::SOUTH_EAST:
		actualX++;
		break;
	case GridDirectionsEnum::SOUTH_WEST:
		actualY++;
		break;
	}

	actualDirection = GridDirectionsEnum::CENTER;
}

void Player::stayInsideGrid(int gridRowsCount, int gridColumnsCount) {
	if (actualY < 0) {
		actualY = 0;
	}

	if (actualX < 0) {
		actualX = 0;
	}

	if (actualY > gridRowsCount - 1) {
		actualY = gridRowsCount - 1;
	}

	if (actualX > gridColumnsCount - 1) {
		actualX = gridColumnsCount - 1;
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
	VAO = texture.setup(4, 4);
	textureId = texture.load(PLAYER_SPRITE_PATH);
}

int iFrame = 2;
int iAnims = 0;
int frameCount = 4;

void Player::render() {
	float xi = 640 - 64;
	float yi = 80;

	float x = xi + (actualX - actualY) * GRIDS_WIDTH / 2.0;
	float y = yi + (actualX + actualY) * GRIDS_HEIGHT / 2.0;

	shader->Use();

	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(x, y, 0.0));
	model = glm::scale(model, glm::vec3(200.0, 200.0, 1.0));

	shader->setMat4("model", glm::value_ptr(model));

	float offsetx = texture.getDX() * iFrame;
	float offsety = texture.getDY() * iAnims;

	shader->setVec2("offsets", offsetx, offsety);

	iFrame = (iFrame + 1) % frameCount;

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

int Player::getActualX() {
	return actualX;
}

int Player::getActualY() {
	return actualY;
}

Texture Player::getTexture() {
	return texture;
}

void Player::setShader(Shader* shader) {
	this->shader = shader;
}
