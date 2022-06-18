#pragma once
#include "Shader.h"
#include "Constants.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TileIso
{
protected:
	GLuint VAO;

	Shader* shader;

public:
	TileIso();
	~TileIso();
	
	void inicializar(GLuint testeVAO);

	void setShader(Shader* shader);

	void draw(glm::mat4 model, GLuint testeID);
};
