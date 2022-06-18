#pragma once
#include "Shader.h"
#include "Constants.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TileIso
{
protected:
	int type;

	GLuint VAO;

	Shader* shader;

public:
	TileIso();
	~TileIso();
	
	void inicializar(GLuint testeVAO);

	int getType();

	void setType(int type);
	void setShader(Shader* shader);

	void render(glm::mat4 model, GLuint testeID);
};
