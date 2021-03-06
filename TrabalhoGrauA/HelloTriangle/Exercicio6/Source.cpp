#include <cmath>
#include "Cube.h"
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>
#include "Shader.h"
#include <iterator>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Constants.h"
#include "ColorsEnum.h"
#include "SpaceDirectionsKeyEnum.h"
#include "GridDirectionsKeyEnum.h"
#include "NumbersKeyEnum.h"
#include "Pallete.h"

using namespace std;

Pallete pallete;

glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

float lastX = WIDTH / 2.0;
float lastY = HEIGHT / 2.0;

bool firstTimeMovingMouse = true;

float yaw = -90.0;
float pitch = 0.0;

Cube cubes[GRID_SIZE][GRID_SIZE][GRID_SIZE];

int actualCubeX = 0;
int actualCubeY = 0;
int actualCubeZ = 0;

GLfloat vertices[TOTAL_VERTICES_SIZE];

GLuint VAO;

void processMovementInput(GLFWwindow* window) {
	float cameraSpeed = 0.001f;

	if (glfwGetKey(window, SpaceDirectionsKeyEnum::FRONT) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}

	if (glfwGetKey(window, SpaceDirectionsKeyEnum::BACK) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}

	if (glfwGetKey(window, SpaceDirectionsKeyEnum::LEFT) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	if (glfwGetKey(window, SpaceDirectionsKeyEnum::RIGHT) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

void processGridInput(int key) {
	switch (key) {
		case GridDirectionsKeyEnum::GO_ON:
			actualCubeZ = actualCubeZ < GRID_SIZE - 1 ? actualCubeZ + 1 : actualCubeZ;
			break;
		case GridDirectionsKeyEnum::GO_BACK:
			actualCubeZ = actualCubeZ >= 1 ? actualCubeZ - 1 : actualCubeZ;
			break;
		case GridDirectionsKeyEnum::GO_UP:
			actualCubeY = actualCubeY < GRID_SIZE - 1 ? actualCubeY + 1 : actualCubeY;
			break;
		case GridDirectionsKeyEnum::GO_DOWN:
			actualCubeY = actualCubeY >= 1 ? actualCubeY - 1 : actualCubeY;
			break;
		case GridDirectionsKeyEnum::GO_RIGHT:
			actualCubeX = actualCubeX < GRID_SIZE - 1 ? actualCubeX + 1 : actualCubeX;
			break;
		case GridDirectionsKeyEnum::GO_LEFT:
			actualCubeX = actualCubeX >= 1 ? actualCubeX - 1 : actualCubeX;
			break;
	}
}

void setupCubesClass() {
	int actualIndex = 0;

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			for (int k = 0; k < GRID_SIZE; k++) {
				float* points = cubes[i][j][k].getPoints();

				for (int l = 0; l < SIZE_PER_CUBE; l++) {
					vertices[actualIndex] = points[l];

					actualIndex++;
				}
			}
		}
	}

	GLuint VBO;

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
}

void processActionInput(int key, GLFWwindow* window) {
	switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_ENTER:
			cubes[actualCubeX][actualCubeY][actualCubeZ].changeColor(pallete.getActualColor());

			setupCubesClass();
			break;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		processGridInput(key);
		pallete.processColorInput(key);
		processActionInput(key, window);
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

Cube instantiateNewCube(float addX, float addY, float addZ) {
	Point frontBottomTriangleTopPoint = Point(0.0 + addX, 0.1 + addY, 0.0 + addZ);
	Point frontBottomTriangleLeftPoint = Point(0.0 + addX, 0.0 + addY, 0.0 + addZ);
	Point frontBottomTriangleRightPoint = Point(0.1 + addX, 0.0 + addY, 0.0 + addZ);
	Triangle frontBottomTriangle = Triangle(frontBottomTriangleTopPoint, frontBottomTriangleLeftPoint, frontBottomTriangleRightPoint);

	Point frontTopTriangleTopPoint = Point(0.1 + addX, 0.1 + addY, 0.0 + addZ);
	Point frontTopTriangleLeftPoint = Point(0.0 + addX, 0.1 + addY, 0.0 + addZ);
	Point frontTopTriangleRightPoint = Point(0.1 + addX, 0.0 + addY, 0.0 + addZ);
	Triangle frontTopTriangle = Triangle(frontTopTriangleTopPoint, frontTopTriangleLeftPoint, frontTopTriangleRightPoint);

	Square frontSquare = Square(frontTopTriangle, frontBottomTriangle);

	Point backBottomTriangleTopPoint = Point(0.0 + addX, 0.1 + addY, 0.1 + addZ);
	Point backBottomTriangleLeftPoint = Point(0.0 + addX, 0.0 + addY, 0.1 + addZ);
	Point backBottomTriangleRightPoint = Point(0.1 + addX, 0.0 + addY, 0.1 + addZ);
	Triangle backBottomTriangle = Triangle(backBottomTriangleTopPoint, backBottomTriangleLeftPoint, backBottomTriangleRightPoint);

	Point backTopTriangleTopPoint = Point(0.1 + addX, 0.1 + addY, 0.1 + addZ);
	Point backTopTriangleLeftPoint = Point(0.0 + addX, 0.1 + addY, 0.1 + addZ);
	Point backTopTriangleRightPoint = Point(0.1 + addX, 0.0 + addY, 0.1 + addZ);
	Triangle backTopTriangle = Triangle(backTopTriangleTopPoint, backTopTriangleLeftPoint, backTopTriangleRightPoint);

	Square backSquare = Square(backTopTriangle, backBottomTriangle);

	Point leftBottomTriangleTopPoint = Point(0.0 + addX, 0.1 + addY, 0.0 + addZ);
	Point leftBottomTriangleLeftPoint = Point(0.0 + addX, 0.0 + addY, 0.0 + addZ);
	Point leftBottomTriangleRightPoint = Point(0.0 + addX, 0.0 + addY, 0.1 + addZ);
	Triangle leftBottomTriangle = Triangle(leftBottomTriangleTopPoint, leftBottomTriangleLeftPoint, leftBottomTriangleRightPoint);

	Point leftTopTriangleTopPoint = Point(0.0 + addX, 0.1 + addY, 0.1 + addZ);
	Point leftTopTriangleLeftPoint = Point(0.0 + addX, 0.1 + addY, 0.0 + addZ);
	Point leftTopTriangleRightPoint = Point(0.0 + addX, 0.0 + addY, 0.1 + addZ);
	Triangle leftTopTriangle = Triangle(leftTopTriangleTopPoint, leftTopTriangleLeftPoint, leftTopTriangleRightPoint);

	Square leftSquare = Square(leftTopTriangle, leftBottomTriangle);

	Point rightBottomTriangleTopPoint = Point(0.1 + addX, 0.1 + addY, 0.0 + addZ);
	Point rightBottomTriangleLeftPoint = Point(0.1 + addX, 0.0 + addY, 0.0 + addZ);
	Point rightBottomTriangleRightPoint = Point(0.1 + addX, 0.0 + addY, 0.1 + addZ);
	Triangle rightBottomTriangle = Triangle(rightBottomTriangleTopPoint, rightBottomTriangleLeftPoint, rightBottomTriangleRightPoint);

	Point rightTopTriangleTopPoint = Point(0.1 + addX, 0.1 + addY, 0.1 + addZ);
	Point rightTopTriangleLeftPoint = Point(0.1 + addX, 0.1 + addY, 0.0 + addZ);
	Point rightTopTriangleRightPoint = Point(0.1 + addX, 0.0 + addY, 0.1 + addZ);
	Triangle rightTopTriangle = Triangle(rightTopTriangleTopPoint, rightTopTriangleLeftPoint, rightTopTriangleRightPoint);

	Square rightSquare = Square(rightTopTriangle, rightBottomTriangle);

	Point topBottomTriangleTopPoint = Point(0.0 + addX, 0.1 + addY, 0.0 + addZ);
	Point topBottomTriangleLeftPoint = Point(0.1 + addX, 0.1 + addY, 0.0 + addZ);
	Point topBottomTriangleRightPoint = Point(0.1 + addX, 0.1 + addY, 0.1 + addZ);
	Triangle topBottomTriangle = Triangle(topBottomTriangleTopPoint, topBottomTriangleLeftPoint, topBottomTriangleRightPoint);

	Point topTopTriangleTopPoint = Point(0.0 + addX, 0.1 + addY, 0.1 + addZ);
	Point topTopTriangleLeftPoint = Point(0.0 + addX, 0.1 + addY, 0.0 + addZ);
	Point topTopTriangleRightPoint = Point(0.1 + addX, 0.1 + addY, 0.1 + addZ);
	Triangle topTopTriangle = Triangle(topTopTriangleTopPoint, topTopTriangleLeftPoint, topTopTriangleRightPoint);

	Square topSquare = Square(topTopTriangle, topBottomTriangle);

	Point bottomBottomTriangleTopPoint = Point(0.0 + addX, 0.1 + addY, 0.0 + addZ);
	Point bottomBottomTriangleLeftPoint = Point(0.1 + addX, 0.1 + addY, 0.0 + addZ);
	Point bottomBottomTriangleRightPoint = Point(0.1 + addX, 0.1 + addY, 0.1 + addZ);
	Triangle bottomBottomTriangle = Triangle(bottomBottomTriangleTopPoint, bottomBottomTriangleLeftPoint, bottomBottomTriangleRightPoint);

	Point bottomTopTriangleTopPoint = Point(0.0 + addX, 0.1 + addY, 0.1 + addZ);
	Point bottomTopTriangleLeftPoint = Point(0.0 + addX, 0.1 + addY, 0.0 + addZ);
	Point bottomTopTriangleRightPoint = Point(0.1 + addX, 0.1 + addY, 0.1 + addZ);
	Triangle bottomTopTriangle = Triangle(bottomTopTriangleTopPoint, bottomTopTriangleLeftPoint, bottomTopTriangleRightPoint);

	Square bottomSquare = Square(bottomTopTriangle, bottomBottomTriangle);

	return Cube(frontSquare, backSquare, leftSquare, rightSquare, topSquare, bottomSquare);
}

void initializeCubeMatrix() {
	float addX = 0.0;
	float addY = 0.0;
	float addZ = 0.0;

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			for (int k = 0; k < GRID_SIZE; k++) {
				cubes[i][j][k] = instantiateNewCube(addX, addY, addZ);
				
				addX += 0.1;
			}
			addY += 0.1; 
			addX = 0.0;
		}
		addZ += 0.1;
		addY = 0.0;
	}
}

int main() {
	glfwInit();

	initializeCubeMatrix();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho Grau A - Marcelo dos Santos Alvarez!", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	Shader shader("../shaders/helloCamera.vs", "../shaders/helloCamera.fs");

	setupCubesClass();

	glUseProgram(shader.ID);

	glm::mat4 view = glm::mat4(1);
	glm::mat4 projection = glm::mat4(1);

	view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0) + cameraFront, cameraUp);
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	shader.setMat4("view", glm::value_ptr(view));
	shader.setMat4("projection", glm::value_ptr(projection));

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		processMovementInput(window);

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

		GLint modelLoc = glGetUniformLocation(shader.ID, "model");

		glUniformMatrix4fv(modelLoc, 1, FALSE, glm::value_ptr(model));

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();

	return 0;
}
