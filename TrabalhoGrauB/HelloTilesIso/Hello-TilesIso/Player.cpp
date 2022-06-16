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

int Player::getActualX() {
	return this->actualX;
}

int Player::getActualY() {
	return this->actualY;
}

Texture Player::getTexture() {
	return this->texture;
}
