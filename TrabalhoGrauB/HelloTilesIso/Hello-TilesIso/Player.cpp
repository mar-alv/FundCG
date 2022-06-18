#include "Player.h"

int Player::actualDirection = GridDirectionsEnum::CENTER;

Player::Player() {
	this->actualX = 0;
	this->actualY = 0;

	this->texture = Texture();
}

void Player::move() {
	switch (this->actualDirection) {
	case GridDirectionsEnum::NORTH:
		this->actualX--;
		this->actualY--;
		break;
	case GridDirectionsEnum::SOUTH:
		this->actualX++;
		this->actualY++;
		break;
	case GridDirectionsEnum::EAST:
		this->actualX++;
		this->actualY--;
		break;
	case GridDirectionsEnum::WEST:
		this->actualX--;
		this->actualY++;
		break;
	case GridDirectionsEnum::NORTH_EAST:
		this->actualY--;
		break;
	case GridDirectionsEnum::NORTH_WEST:
		this->actualX--;
		break;
	case GridDirectionsEnum::SOUTH_EAST:
		this->actualX++;
		break;
	case GridDirectionsEnum::SOUTH_WEST:
		this->actualY++;
		break;
	}

	this->actualDirection = GridDirectionsEnum::CENTER;
}

void Player::stayInsideGrid(int gridRowsCount, int gridColumnsCount) {
	if (this->actualY < 0) {
		this->actualY = 0;
	}

	if (this->actualX < 0) {
		this->actualX = 0;
	}

	if (actualY > gridRowsCount - 1) {
		this->actualY = gridRowsCount - 1;
	}

	if (actualX > gridColumnsCount - 1) {
		this->actualX = gridColumnsCount - 1;
	}
}

void Player::onMovementKeyPress(int key, int action) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GridDirectionsEnum::NORTH:
			this->actualDirection = GridDirectionsEnum::NORTH;
			break;
		case GridDirectionsEnum::SOUTH:
			this->actualDirection = GridDirectionsEnum::SOUTH;
			break;
		case GridDirectionsEnum::EAST:
			this->actualDirection = GridDirectionsEnum::EAST;
			break;
		case GridDirectionsEnum::WEST:
			this->actualDirection = GridDirectionsEnum::WEST;
			break;
		case GridDirectionsEnum::NORTH_EAST:
			this->actualDirection = GridDirectionsEnum::NORTH_EAST;
			break;
		case GridDirectionsEnum::NORTH_WEST:
			this->actualDirection = GridDirectionsEnum::NORTH_WEST;
			break;
		case GridDirectionsEnum::SOUTH_EAST:
			this->actualDirection = GridDirectionsEnum::SOUTH_EAST;
			break;
		case GridDirectionsEnum::SOUTH_WEST:
			this->actualDirection = GridDirectionsEnum::SOUTH_WEST;
			break;
		}
	}
}

void Player::initializeTexture() {
	this->VAO = this->texture.setup(4, 4);
	this->textureId = this->texture.load(PLAYER_SPRITE_PATH);
}

int iFrame = 2;
int iAnims = 0;
int frameCount = 4;


void Player::render() {
	this->shader->Use();
	const float addaaa = 50.0;

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(400.0 + actualX + addaaa, 100.0 + actualY + addaaa, 0));
	model = glm::scale(model, glm::vec3(200.0, 200.0, 1.0));

	this->shader->setMat4("model", glm::value_ptr(model));

	float offsetx = this->texture.getDX() * iFrame;
	float offsety = this->texture.getDY() * iAnims;

	this->shader->setVec2("offsets", offsetx, offsety);

	iFrame = (iFrame + 1) % frameCount;

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, this->textureId);

	glBindVertexArray(this->VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

int Player::getActualX() {
	return this->actualX;
}

int Player::getActualY() {
	return this->actualY;
}

Texture Player::getTexture() {
	return this->texture;
}

void Player::setShader(Shader* shader) {
	this->shader = shader;
}
