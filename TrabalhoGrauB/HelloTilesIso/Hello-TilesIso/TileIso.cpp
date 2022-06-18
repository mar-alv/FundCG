#include "TileIso.h"

TileIso::TileIso() { }
TileIso::~TileIso() { }

void TileIso::inicializar(GLuint testeVAO) {
	float vertices[] = {
		0.0, GRIDS_HEIGHT / 2.0, 0.0,               0.0,0.5,
		GRIDS_WIDTH / 2.0, GRIDS_HEIGHT, 0.0,         0.5,1.0,
		GRIDS_WIDTH, GRIDS_HEIGHT / 2.0, 0.0,          1.0,0.5,
		GRIDS_WIDTH / 2.0, 0.0, 0.0,                 0.5,0.0,
	}; 

	int indices[] = {
		0, 1 , 3,
		1, 2,  3,
	};

	GLuint VBO, EBO;

	glGenVertexArrays(1, &testeVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(testeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	this->VAO = testeVAO;
}

void TileIso::draw(glm::mat4 model, GLuint testeID) {
	shader->Use();

	// Pegando a localização do uniform em que passaremos a matriz de transformação/modelo
	GLint modelLoc = glGetUniformLocation(shader->ID, "model");

	// Passando para o shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// vinculando a textura
	glBindTexture(GL_TEXTURE_2D, testeID);
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture1"), 0);

	// Chama o shader
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TileIso::setShader(Shader* shader) {
	this->shader = shader;
}
