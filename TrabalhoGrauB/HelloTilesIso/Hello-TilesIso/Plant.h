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
	Shader* shader;
	Texture texture;
	glm::mat4 model;
	GLuint textureId;
	int actualRowPosition;
	int actualColumnPosition;

public:
	Plant(int actualX, int actualY, int type, Shader* shader, int actualRowPosition, int actualColumnPosition);

	float getActualRowPosition();
	float getActualColumnPosition();

	void grow();
	void render();
	void initializeTexture();
	void updateModelOnShader();
	void updateOffsetsOnShader();
};
