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
	Shader* shader;
	glm::mat4 model;
	GLuint VAO;
	GLuint textureId;

public:
	TileIso(int type, GLuint VAO, Shader* shader, GLuint textureId);
	~TileIso();

	int getType();
	glm::mat4 getModel();

	void setType(int type);
	void setModel(glm::mat4 model);
	void setShader(Shader* shader);

	void inicializar();
	void render(glm::mat4 model);
	glm::mat4 translate(int rowIndex, int columnIndex);
};
