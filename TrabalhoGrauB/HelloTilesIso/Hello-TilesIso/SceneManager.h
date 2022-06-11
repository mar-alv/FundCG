#pragma once
#include <ctime>
#include <vector>
#include "Shader.h"
#include "Sprite.h"
#include "TileIso.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include "Constants.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Constants.h"


enum direcoes{PARADO, NORTE, SUL, LESTE, OESTE};

class SceneManager
{
private:
	GLFWwindow* window;

	vector <Shader*> shaders;

	GLuint VAO;

	glm::mat4 model;
	glm::mat4 projection;

	vector <TileIso> tileset;

	int map[GRID_SIZE][GRID_SIZE];

	Sprite player;
	glm::vec2 playerPosition;
	int poslinha; //POS Y DO PERSONAGEM NO MAPA
	int poscoluna; //POS X DO PERSONAGEM NO MAPA

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
