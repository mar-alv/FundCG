#pragma once

#include <iostream>
#include "stb_image.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Texture
{
private:
	float dx, dy;

public:
	Texture();

	float getDX();
	float getDY();

	int load(std::string path);
	int setup(float nFrames, float nAnims);
};
