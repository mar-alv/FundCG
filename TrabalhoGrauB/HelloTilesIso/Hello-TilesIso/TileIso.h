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

	glm::vec4 cor;

	Shader* shader;

public:
	TileIso();
	~TileIso();
	
	void inicializar();

	void draw(glm::mat4 model);
	
	void setCor(glm::vec4 cor);
	
	void setShader(Shader* shader);

	void setCor(float r, float g, float b);
};
