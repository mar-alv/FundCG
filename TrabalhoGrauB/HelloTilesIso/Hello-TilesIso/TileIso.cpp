#include "TileIso.h"

TileIso::TileIso(int type, GLuint VAO, Shader* shader, GLuint textureId) {
	this->type = type;
	this->VAO = VAO;
	this->shader = shader;
	this->textureId = textureId;
}

TileIso::~TileIso() { }

void TileIso::inicializar() {
	GLuint VBO, EBO;

	float vertices[] = {
		0.0, TILE_HEIGHT / 2.0, 0.0, 0.0, 0.5,
		TILE_WIDTH / 2.0, TILE_HEIGHT, 0.0, 0.5, 1.0,
		TILE_WIDTH, TILE_HEIGHT / 2.0, 0.0, 1.0, 0.5,
		TILE_WIDTH / 2.0, 0.0, 0.0, 0.5, 0.0
	};

	int indices[] = {
		0, 1 , 3,
		1, 2,  3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void TileIso::render(glm::mat4 model) {
	shader->Use();

	GLint modelLoc = glGetUniformLocation(shader->ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindTexture(GL_TEXTURE_2D, textureId);
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture1"), 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int TileIso::getType() {
	return type;
}

void TileIso::setType(int type) {
	this->type = type;
}

void TileIso::setShader(Shader* shader) {
	this->shader = shader;
}
