#include "Texture.h"

Texture::Texture() {
}

Texture::Texture(float framesCount, float animationsCount) {
	this->dx = 0;
	this->dy = 0;
	this->iFrame = 0;
	this->iAnims = 0;
	this->framesCount = framesCount;
	this->animationsCount = animationsCount;
}

Texture::Texture(float framesCount, float animationsCount, std::string filePath) {
	this->dx = 0;
	this->dy = 0;
	this->iFrame = 0;
	this->iAnims = 0;
	this->framesCount = framesCount;
	this->animationsCount = animationsCount;

	initializeTextureIdAndVAO(filePath);
}

void Texture::initializeTextureIdAndVAO(std::string filePath) {
	VAO = setup();
	textureId = load(filePath);
}

float Texture::getDX() {
	return dx;
}

float Texture::getDY() {
	return dy;
}

int Texture::getIFrame() {
	return iFrame;
}

int Texture::getIAnims() {
	return iAnims;
}

GLuint Texture::getVAO() {
	return VAO;
}

GLuint Texture::getTextureId() {
	return textureId;
}

void Texture::setIAnims(int iAnims) {
	this->iAnims = iAnims;
}

int Texture::load(std::string path) {
	GLuint texID;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

int Texture::setup() {
	GLuint VAO;
	GLuint VBO, EBO;

	dx = 1.0 / framesCount;
	dy = 1.0 / animationsCount;

	float vertices[] = {
		// posicoes          // cores          // coordenadas de textura
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   dx, dy, // superior direito
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   dx, 0.0f, // inferior direito
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // inferior esquerdo
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, dy  // superior esquerdo
	};

	unsigned int indices[] = {
	0, 1, 3, // primeiro triangulo
	1, 2, 3  // segundo triangulo
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Primeiro atributo - Layout 0 - posição - 3 valores - x, y, z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Segundo atributo - Layout 1 - cor - 3 valores - r, g, b
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Terceiro atributo - Layout 2 - coordenadas de textura - 2 valores - s, t (ou u, v)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	return VAO;
}

void Texture::updateActualFrame() {
	iFrame = (iFrame + 1) % (int)framesCount;
}
