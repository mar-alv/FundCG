#include <cmath>
#include <string>
#include <assert.h>
#include <iostream>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

const float PI = 3.14159;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupGeometry();

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "HelloTriangle - Marcelo dos Santos Alvarez!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	Shader shader("../shaders/ortho.vs", "../shaders/ortho.fs");

	GLuint VAO = setupGeometry();

	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);

	glUseProgram(shader.ID);

	glm::mat4 projection = glm::mat4(1);

	// Exercício 1. -10.0, 10.0, -10.0, 10.0, -1.0, 1.0
	// Exercício 2. 0.0, 800.0, 600.0, 0.0, -1.0, 1.0
	// Outros: -1.0, 1.0, -1.0, 1.0, -1.0, 1.0
	projection = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, FALSE, glm::value_ptr(projection));

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		// Exercício 4: width / 2, height / 2, width / 2, height / 2
		glViewport(width / 2, height / 2, width / 2, height / 2);

		glClearColor(0.8, 0.8, 0.8, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		glUniform4f(colorLoc, 0.0, 0.0, 0.0, 1.0);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int setupGeometry()
{
	GLfloat vertices[] = {
		-0.5, 0.0, 0.0, // ESQ
		0.0, 0.5, 0.0,  // CIM
		0.5, 0.0, 0.0,  // DIR
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}
