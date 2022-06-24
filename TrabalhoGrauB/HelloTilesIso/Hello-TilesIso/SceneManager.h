#pragma once
#include "Level.h"
#include "Timer.h"
#include "Player.h"
#include "stb_image.h"

class SceneManager
{
private:
	glm::mat4 model;
	int actualLevel;
	GLFWwindow* window;
	static bool resized;
	static Player player;
	glm::mat4 projection;
	static bool keys[1024];
	bool areEnemiesAbleToMove;
	std::vector <Level> levels;
	std::vector <Shader*> shaders;
	static GLuint actualWindowWidth, actualWindowHeight;

public:
	SceneManager();
	~SceneManager();

	void run();
	void finish();
	void render();
	void update();
	void initialize();
	void setupScene();
	void enableDepth();
	void setupLevels();
	void setupPlayer();
	void renderObjects();
	void setupCamera2D();
	void clearColorBuffer();
	void enableAlphaChannel();
	void initializeGraphics();
	void setupCameraOnReize();
	void addShader(std::string vsFilePath, std::string fsFilePath);
	static void resize(GLFWwindow* window, int newWindowWidth, int newWindowHeight);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};
