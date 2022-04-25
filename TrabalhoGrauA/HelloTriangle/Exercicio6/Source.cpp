#include <cmath>
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>
#include "Shader.h"
#include <iterator>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"

using namespace std;

const int GRID_SIZE = 3;
const int SIZE_PER_CUBE = 216;
const GLuint WIDTH = 800, HEIGHT = 600;
const int POINTS_PER_SQUARE = SIZE_PER_CUBE / 6;
const int CUBES_PER_GRID = GRID_SIZE * GRID_SIZE;
const int TOTAL_CUBES = GRID_SIZE * GRID_SIZE * GRID_SIZE;
const int TOTAL_VERTICES_SIZE = SIZE_PER_CUBE * TOTAL_CUBES;

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

void renderCubes() {
	glDrawArrays(GL_TRIANGLES, 0, TOTAL_CUBES * POINTS_PER_SQUARE);
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

Cube initializateCube() {
	Point frontBottomTriangleTopPoint = Point(0.0, 0.1, 0.0);
	Point frontBottomTriangleLeftPoint = Point(0.0, 0.0, 0.0);
	Point frontBottomTriangleRightPoint = Point(0.1, 0.0, 0.0);
	Triangle frontBottomTriangle = Triangle(frontBottomTriangleTopPoint, frontBottomTriangleLeftPoint, frontBottomTriangleRightPoint);

	Point frontTopTriangleTopPoint = Point(0.1, 0.1, 0.0);
	Point frontTopTriangleLeftPoint = Point(0.0, 0.1, 0.0);
	Point frontTopTriangleRightPoint = Point(0.1, 0.0, 0.0);
	Triangle frontTopTriangle = Triangle(frontTopTriangleTopPoint, frontTopTriangleLeftPoint, frontTopTriangleRightPoint);

	Square frontSquare = Square(frontTopTriangle, frontBottomTriangle);

	Point backBottomTriangleTopPoint = Point(0.0, 0.1, 0.1);
	Point backBottomTriangleLeftPoint = Point(0.0, 0.0, 0.1);
	Point backBottomTriangleRightPoint = Point(0.1, 0.0, 0.1);
	Triangle backBottomTriangle = Triangle(backBottomTriangleTopPoint, backBottomTriangleLeftPoint, backBottomTriangleRightPoint);

	Point backTopTriangleTopPoint = Point(0.1, 0.1, 0.1);
	Point backTopTriangleLeftPoint = Point(0.0, 0.1, 0.1);
	Point backTopTriangleRightPoint = Point(0.1, 0.0, 0.1);
	Triangle backTopTriangle = Triangle(backTopTriangleTopPoint, backTopTriangleLeftPoint, backTopTriangleRightPoint);

	Square backSquare = Square(backTopTriangle, backBottomTriangle);

	Point leftBottomTriangleTopPoint = Point(0.0, 0.1, 0.0);
	Point leftBottomTriangleLeftPoint = Point(0.0, 0.0, 0.0);
	Point leftBottomTriangleRightPoint = Point(0.0, 0.0, 0.1);
	Triangle leftBottomTriangle = Triangle(leftBottomTriangleTopPoint, leftBottomTriangleLeftPoint, leftBottomTriangleRightPoint);

	Point leftTopTriangleTopPoint = Point(0.0, 0.1, 0.1);
	Point leftTopTriangleLeftPoint = Point(0.0, 0.1, 0.0);
	Point leftTopTriangleRightPoint = Point(0.0, 0.0, 0.1);
	Triangle leftTopTriangle = Triangle(leftTopTriangleTopPoint, leftTopTriangleLeftPoint, leftTopTriangleRightPoint);

	Square leftSquare = Square(leftTopTriangle, leftBottomTriangle);

	Point rightBottomTriangleTopPoint = Point(0.1, 0.1, 0.0);
	Point rightBottomTriangleLeftPoint = Point(0.1, 0.0, 0.0);
	Point rightBottomTriangleRightPoint = Point(0.1, 0.0, 0.1);
	Triangle rightBottomTriangle = Triangle(rightBottomTriangleTopPoint, rightBottomTriangleLeftPoint, rightBottomTriangleRightPoint);

	Point rightTopTriangleTopPoint = Point(0.1, 0.1, 0.1);
	Point rightTopTriangleLeftPoint = Point(0.1, 0.1, 0.0);
	Point rightTopTriangleRightPoint = Point(0.1, 0.0, 0.1);
	Triangle rightTopTriangle = Triangle(rightTopTriangleTopPoint, rightTopTriangleLeftPoint, rightTopTriangleRightPoint);

	Square rightSquare = Square(rightTopTriangle, rightBottomTriangle);

	Point topBottomTriangleTopPoint = Point(0.0, 0.1, 0.0);
	Point topBottomTriangleLeftPoint = Point(0.1, 0.1, 0.0);
	Point topBottomTriangleRightPoint = Point(0.1, 0.1, 0.1);
	Triangle topBottomTriangle = Triangle(topBottomTriangleTopPoint, topBottomTriangleLeftPoint, topBottomTriangleRightPoint);

	Point topTopTriangleTopPoint = Point(0.0, 0.1, 0.1);
	Point topTopTriangleLeftPoint = Point(0.0, 0.1, 0.0);
	Point topTopTriangleRightPoint = Point(0.1, 0.1, 0.1);
	Triangle topTopTriangle = Triangle(topTopTriangleTopPoint, topTopTriangleLeftPoint, topTopTriangleRightPoint);

	Square topSquare = Square(topTopTriangle, topBottomTriangle);

	Point bottomBottomTriangleTopPoint = Point(0.0, 0.1, 0.0);
	Point bottomBottomTriangleLeftPoint = Point(0.1, 0.1, 0.0);
	Point bottomBottomTriangleRightPoint = Point(0.1, 0.1, 0.1);
	Triangle bottomBottomTriangle = Triangle(bottomBottomTriangleTopPoint, bottomBottomTriangleLeftPoint, bottomBottomTriangleRightPoint);

	Point bottomTopTriangleTopPoint = Point(0.0, 0.1, 0.1);
	Point bottomTopTriangleLeftPoint = Point(0.0, 0.1, 0.0);
	Point bottomTopTriangleRightPoint = Point(0.1, 0.1, 0.1);
	Triangle bottomTopTriangle = Triangle(bottomTopTriangleTopPoint, bottomTopTriangleLeftPoint, bottomTopTriangleRightPoint);

	Square bottomSquare = Square(bottomTopTriangle, bottomBottomTriangle);

	return Cube(frontSquare, backSquare, leftSquare, rightSquare, topSquare, bottomSquare);
}

int setupCubesClass() {
	Cube cube = initializateCube();

	float* points = cube.getPoints();

	GLfloat vertices[TOTAL_VERTICES_SIZE];

	int actualIndex = 0;

	for (int i = 0; i < TOTAL_CUBES; i++) {
		for (int j = 0; j < SIZE_PER_CUBE; j++) {
			vertices[actualIndex] = points[j];

			actualIndex++;
		}

		cube.increaseX();

		if (i != 0 && (i + 1) % GRID_SIZE == 0) {
			cube.increaseY();
			cube.initializateX();
		}

		if (i != 0 && (i + 1) % CUBES_PER_GRID == 0) {
			cube.increaseZ();
			cube.initializateY();
		}

		points = cube.getPoints();
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

	//initializePaletteVector();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho Grau A - Marcelo dos Santos Alvarez!", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	Shader shader("../shaders/helloCamera.vs", "../shaders/helloCamera.fs");

	GLuint VAO = setupCubesClass();

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
		renderCubes();
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
