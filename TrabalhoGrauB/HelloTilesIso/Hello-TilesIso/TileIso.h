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

	GLuint VAO;
	GLuint textureId;

public:
	TileIso(int type, GLuint VAO, Shader* shader, GLuint textureId);

	~TileIso();

	int getType();

	void setType(int type);
	void setShader(Shader* shader);

	void inicializar();

	void render(glm::mat4 model);
};
