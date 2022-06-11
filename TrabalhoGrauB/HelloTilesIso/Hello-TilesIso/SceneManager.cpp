#include "SceneManager.h"

int SceneManager::dir = PARADO;
bool SceneManager::resized = false;
bool SceneManager::keys[1024] = { 0 };
GLuint SceneManager::actualWindowWidth = WIDTH;
GLuint SceneManager::actualWindowHeight = HEIGHT;

SceneManager::SceneManager() {
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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	addShader(SHADER_TRANSFORMATIONS_VS_PATH, SHADER_TRANSFORMATIONS_FS_PATH);
	addShader(SHADER_SPRITE_VS_PATH, SHADER_SPRITE_FS_PATH);

	setupScene();

	resized = true;

	setupCamera2D();
}

void SceneManager::addShader(string vsFilePath, string fsFilePath) {
	Shader* shader = new Shader(vsFilePath.c_str(), fsFilePath.c_str());

	shaders.push_back(shader);
}

void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
		{
			dir = NORTE;
		}
		if (key == GLFW_KEY_S)
		{
			dir = SUL;
		}
		if (key == GLFW_KEY_A)
		{
			dir = OESTE;
		}
		if (key == GLFW_KEY_D)
		{
			dir = LESTE;
		}
	}
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

	if (dir == NORTE)
	{
		//atualiza posição do mapa onde personagem irá,
		//conforme tabela de navegação do diamond
	}

	if (dir == SUL)
	{
		//atualiza posição do mapa onde personagem irá,
		//conforme tabela de navegação do diamond
	}

	if (dir == LESTE)
	{
		//atualiza posição do mapa onde personagem irá,
		//conforme tabela de navegação do diamond
	}

	if (dir == OESTE)
	{
		//atualiza posição do mapa onde personagem irá,
		//conforme tabela de navegação do diamond
	}

	if (poslinha < 0)
	{
		poslinha = 0;
	}
	if (poscoluna < 0)
	{
		poscoluna = 0;
	}
	if (poslinha > GRID_SIZE - 1)
	{
		poslinha = GRID_SIZE - 1;
	}
	if (poscoluna > GRID_SIZE - 1)
	{
		poscoluna = GRID_SIZE - 1;
	}
}

void SceneManager::clearColorBuffer() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneManager::render() {
	clearColorBuffer();

	if (resized)
	{
		setupCamera2D();

		resized = false;
	}

	shaders[0]->Use();

	float xi = 368;
	float yi = 100;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			float x = xi + (j - i) * tileset[0].getWidth() / 2.0;
			float y = yi + (j + i) * tileset[0].getHeight() / 2.0;

			model = glm::mat4();
			model = glm::translate(model, glm::vec3(x, y, 0.0));
			tileset[map[i][j]].draw(model);
		}
	}
	float x = xi + (poscoluna - poslinha) * tileset[0].getWidth() / 2.0;
	float y = yi + (poscoluna + poslinha) * tileset[0].getHeight() / 2.0;

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(x, y, 0.0));

	tileset[7].draw(model);

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

glm::vec4 normalizaRGB(glm::vec4 byteColor) {
	glm::vec4 normColor(byteColor.r / 255.0, byteColor.g / 255.0, byteColor.b / 255.0, byteColor.a / 255.0);

	return normColor;
}


void SceneManager::setupLevels() {
	ifstream file;
	std::string fileType = ".txt";
	
	char mat[GRID_SIZE][GRID_SIZE];
	
	file.open(LEVELS_PATH);

	int mapaauxiliar[GRID_SIZE][GRID_SIZE];

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			file >> mat[i][j];
			// file >> mapaauxiliar[i][j];
		}
	}
	/*for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			cout << mat[i][j];
		}
		cout << endl;
	}*/

	file.close();




	int rows = 10, cols = 10;
	int** matrix = new int* [rows];
	
	matrix[0] = new int[rows * cols];
	for (int i = 1; i < rows; ++i)
		matrix[i] = matrix[0] + i * cols;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << "a:"<< matrix[i];
		}
		cout << endl;
	}
}

void SceneManager::setupScene() {
	TileIso tile;
	glm::vec4 corDoTile;

	setupLevels();

	tile.setShader(shaders[0]);

	corDoTile.r = 47; corDoTile.g = 117; corDoTile.b = 181; corDoTile.a = 255;
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	corDoTile.r = 0; corDoTile.g = 176; corDoTile.b = 80; corDoTile.a = 255;
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	corDoTile.r = 191; corDoTile.g = 143; corDoTile.b = 0; corDoTile.a = 255;
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	corDoTile.r = 128; corDoTile.g = 96; corDoTile.b = 0; corDoTile.a = 255;
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	corDoTile.r = 191; corDoTile.g = 191; corDoTile.b = 191; corDoTile.a = 255;
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	corDoTile.r = 198; corDoTile.g = 89; corDoTile.b = 17; corDoTile.a = 255;
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	corDoTile.r = 31; corDoTile.g = 78; corDoTile.b = 120; corDoTile.a = 255;
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	corDoTile.r = 0; corDoTile.g = 0; corDoTile.b = 0; corDoTile.a = 255;
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	int mapaauxiliar[GRID_SIZE][GRID_SIZE] =
	{
		6,	6,	6,	6,	0,	3,	3,	3,	3,	2,
		0,	0,	0,	0,	0,	3,	3,	3,	3,	2,
		1,	1,	0,	0,	0,	0,	3,	3,	3,	2,
		1,	1,	2,	2,	0,	0,	4,	4,	4,	2,
		1,	1,	2,	2,	0,	0,	4,	4,	4,	2,
		1,	1,	2,	2,	2,	4,	4,	4,	4,	2,
		1,	1,	2,	2,	2,	4,	4,	4,	4,	2,
		1,	1,	0,	0,	0,	4,	4,	5,	5,	5,
		1,	1,	2,	2,	0,	4,	4,	5,	5,	5,
		3,	3,	6,	6,	6,	4,	4,	5,	5,	5
	};

	int mapcaminhavel[GRID_SIZE][GRID_SIZE] =
	{
		0,	0,	0,	0,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,  1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	0,	0,	0,	1,	1,	1,	1,	1
	};

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			map[i][j] = mapaauxiliar[i][j];
		}
	}

	poslinha = 0;
	poscoluna = 0;

	dir = PARADO;
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
