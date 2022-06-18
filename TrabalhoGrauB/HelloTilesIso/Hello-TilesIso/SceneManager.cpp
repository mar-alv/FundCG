#include "SceneManager.h"

bool SceneManager::resized = false;
bool SceneManager::keys[1024] = { 0 };
Player SceneManager::player = Player();
GLuint SceneManager::actualWindowWidth = WIDTH;
GLuint SceneManager::actualWindowHeight = HEIGHT;
GLuint testeVAO, testeID;

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

	window = glfwCreateWindow(actualWindowWidth, actualWindowHeight, "Trabalho Grau B - Marcelo Alvarez", nullptr, nullptr);

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
	int gridRowsCount = levels[actualLevel].getGridRowsCount();
	int gridColumnsCount = levels[actualLevel].getGridColumnsCount();

	if (keys[GLFW_KEY_ESCAPE]) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	this->player.move();

	this->player.stayInsideGrid(gridRowsCount, gridColumnsCount);
}

void SceneManager::clearColorBuffer() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int iFrame = 2;
int iAnims = 0;
int frameCount = 4;

void SceneManager::drawPlayer() {
	glUseProgram(shaders[1]->ID);
	const float addaaa = 25.0;

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(400.0 + player.getActualX() + addaaa, 100.0 + player.getActualY() + addaaa, 0));
	model = glm::scale(model, glm::vec3(200.0, 200.0, 1.0));

	shaders[1]->setMat4("model", glm::value_ptr(model));

	float offsetx = player.getTexture().getDX() * iFrame;
	float offsety = player.getTexture().getDY() * iAnims;

	shaders[1]->setVec2("offsets", offsetx, offsety);

	iFrame = (iFrame + 1) % frameCount;

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, testeID);

	glBindVertexArray(testeVAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void SceneManager::render() {
	clearColorBuffer();

	if (resized) {
		setupCamera2D();

		resized = false;
	}

	shaders[0]->Use();

	float xi = 640 - 64;
	float yi = 80;

	levels[actualLevel].renderGridMap();
	
	float x = xi + (this->player.getActualX() - this->player.getActualY()) * GRIDS_WIDTH / 2.0;
	float y = yi + (this->player.getActualX() + this->player.getActualY()) * GRIDS_HEIGHT / 2.0;

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(x, y, 0.0));

	drawPlayer();
}

void SceneManager::run() {
	glUseProgram(shaders[1]->ID);

	glUniform1i(glGetUniformLocation(shaders[1]->ID, "ourTexture1"), 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	testeID = this->player.getTexture().load(PLAYER_SPRITE_PATH);
	testeVAO = this->player.getTexture().setup(4,4);
}
