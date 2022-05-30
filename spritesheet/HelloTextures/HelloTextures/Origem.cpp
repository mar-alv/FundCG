#include <cmath>
#include "Timer.h"
#include "Shader.h"
#include <assert.h>
#include "Sprite.h"
#include <glm/glm.hpp> 
#include "Constants.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void enableDepth() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
}

void enableBlend() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void clearColorBuffer() {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main()
{
	glfwInit();
	
	Timer timer = Timer();
	Sprite linkSprite  = Sprite();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Textures!", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	Shader shader(SPRITE_VS_PATH, SPRITE_FS_PATH);

	GLuint texID = linkSprite.load(LINK_SPRITE_PATH);

	int frameCount = 5;
	int animationCount = 1;

	GLuint VAO = linkSprite.setup(frameCount, animationCount);

	glUseProgram(shader.getId());

	glUniform1i(glGetUniformLocation(shader.getId(), "tex_buffer"), 0);

	glm::mat4 projection = glm::mat4(1); 

	projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	GLint projLoc = glGetUniformLocation(shader.getId(), "projection");

	glUniformMatrix4fv(projLoc, 1, FALSE, glm::value_ptr(projection));
	
	enableDepth();
	enableBlend();
	
	int iFrame = 2;
	int iAnims = 0;

	while (!glfwWindowShouldClose(window))
	{
		timer.start();
		
		glfwPollEvents();

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);

		clearColorBuffer();
		
		glLineWidth(10);

		glPointSize(20);

		glm::mat4 model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(400.0, 300.0, 0));
		model = glm::scale(model, glm::vec3(200.0, 200.0, 1.0));

		shader.setMat4("model", glm::value_ptr(model));

		float offsetx = linkSprite.getDX() * iFrame;
		float offsety = linkSprite.getDY() * iAnims;

		shader.setVec2("offsets", offsetx, offsety);

		iFrame = (iFrame + 1) % frameCount;

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, texID);

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);

		timer.finish();
		timer.delay();

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();

	return 0;
}
