#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>

using namespace std;

class Texture
{
private:
	GLuint texID;
public:
	Texture();

	Texture(string path);

	GLuint getTextID();

	int loadTexture(string path);
};
