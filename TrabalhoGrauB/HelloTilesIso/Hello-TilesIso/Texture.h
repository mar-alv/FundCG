#pragma once
#include <iostream>
#include "stb_image.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Texture
{
private:
	float dx;
	float dy;
	int iFrame;
	int iAnims;
	GLuint VAO;
	GLuint textureId;
	float framesCount;
	float animationsCount;

public:
	Texture();
	Texture(float framesCount, float animationsCount);

	float getDX();
	float getDY();
	int getIFrame();
	int getIAnims();
	GLuint getVAO();
	GLuint getTextureId();

	void setIAnims(int iAnims);

	int setup();
	void updateActualFrame();
	int load(std::string path);
	void initializeTextureIdAndVAO(std::string filePath);
};
