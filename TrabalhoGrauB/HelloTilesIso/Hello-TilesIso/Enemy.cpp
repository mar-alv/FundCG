#include "Enemy.h"

Enemy::Enemy(Shader* shader) {
	actualX = 0.0;
	actualY = 0.0;
	this->shader = shader;
	actualRowPosition = 2;
	actualColumnPosition = 2;
	this->texture = Texture(2, 1);

	initializeTexture();
}

void Enemy::initializeTexture() {
	VAO = texture.setup();
	textureId = texture.load(COW_SPRITE_PATH);
}

void Enemy::move() {
	updatePosition();
}

void Enemy::updatePosition() {
	int range = 9 - 1 + 1;
	int num = rand() % range + 1;

	std::cout << num << std::endl;

	std::cout << "Antes: " << actualRowPosition << "/" << actualColumnPosition << std::endl;

	switch (num) {
	case EnemyGridDirectionsEnum::ENEMY_NORTH:
		actualColumnPosition--;
		actualRowPosition--;
		break;
	case EnemyGridDirectionsEnum::ENEMY_SOUTH:
		actualColumnPosition++;
		actualRowPosition++;
		break;
	case EnemyGridDirectionsEnum::ENEMY_EAST:
		actualColumnPosition++;
		actualRowPosition--;
		break;
	case EnemyGridDirectionsEnum::ENEMY_WEST:
		actualColumnPosition--;
		actualRowPosition++;
		break;
	case EnemyGridDirectionsEnum::ENEMY_NORTH_EAST:
		actualRowPosition--;
		break;
	case EnemyGridDirectionsEnum::ENEMY_NORTH_WEST:
		actualColumnPosition--;
		break;
	case EnemyGridDirectionsEnum::ENEMY_SOUTH_EAST:
		actualColumnPosition++;
		break;
	case EnemyGridDirectionsEnum::ENEMY_SOUTH_WEST:
		actualRowPosition++;
		break;
	}

	std::cout << "Depois: " << actualRowPosition << "/" << actualColumnPosition << std::endl;
}

void Enemy::stayInsideGrid(int gridRowsCount, int gridColumnsCount) {
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

void Enemy::attack() {
	//isAttacking = true;
}

void Enemy::render() {
	calculateActualPosition();
	update();
	texture.updateActualFrame();

	glBindTexture(GL_TEXTURE_2D, textureId);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Enemy::update() {
	updateShader();
}

void Enemy::updateShader() {
	shader->Use();

	updateModelOnShader();
	updateOffsetsOnShader();
}

void Enemy::calculateActualPosition() {
	actualX = XI + XI / 10.0 + (actualColumnPosition - actualRowPosition) * TILE_WIDTH / 2.0;
	actualY = YI + YI / 6.0 + (actualColumnPosition + actualRowPosition) * TILE_HEIGHT / 2.0;
}

void Enemy::updateModelOnShader() {
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(actualX, actualY, 0.0));
	model = glm::scale(model, glm::vec3(100.0, 100.0, 1.0));

	shader->setMat4("model", glm::value_ptr(model));
}

void Enemy::updateOffsetsOnShader() {
	float offsetx = texture.getDX() * texture.getIFrame();
	float offsety = texture.getDY() * texture.getIAnims();

	shader->setVec2("offsets", offsetx, offsety);
}

int Enemy::getActualRowPosition() {
	return actualRowPosition;
}

int Enemy::getActualColumnPosition() {
	return actualColumnPosition;
}

void Enemy::setActualTileType(int actualTileType) {
	this->actualTileType = actualTileType;
}
