#include <iostream>
#include <string>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <cmath>

using namespace std;

const float PI = 3.14159;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupGeometry();
int createCircle(float radius, int nPoints);

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

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader shader("../shaders/hello.vs", "../shaders/hello.fs");

	// Exercício 6.0: 0.5,100
	// Exercício 6.a: 0.5,8
	// Exercício 6.b: 0.5,5
	GLuint VAO = createCircle(0.5, 5);

	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);

	glUseProgram(shader.ID);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(VAO);

		// Exercício 6   -   Círculo: 0.5,102
		// Exercício 6.a -  Octágono: 0.5,10
		// Exercício 6.b - Pentágono: 0.5,7
		glDrawArrays(GL_TRIANGLE_FAN, 0, 7);

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
		0.0, -0.4, 0.0, // ESQ
		0.8, -0.4, 0.0, // DIR
		0.0, 0.4, 0.0,  // CIM

		0.8, -0.4, 0.0, // DIR
		0.8, 0.4, 0.0,  // CIM
		0.0, 0.4, 0.0,  // ESQ
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

int createCircle(float radius, int nPoints)
{
	float* vertices;

	const int totalSize = (nPoints + 2) * 3;

	vertices = new float[totalSize];

	vertices[0] = 0.0; // x
	vertices[1] = 0.0; // y
	vertices[2] = 0.0; // z

	float angle = 0.0f;

	const float maxAngle = 2 * PI;

	const float slice = maxAngle / (float)(nPoints);

	int i = 3;

	const float z = 0.0;

	while (i < totalSize)
	{
		float x = radius * cos(angle);
		float y = radius * sin(angle);

		vertices[i] = x;
		vertices[i + 1] = y;
		vertices[i + 2] = z;

		i += 3;

		angle += slice;
	}

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, totalSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}
