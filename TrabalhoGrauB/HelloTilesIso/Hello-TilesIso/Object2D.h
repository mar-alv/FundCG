#pragma once
#include "Shader.h"
#include <glm/glm.hpp> 
#include <glad/glad.h>

class Object2D
{
private:
	float angle;

	GLuint VAO;
	GLuint texID;

	Shader shader;

	glm::vec3 scale;
	glm::vec3 position;

	glm::mat4 transform;

public:
	void draw();
	void update();
	void initialize();

	void setAngle(float);

	void setShader(Shader);

	void setTexture(GLuint);

	void setPosition(glm::vec3);
	void setDimensions(glm::vec3);

	void setScale(glm::vec3, bool);
	void setTranslation(glm::vec3, bool);

	void setRotation(float, glm::vec3, bool);
};
