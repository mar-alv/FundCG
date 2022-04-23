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

const int CUBES_PER_ROW = 3;
const int SIZE_PER_CUBE = 36;
const int CUBE_FACES_COUNT = 6;
const GLuint WIDTH = 800, HEIGHT = 600;
const int CUBES_PER_GRID = CUBES_PER_ROW * CUBES_PER_ROW;

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


enum colors {
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

void initializePaletteVector() {
	palette[colors::RED] = glm::vec3(1.0, 0.0, 0.0);
	palette[colors::BLUE] = glm::vec3(0.0, 0.0, 1.0);
	palette[colors::GREEN] = glm::vec3(0.0, 1.0, 0.0);
	palette[colors::WHITE] = glm::vec3(1.0, 1.0, 1.0);
}

void processInput(GLFWwindow* window) {
	float cameraSpeed = 0.005f;

	if (glfwGetKey(window, keyDirections::FRONT) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}

	if (glfwGetKey(window, keyDirections::BACK) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}

	if (glfwGetKey(window, keyDirections::LEFT) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	if (glfwGetKey(window, keyDirections::RIGHT) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void renderCube() {
	glDrawArrays(GL_TRIANGLES, 0, CUBES_PER_GRID * 6 * 4); // por no lugar do 4: CUBE_FACES_COUNT);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
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


int setupCube() {
	float initialBottomTriangleLeftX = 0.0;
	float initialBottomTriangleTopX = 0.0;
	float initialBottomTriangleRightX = 0.1;
	float initialTopTriangleTopX = 0.0;
	float initialTopTriangleRightX = 0.1;
	float initialTopTriangleLeftX = 0.1;

	float initialBottomTriangleLeftY = 0.0;
	float initialBottomTriangleTopY = 0.1;
	float initialBottomTriangleRightY = 0.0;
	float initialTopTriangleTopY = 0.1;
	float initialTopTriangleRightY = 0.1;
	float initialTopTriangleLeftY = 0.0;

	float initialZ = 0.0;

	float bottomTriangleLeftX = initialBottomTriangleLeftX;
	float bottomTriangleLeftY = initialBottomTriangleLeftY;
	float bottomTriangleLeftZ = initialZ;

	float bottomTriangleTopX = initialBottomTriangleTopX;
	float bottomTriangleTopY = initialBottomTriangleTopY;
	float bottomTriangleTopZ = initialZ;

	float bottomTriangleRightX = initialBottomTriangleRightX;
	float bottomTriangleRightY = initialBottomTriangleRightY;
	float bottomTriangleRightZ = initialZ;

	float topTriangleTopX = initialTopTriangleTopX;
	float topTriangleTopY = initialTopTriangleTopY;
	float topTriangleTopZ = initialZ;

	float topTriangleRightX = initialTopTriangleRightX;
	float topTriangleRightY = initialTopTriangleRightY;
	float topTriangleRightZ = initialZ;

	float topTriangleLeftX = initialTopTriangleLeftX;
	float topTriangleLeftY = initialTopTriangleLeftY;
	float topTriangleLeftZ = initialZ;

	GLfloat vertices[(CUBES_PER_GRID * SIZE_PER_CUBE) * 4]; /* No lugar do 2 CUBE_FACES_COUNT */

	float xCount = 0.0;
	int actualIndex = 0;

	for (int actualCube = 1, cubePerRowCounter = 1; actualCube <= CUBES_PER_GRID * 2; actualCube++, cubePerRowCounter++, actualIndex += 36) {
		vertices[actualIndex] = bottomTriangleLeftX;
		vertices[actualIndex + 1] = bottomTriangleLeftY;
		vertices[actualIndex + 2] = bottomTriangleLeftZ;

		vertices[actualIndex + 3] = 1.1;
		vertices[actualIndex + 4] = 1.1;
		vertices[actualIndex + 5] = 1.1;

		vertices[actualIndex + 6] = bottomTriangleTopX;
		vertices[actualIndex + 7] = bottomTriangleTopY;
		vertices[actualIndex + 8] = bottomTriangleTopZ;

		vertices[actualIndex + 9] = 1.1;
		vertices[actualIndex + 10] = 1.1;
		vertices[actualIndex + 11] = 1.1;

		vertices[actualIndex + 12] = bottomTriangleRightX;
		vertices[actualIndex + 13] = bottomTriangleRightY;
		vertices[actualIndex + 14] = bottomTriangleRightZ;

		vertices[actualIndex + 15] = 1.1;
		vertices[actualIndex + 16] = 1.1;
		vertices[actualIndex + 17] = 1.1;

		vertices[actualIndex + 18] = topTriangleTopX;
		vertices[actualIndex + 19] = topTriangleTopY;
		vertices[actualIndex + 20] = topTriangleTopZ;

		vertices[actualIndex + 21] = 1.1;
		vertices[actualIndex + 22] = 1.1;
		vertices[actualIndex + 23] = 1.1;

		vertices[actualIndex + 24] = topTriangleRightX;
		vertices[actualIndex + 25] = topTriangleRightY;
		vertices[actualIndex + 26] = topTriangleRightZ;

		vertices[actualIndex + 27] = 1.1;
		vertices[actualIndex + 28] = 1.1;
		vertices[actualIndex + 29] = 1.1;

		vertices[actualIndex + 30] = topTriangleLeftX;
		vertices[actualIndex + 31] = topTriangleLeftY;
		vertices[actualIndex + 32] = topTriangleLeftZ;

		vertices[actualIndex + 33] = 1.1;
		vertices[actualIndex + 34] = 1.1;
		vertices[actualIndex + 35] = 1.1;

		xCount += 0.04;

		bottomTriangleLeftX += 0.1;
		bottomTriangleTopX += 0.1;
		bottomTriangleRightX += 0.1;

		topTriangleTopX += 0.1;
		topTriangleRightX += 0.1;
		topTriangleLeftX += 0.1;

		if (cubePerRowCounter == CUBES_PER_ROW)
		{
			bottomTriangleLeftY -= 0.1;
			bottomTriangleTopY -= 0.1;
			bottomTriangleRightY -= 0.1;
			topTriangleTopY -= 0.1;
			topTriangleRightY -= 0.1;
			topTriangleLeftY -= 0.1;

			bottomTriangleLeftX = initialBottomTriangleLeftX;
			bottomTriangleTopX = initialBottomTriangleTopX;
			bottomTriangleRightX = initialBottomTriangleRightX;
			topTriangleTopX = initialTopTriangleTopX;
			topTriangleRightX = initialTopTriangleRightX;
			topTriangleLeftX = initialTopTriangleLeftX;

			cubePerRowCounter = 0;
		}

		if (actualCube == CUBES_PER_GRID)
		{
			xCount = 0.3;

			bottomTriangleLeftZ = xCount;
			bottomTriangleTopZ = xCount;
			bottomTriangleRightZ = xCount;
			topTriangleTopZ = xCount;
			topTriangleRightZ = xCount;
			topTriangleLeftZ = xCount;

			bottomTriangleLeftY = initialBottomTriangleLeftY;
			bottomTriangleTopY = initialBottomTriangleTopY;
			bottomTriangleRightY = initialBottomTriangleRightY;
			topTriangleTopY = initialTopTriangleTopY;
			topTriangleRightY = initialTopTriangleRightY;
			topTriangleLeftY = initialTopTriangleLeftY;
		}
	}

	bottomTriangleLeftX = 0.0;
	bottomTriangleLeftY = 0.0;
	bottomTriangleLeftZ = 0.0;

	bottomTriangleTopX = 0.0;
	bottomTriangleTopY = 0.1;
	bottomTriangleTopZ = 0.0;

	bottomTriangleRightX = 0.0;
	bottomTriangleRightY = 0.0;
	bottomTriangleRightZ = 0.1;

	topTriangleTopX = 0.0;
	topTriangleTopY = 0.1;
	topTriangleTopZ = 0.1;

	topTriangleRightX = 0.0;
	topTriangleRightY = 0.0;
	topTriangleRightZ = 0.1;

	topTriangleLeftX = 0.0;
	topTriangleLeftY = 0.1;
	topTriangleLeftZ = 0.0;

	float zCount = 0.0;

	for (int actualCube = 1, cubePerRowCounter = 1; actualCube <= CUBES_PER_GRID * 2; actualCube++, cubePerRowCounter++, actualIndex += 36) {
		vertices[actualIndex] = bottomTriangleLeftX;
		vertices[actualIndex + 1] = bottomTriangleLeftY;
		vertices[actualIndex + 2] = bottomTriangleLeftZ;

		vertices[actualIndex + 3] = 1.1;
		vertices[actualIndex + 4] = 1.1;
		vertices[actualIndex + 5] = 1.1;

		vertices[actualIndex + 6] = bottomTriangleTopX;
		vertices[actualIndex + 7] = bottomTriangleTopY;
		vertices[actualIndex + 8] = bottomTriangleTopZ;

		vertices[actualIndex + 9] = 1.1;
		vertices[actualIndex + 10] = 1.1;
		vertices[actualIndex + 11] = 1.1;

		vertices[actualIndex + 12] = bottomTriangleRightX;
		vertices[actualIndex + 13] = bottomTriangleRightY;
		vertices[actualIndex + 14] = bottomTriangleRightZ;

		vertices[actualIndex + 15] = 1.1;
		vertices[actualIndex + 16] = 1.1;
		vertices[actualIndex + 17] = 1.1;

		vertices[actualIndex + 18] = topTriangleTopX;
		vertices[actualIndex + 19] = topTriangleTopY;
		vertices[actualIndex + 20] = topTriangleTopZ;

		vertices[actualIndex + 21] = 1.1;
		vertices[actualIndex + 22] = 1.1;
		vertices[actualIndex + 23] = 1.1;

		vertices[actualIndex + 24] = topTriangleRightX;
		vertices[actualIndex + 25] = topTriangleRightY;
		vertices[actualIndex + 26] = topTriangleRightZ;

		vertices[actualIndex + 27] = 1.1;
		vertices[actualIndex + 28] = 1.1;
		vertices[actualIndex + 29] = 1.1;

		vertices[actualIndex + 30] = topTriangleLeftX;
		vertices[actualIndex + 31] = topTriangleLeftY;
		vertices[actualIndex + 32] = topTriangleLeftZ;

		vertices[actualIndex + 33] = 1.1;
		vertices[actualIndex + 34] = 1.1;
		vertices[actualIndex + 35] = 1.1;

		bottomTriangleLeftZ += 0.1;
		bottomTriangleTopZ += 0.1;
		bottomTriangleRightZ += 0.1;

		topTriangleTopZ += 0.1;
		topTriangleRightZ += 0.1;
		topTriangleLeftZ += 0.1;

		if (cubePerRowCounter == CUBES_PER_ROW)
		{
			bottomTriangleLeftY -= 0.1;
			bottomTriangleTopY -= 0.1;
			bottomTriangleRightY -= 0.1;
			topTriangleTopY -= 0.1;
			topTriangleRightY -= 0.1;
			topTriangleLeftY -= 0.1;

			bottomTriangleLeftZ = 0.0;
			bottomTriangleTopZ = 0.0;
			bottomTriangleRightZ = 0.1;
			topTriangleTopZ = 0.1;
			topTriangleRightZ = 0.1;
			topTriangleLeftZ = 0.0;

			cubePerRowCounter = 0;
		}

		if (actualCube == CUBES_PER_GRID)
		{
			zCount = 0.3;
		
			bottomTriangleLeftX = zCount;
			bottomTriangleTopX = zCount;
			bottomTriangleRightX = zCount;
			topTriangleTopX = zCount;
			topTriangleRightX = zCount;
			topTriangleLeftX = zCount;

			bottomTriangleLeftY = 0.0;
			bottomTriangleTopY = 0.1;
			bottomTriangleRightY = 0.0;
			topTriangleTopY = 0.1;
			topTriangleRightY = 0.0;
			topTriangleLeftY = 0.1;
		}
	}

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}

int main() {
	glfwInit();

	// initializePaletteVector();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho Grau A - Marcelo dos Santos Alvarez!", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	Shader shader("../shaders/helloCamera.vs", "../shaders/helloCamera.fs");

	GLuint VAO = setupCube();

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
		renderCube();
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
