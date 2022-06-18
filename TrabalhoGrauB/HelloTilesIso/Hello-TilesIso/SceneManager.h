#pragma once
#include "Level.h"
#include "Player.h"
#include "stb_image.h"

class SceneManager
{
private:
	int actualLevel;

	GLFWwindow* window;
	
	static Player player;

	glm::mat4 model;
	glm::mat4 projection;

	std::vector <Level> levels;
	std::vector <Shader*> shaders;

	static bool resized;
	static bool keys[1024];
	static GLuint actualWindowWidth, actualWindowHeight;

public:
	SceneManager();
	~SceneManager();

	void setupScene();
	void setupLevels();
	void setupPlayer();
	void setupCamera2D();
	
	void run();
	void finish();
	void render();
	void update();
	void clearColorBuffer();
	
	void initialize();
	void initializeGraphics();

	void setupCameraOnReize();

	void renderObjects();

	void enableDepth();
	void enableAlphaChannel();

	void addShader(std::string vsFilePath, std::string fsFilePath);

	static void resize(GLFWwindow* window, int newWindowWidth, int newWindowHeight);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};
