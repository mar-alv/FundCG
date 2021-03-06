#pragma once
#include "Shader.h"
#include "Texture.h"
#include <glad/glad.h>

class Plant
{
private:
	int type;
	GLuint VAO;
	int actualX;
	int actualY;
	bool isFarmed;
	Shader* shader;
	Texture texture;
	glm::mat4 model;
	bool isDestroyed;
	GLuint textureId;
	int actualRowPosition;
	int actualColumnPosition;

public:
	Plant(int actualX, int actualY, int type, Shader* shader, int actualRowPosition, int actualColumnPosition);

	bool getIsFarmed();
	Texture getTexture();
	bool getIsDestroyed();
	float getActualRowPosition();
	float getActualColumnPosition();

	void setIsDestroyed(bool isDestroyed);

	void grow();
	void render();
	void initializeTexture();
	void updateModelOnShader();
	void updateOffsetsOnShader();
};
