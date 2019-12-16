#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Camera.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(45.0f);

GLFWwindow* Initialization();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	GLFWwindow* window = Initialization();

	// set function callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	VertexArray vao;
	Cube cube(vao);

	Shader shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");

	/* --------------------------- MAIN LOOP  -----------------------*/
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		vao.Bind();
		shader.Use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));

		glm::mat4 view = camera.GetView();

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(camera.FOV), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		unsigned int modelloc = glGetUniformLocation(shader.program, "model");
		unsigned int viewloc = glGetUniformLocation(shader.program, "view");
		unsigned int projloc = glGetUniformLocation(shader.program, "projection");

		glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projloc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));

		cube.Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/* ------------------------END OF MAIN LOOP ----------------------*/

	glfwTerminate();
	return 0;
}

GLFWwindow* Initialization()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rend3D", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Could not create GLFW window" << std::endl;
		return NULL;
	}

	glfwMakeContextCurrent(window);

	// initalize glad

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.MoveCamera(Camera::MoveDirection::UP, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.MoveCamera(Camera::MoveDirection::DOWN, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.MoveCamera(Camera::MoveDirection::LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.MoveCamera(Camera::MoveDirection::RIGHT, deltaTime);
	}
}