#include "SceneManager.h"

bool SceneManager::resized = false;
bool SceneManager::keys[1024] = { 0 };
Player SceneManager::player = Player();
GLuint SceneManager::actualWindowWidth = WIDTH;
GLuint SceneManager::actualWindowHeight = HEIGHT;

SceneManager::SceneManager() {
	actualLevel = 2;
	areEnemiesAbleToMove = false;

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
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}

	player.onKeyPress(key, action);
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

	player.move();
	player.stayInsideGrid(gridRowsCount, gridColumnsCount);
	player.setActualTileType(levels[actualLevel].getGrid()[player.getActualRowPosition()][player.getActualColumnPosition()].getType());

	if (areEnemiesAbleToMove) {
		levels[actualLevel].makeEnemiesMoveOrAttack();
		levels[actualLevel].updateEnemyActualTileType();

		areEnemiesAbleToMove = false;
	}
	if (player.getIsAttacking()) {
		levels[actualLevel].killEnemy(player.getActualRowPosition(), player.getActualColumnPosition());
	}
	if (player.getHasWatered()) {
		player.setHasWatered(false);

		levels[actualLevel].growPlant(player.getActualColumnPosition(), player.getActualRowPosition());
	}

	if (levels[actualLevel].checkIfPlayerWon()) {
		actualLevel++;
	}

	if (levels[actualLevel].checkIfPlayerLost()) {
		resetLevels();
	}
}

void SceneManager::resetLevels() {
	actualLevel = 0;
	levels.clear();
	setupLevels();
}

void SceneManager::render() {
	clearColorBuffer();
	setupCameraOnReize();
	renderObjects();
}

void SceneManager::clearColorBuffer() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneManager::setupCameraOnReize() {
	if (resized) {
		setupCamera2D();

		resized = false;
	}
}

void SceneManager::renderObjects() {
	levels[actualLevel].render();
	player.render();
}

void SceneManager::enableAlphaChannel() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SceneManager::enableDepth() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
}

void SceneManager::run() {
	shaders[1]->Use();

	Timer timer = Timer();
	Timer timerMoveEnemies = Timer(2500);
	Timer timerSpawnEnemies = Timer(5000);

	glUniform1i(glGetUniformLocation(shaders[1]->ID, "ourTexture1"), 0);

	enableDepth();
	enableAlphaChannel();

	while (!glfwWindowShouldClose(window)) {
		timer.start();

		if (timerMoveEnemies.getElapsedTime() <= 0) {
			timerMoveEnemies.resetTimer();

			areEnemiesAbleToMove = true;
		}

		if (timerSpawnEnemies.getElapsedTime() <= 0) {
			timerSpawnEnemies.resetTimer();

			levels[actualLevel].spawnEnemy();
		}

		glfwPollEvents();
		update();
		render();

		timer.finish();
		timer.delay();

		glfwSwapBuffers(window);
	}

	timerMoveEnemies.finish();
}

void SceneManager::finish() {
	glfwTerminate();
}

void SceneManager::setupScene() {
	setupLevels();
	setupPlayer();
}

void SceneManager::setupLevels() {
	Level level0 = Level(shaders[0], shaders[1], '0');
	Level level1 = Level(shaders[0], shaders[1], '1');
	Level level2 = Level(shaders[0], shaders[1], '2');

	levels.push_back(level0);
	levels.push_back(level1);
	levels.push_back(level2);
}

void SceneManager::setupPlayer() {
	player.initializeTextures();
	player.setShader(shaders[1]);
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
