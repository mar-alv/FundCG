#include "Plant.h"
#include "Constants.h"

Plant::Plant(int actualX, int actualY, int type, Shader* shader) {
	this->type = type;
	this->shader = shader;
	this->actualX = actualX;
	this->actualY = actualY;
	this->texture = Texture(5, 1);
}

void Plant::initializeTexture() {
	const std::string fileCompletePath = PLANT_SPRITES_PATH + std::to_string(type) + TEXTURE_FILE_FORMAT;

	VAO = texture.setup();
	textureId = texture.load(fileCompletePath);
}

void Plant::render() {
	updateModelOnShader();
	updateOffsetsOnShader();
	//texture.updateActualFrame();

	glBindTexture(GL_TEXTURE_2D, textureId);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Plant::updateModelOnShader() {
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(actualX, actualY, 0.0));
	model = glm::scale(model, glm::vec3(TILE_WIDTH, TILE_HEIGHT, 1.0));

	shader->setMat4("model", glm::value_ptr(model));
}

void Plant::updateOffsetsOnShader() {
	float offsetx = texture.getDX() * texture.getIFrame();
	float offsety = texture.getDY() * texture.getIAnims();

	shader->setVec2("offsets", offsetx, offsety);
}
