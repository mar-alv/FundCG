#pragma once

#include <iostream>
#include "stb_image.h"
#include <glad/glad.h>

class Sprite
{
private:
	float dx, dy;

public:
	Sprite();

	float getDX();
	float getDY();

	int load(std::string path);
	int setup(float nFrames, float nAnims);
};
