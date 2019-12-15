#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

GLFWwindow* Initialization();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	GLFWwindow* window = Initialization();

	// set function callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
		Test Data
	*/
	float vertices[] = {
		0.5f, 0.5f, 1.0f,
		-0.5f, 0.5f, 1.0f,
		-0.5f, -0.5f, 1.0f,
		0.5f, -0.5f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vbo(sizeof(vertices), vertices);
	IndexBuffer ibo(sizeof(indices), indices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	Shader shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");

	/* --------------------------- MAIN LOOP  -----------------------*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		vbo.Bind();
		ibo.Bind();
		shader.Use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
}