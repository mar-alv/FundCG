#include <cmath>
#include <string>
#include <vector>
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

int setupGeometry3D();

const GLuint WIDTH = 800, HEIGHT = 600;

char viewID = 'W';

glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

float lastX = WIDTH / 2.0;
float lastY = HEIGHT / 2.0;

bool firstTimeMovingMouse = true;

float yaw = -90.0;
float pitch = 0.0;

std::vector <glm::vec3> palette;

enum colors 
{ 
	RED, 
	GREEN, 
	BLUE,
	WHITE
};

enum keyDirections {
	FRONT = 'W',
	BACK = 'S',
	LEFT = 'A',
	RIGHT = 'D',
	TOP = 'E',
	BOTTOM = 'Q',
	EXIT = 'ESC',
};

void initializePaletteVector()
{
	palette[colors::RED] = glm::vec3(1.0, 0.0, 0.0);
	palette[colors::BLUE] = glm::vec3(0.0, 0.0, 1.0);
	palette[colors::GREEN] = glm::vec3(0.0, 1.0, 0.0);
	palette[colors::WHITE] = glm::vec3(1.0, 1.0, 1.0);
}

void processInput(GLFWwindow* window)
{
	float cameraSpeed = 0.005f;

	if (glfwGetKey(window, keyDirections::FRONT) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;

	if (glfwGetKey(window, keyDirections::BACK) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	if (glfwGetKey(window, keyDirections::LEFT) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, keyDirections::RIGHT) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void renderTriangle() {
	glDrawArrays(GL_TRIANGLES, 0, 18);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstTimeMovingMouse)
	{
		lastX = xpos;
		lastY = ypos;

		firstTimeMovingMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(front);
}

int main()
{
	glfwInit();

	initializePaletteVector();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho Grau A - Marcelo dos Santos Alvarez!", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	Shader shader("../shaders/helloCamera.vs", "../shaders/helloCamera.fs");

	GLuint VAO = setupGeometry3D();

	glUseProgram(shader.ID);

	glm::mat4 view = glm::mat4(1);
	glm::mat4 projection = glm::mat4(1);

	view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0) + cameraFront, cameraUp);
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	shader.setMat4("view", glm::value_ptr(view));
	shader.setMat4("projection", glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		processInput(window);

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glClearColor(0.8, 0.8, 0.8, 1.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);

		glPointSize(20);

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		shader.setMat4("view", glm::value_ptr(view));

		glBindVertexArray(VAO);

		glm::mat4 model = glm::mat4(1);
		renderTriangle();
		//model = glm::translate(model, glm::vec3(0.4, 0.0, 0.0));
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0, 1, 0));
		//model = glm::scale(model, glm::vec3(2.0, 2.0, 1.0));
		GLint modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, FALSE, glm::value_ptr(model));

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();

	return 0;
}

int setupGeometry3D()
{
	/*GLfloat matrizCubos[10][10][10];

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int z = 0; z < 10; z++)
			{
				matrizCubos[x][y][z] = palette[colors::WHITE];
			}
		}
	}

	matrizCubos[0][9][5] = colors::RED;*/

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
		  -0.5, -0.5, -0.5,1.0, 1.0, 1.0,
		   0.0,  0.5,  0.0, 1.0, 1.0, 1.0,
		   0.5, -0.5, -0.5,1.0, 1.0, 1.0,
		  -0.5, -0.5, -0.5,1.0, 1.0, 1.0,
		   0.0,  0.5,  0.0, 1.0, 1.0, 1.0,
		  -0.5, -0.5,  0.5, 1.0, 1.0, 1.0,
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

