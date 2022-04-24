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

class Color {
private:
	float r;
	float g;
	float b;

public:
	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	Color() {
	}

	float* getPoints() {
		float* points = new float[3];

		points[0] = r;
		points[1] = g;
		points[2] = b;

		return points;
	}
};

class Point {
private:
	float x;
	float y;
	float z;
	float initialX;
	float initialY;

public:
	Point(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->initialX = x;
		this->initialY = y;
	}

	Point() {
	}

	float getX() {
		return this->x;
	}

	float getY() {
		return this->y;
	}

	float getZ() {
		return this->z;
	}

	void setX(float x) {
		this->x = x;
	}

	void setY(float y) {
		this->y = y;
	}

	void setZ(float z) {
		this->z = z;
	}

	float getInitialX() {
		return this->initialX;
	}

	float getInitialY() {
		return this->initialY;
	}

	float* getPoints() {
		float* points = new float[3];

		points[0] = x; 
		points[1] = y;
		points[2] = z;
		
		return points;
	}

	void initializateX() {
		this->x = this->getInitialX();
	}

	void increaseX() {
		setX(x + 0.1);
	}

	void increaseY() {
		setY(y + 0.1);
	}

	void increaseZ() {
		setZ(z + 0.1);
	}

	void initializateY() {
		this->y = this->getInitialY();
	}
};

class Triangle {
private:
	Point top;
	Point left;
	Point right;
	Color color;

public:
	Triangle(Point top, Point left, Point right) {
		this->top = top;
		this->left = left;
		this->right = right;
		this->color = Color(1.1, 1.1, 1.1);
	}

	Triangle() {
	}

	Point getTop() {
		return top;
	}

	Point getLeft() {
		return left;
	}

	Point getRight() {
		return right;
	}

	float* getPoints() {
		float* topPoints = top.getPoints();
		float* leftPoints = left.getPoints();
		float* rightPoints = right.getPoints();
		float* colorPoints = color.getPoints();

		float* points = new float[18];

		for (int i = 0; i < 3; i++) {
			points[i] = topPoints[i];
			points[i + 3] = colorPoints[i];
			points[i + 6] = leftPoints[i];
			points[i + 9] = colorPoints[i];
			points[i + 12] = rightPoints[i];
			points[i + 15] = colorPoints[i];
		}

		return points;
	}

	void initializateX() {
		top.initializateX();
		left.initializateX();
		right.initializateX();
	}

	void increaseX() {
		top.increaseX();
		left.increaseX();
		right.increaseX();
	}

	void increaseY() {
		top.increaseY();
		left.increaseY();
		right.increaseY();
	}

	void increaseZ() {
		top.increaseZ();
		left.increaseZ();
		right.increaseZ();
	}

	void initializateY() {
		top.initializateY();
		left.initializateY();
		right.initializateY();
	}
};

class Square {
private:
	Triangle topTriangle;
	Triangle bottomTriangle;

public:
	Square(Triangle topTriangle, Triangle bottomTriangle) {
		this->topTriangle = topTriangle;
		this->bottomTriangle = bottomTriangle;
	}

	Square() {
	}

	Triangle getTopTriangle() {
		return topTriangle;
	}

	Triangle getBottomTriangle() {
		return bottomTriangle;
	}

	float* getPoints() {
		float* topPoints = topTriangle.getPoints();
		float* bottomPoints = bottomTriangle.getPoints();

		float* points = new float[36];

		for (int i = 0; i < 18; i++) {
			points[i] = topPoints[i];
			points[i + 18] = bottomPoints[i];
		}

		return points;
	}

	void initializateX() {
		topTriangle.initializateX();
		bottomTriangle.initializateX();
	}

	void increaseX() {
		topTriangle.increaseX();
		bottomTriangle.increaseX();
	}

	void increaseY() {
		topTriangle.increaseY();
		bottomTriangle.increaseY();
	}

	void increaseZ() {
		topTriangle.increaseZ();
		bottomTriangle.increaseZ();
	}

	void initializateY() {
		topTriangle.initializateY();
		bottomTriangle.initializateY();
	}
};

class Cube {
private:
	Square frontSquare;
	Square backSquare;
	Square leftSquare;
	Square rightSquare;
	Square topSquare;
	Square bottomSquare;

public:
	Cube(Square frontSquare, Square backSquare, Square leftSquare, Square rightSquare, Square topSquare, Square bottomSquare) {
		this->frontSquare = frontSquare;
		this->backSquare = backSquare;
		this->leftSquare = leftSquare;
		this->rightSquare = rightSquare;
		this->topSquare = topSquare;
		this->bottomSquare = bottomSquare;
	}

	Cube() {
	}

	Square getFrontSquare() {
		return frontSquare;
	}

	Square getBackSquare() {
		return backSquare;
	}

	Square getLeftSquare() {
		return leftSquare;
	}

	Square getRightSquare() {
		return rightSquare;
	}

	Square getTopSquare() {
		return topSquare;
	}

	Square getBottomSquare() {
		return bottomSquare;
	}

	float* getPoints() {
		float* frontPoints = frontSquare.getPoints();
		float* backPoints = backSquare.getPoints();
		float* leftPoints = leftSquare.getPoints();
		float* rightPoints = rightSquare.getPoints();
		float* topPoints = topSquare.getPoints();
		float* bottomPoints = bottomSquare.getPoints();

		float* points = new float[216];

		for (int i = 0; i < 36; i++) {
			points[i] = frontPoints[i];
			points[i + 36] = backPoints[i];
			points[i + 72] = leftPoints[i];
			points[i + 108] = rightPoints[i];
			points[i + 144] = topPoints[i];
			points[i + 180] = bottomPoints[i];
		}

		return points;
	}

	void initializateX() {
		frontSquare.initializateX();
		backSquare.initializateX();
		leftSquare.initializateX();
		rightSquare.initializateX();
		topSquare.initializateX();
		bottomSquare.initializateX();
	}

	void increaseX() {
		frontSquare.increaseX();
		backSquare.increaseX();
		leftSquare.increaseX();
		rightSquare.increaseX();
		topSquare.increaseX();
		bottomSquare.increaseX();
	}

	void increaseY() {
		frontSquare.increaseY();
		backSquare.increaseY();
		leftSquare.increaseY();
		rightSquare.increaseY();
		topSquare.increaseY();
		bottomSquare.increaseY();
	}

	void increaseZ() {
		frontSquare.increaseZ();
		backSquare.increaseZ();
		leftSquare.increaseZ();
		rightSquare.increaseZ();
		topSquare.increaseZ();
		bottomSquare.increaseZ();
	}

	void initializateY() {
		frontSquare.initializateY();
		backSquare.initializateY();
		leftSquare.initializateY();
		rightSquare.initializateY();
		topSquare.initializateY();
		bottomSquare.initializateY();
	}
};

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
