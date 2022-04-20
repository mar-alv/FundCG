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
int setupGeometry3D();

const GLuint WIDTH = 800, HEIGHT = 600;

void renderRedTriangle(GLint colorLoc) {
	glUniform4f(colorLoc, 1.0, 0.0, 0.0, 1.0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void renderTransformedTriangle(int x, int y, GLint colorLoc)
{
	renderRedTriangle(colorLoc);
}

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

	GLuint VAO = setupGeometry3D();

	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");

	assert(colorLoc > -1);

	glUseProgram(shader.ID);

	glm::mat4 projection = glm::mat4(1);
	projection = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, FALSE, glm::value_ptr(projection));
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glClearColor(0.8, 0.8, 0.8, 1.0);

		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);

		glPointSize(20);

		glBindVertexArray(VAO);

		glm::mat4 model = glm::mat4(1);
		GLint modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, FALSE, glm::value_ptr(model));

		renderTransformedTriangle(0, 0, colorLoc);

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
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
= {
		1.0, 0.0, 0.0,
		1.0, 0.2, 0.0,
	2.0, 0.0, 0.0,
		0.0, 0.0, 0.0,



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

int setupGeometry3D()
{
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLfloat vertices[] = {
		//Base da pirâmide: 2 triângulos
		//x    y    z    r    g    b
		-0.5, -0.5, -0.5, 1.0, 1.0, 0.0,
		-0.5, -0.5,  0.5, 0.0, 1.0, 1.0,
		 0.5, -0.5, -0.5, 1.0, 0.0, 1.0,
		 -0.5, -0.5, 0.5, 1.0, 1.0, 0.0,
		  0.5, -0.5,  0.5, 0.0, 1.0, 1.0,
		  0.5, -0.5, -0.5, 1.0, 0.0, 1.0,
		  //
		  -0.5, -0.5, -0.5, 1.0, 1.0, 0.0,
		   0.0,  0.5,  0.0, 1.0, 1.0, 0.0,
		   0.5, -0.5, -0.5, 1.0, 1.0, 0.0,
		  -0.5, -0.5, -0.5, 1.0, 0.0, 1.0,
		   0.0,  0.5,  0.0, 1.0, 0.0, 1.0,
		  -0.5, -0.5,  0.5, 1.0, 0.0, 1.0,
		  -0.5, -0.5, 0.5, 1.0, 1.0, 0.0,
		   0.0,  0.5, 0.0, 1.0, 1.0, 0.0,
		   0.5, -0.5, 0.5, 1.0, 1.0, 0.0,
		   0.5, -0.5, 0.5, 0.0, 1.0, 1.0,
		   0.0,  0.5,  0.0, 0.0, 1.0, 1.0,
		   0.5, -0.5, -0.5, 0.0, 1.0, 1.0,
	};
	GLuint VBO, VAO;
	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);

	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo posição (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Atributo cor (r, g, b)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);
	return VAO;
}
