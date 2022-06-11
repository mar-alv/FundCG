#pragma once
#include "Level.h"
#include "Sprite.h"
#include "stb_image.h"
#include "GridDirectionsEnum.h"

class SceneManager
{
private:
	GLFWwindow* window;

	vector <Shader*> shaders;

	GLuint VAO;

	glm::mat4 model;
	glm::mat4 projection;

	int actualLevel;

	std::vector <Level> levels;

	Sprite player;
	glm::vec2 playerPosition;

	int playerY;
	int playerX;

public:
	static int dir;
	static bool resized;
	static bool keys[1024];
	static GLuint actualWindowWidth, actualWindowHeight;

	SceneManager();
	~SceneManager();

	void initialize();
	void initializeGraphics();

	void clearColorBuffer();
	void enableAlphaChannel();

	void update();
	void render();
	void run();
	void finish();

	unsigned char* setupTexture(std::string filePath);

	GLuint setTextureWrapping();
	GLuint loadTexture(std::string filePath);

	void setupScene();
	void setupLevels();
	void setupCamera2D();

	void addShader(string vsFilePath, string fsFilePath);

	static void resize(GLFWwindow* window, int newWindowWidth, int newWindowHeight);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};
