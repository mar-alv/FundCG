#include "SceneManager.h"

bool SceneManager::resized = false;
bool SceneManager::keys[1024] = { 0 };
GLuint SceneManager::actualWindowWidth = WIDTH;
GLuint SceneManager::actualWindowHeight = HEIGHT;
Player SceneManager::player = Player();

SceneManager::SceneManager() {
	this->actualLevel = 0;

	srand(time(0));
}

SceneManager::~SceneManager() { }

void SceneManager::initialize() {
	actualWindowWidth = WIDTH;
	actualWindowHeight = HEIGHT;

	initializeGraphics();
}

void SceneManager::initializeGraphics() {
	glfwInit();

	window = glfwCreateWindow(actualWindowWidth, actualWindowHeight, "Hello Transform", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glfwSetWindowSizeCallback(window, resize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	addShader(SHADER_TRANSFORMATIONS_VS_PATH, SHADER_TRANSFORMATIONS_FS_PATH);
	addShader(SHADER_SPRITE_VS_PATH, SHADER_SPRITE_FS_PATH);

	setupScene();

	resized = true;

	setupCamera2D();
}

void SceneManager::addShader(std::string vsFilePath, std::string fsFilePath) {
	Shader* shader = new Shader(vsFilePath.c_str(), fsFilePath.c_str());

	shaders.push_back(shader);
}

void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

	player.onMovementKeyPress(key, action);
}

void SceneManager::resize(GLFWwindow* window, int newWindowWidth, int newWindowHeight) {
	actualWindowWidth = newWindowWidth;
	actualWindowHeight = newWindowHeight;

	resized = true;

	glViewport(0, 0, actualWindowWidth, actualWindowHeight);
}

void SceneManager::update() {
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

	player.move();

	player.stayInsideGrid(levels[actualLevel].getGridRowsCount(), levels[actualLevel].getGridColumnsCount());
}

void SceneManager::clearColorBuffer() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneManager::render() {
	clearColorBuffer();

	if (resized) {
		setupCamera2D();

		resized = false;
	}

	shaders[0]->Use();

	float xi = 368;
	float yi = 100;

	levels[actualLevel].renderGridMap();
	
	float x = xi + (this->player.getActualX() - this->player.getActualY()) * GRIDS_WIDTH / 2.0;
	float y = yi + (this->player.getActualX() + this->player.getActualY()) * GRIDS_HEIGHT / 2.0;

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(x, y, 0.0));

	levels[actualLevel].getTileset()[7].draw(model);
	//Desenha o personagem
}

void SceneManager::run() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		update();
		render();
		glfwSwapBuffers(window);
	}
}

void SceneManager::finish() {
	glfwTerminate();
}

void SceneManager::setupLevels() {
	Level level0 = Level(shaders[0], '0');
	//Level level1 = Level(shaders[0], '1');
	//Level level2 = Level(shaders[0], '2');

	levels.push_back(level0);
	//levels.push_back(level1);
	//levels.push_back(level2);
}

void SceneManager::setupScene() {
	setupLevels();
}

void SceneManager::setupCamera2D() {
	glViewport(0, 0, actualWindowWidth, actualWindowHeight);

	float zFar = 1.0;
	float zNear = -1.0;
	float xMinAndYMax = 0.0;

	projection = glm::ortho(xMinAndYMax, (float)WIDTH, (float)HEIGHT, xMinAndYMax, zNear, zFar);

	shaders[0]->Use();

	GLint projLoc = glGetUniformLocation(shaders[0]->ID, "projection");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	shaders[1]->Use();

	projLoc = glGetUniformLocation(shaders[1]->ID, "projection");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void SceneManager::enableAlphaChannel() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLuint SceneManager::setTextureWrapping() {
	GLuint texID;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texID;
}

unsigned char* SceneManager::setupTexture(std::string filePath) {
	int width;
	int height;
	int numberOfChannels;

	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &numberOfChannels, 0);

	const bool isTextureNotPNG = numberOfChannels == 3;

	const GLuint correctFormat = isTextureNotPNG ? GL_RGB : GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, correctFormat, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	return data;
}

GLuint SceneManager::loadTexture(std::string filePath) {
	GLuint texID = setTextureWrapping();

	unsigned char* data = setupTexture(filePath);

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);

	enableAlphaChannel();

	return texID;
}
