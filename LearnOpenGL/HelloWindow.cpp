#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "HelperFunctions.h"

// Constants
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

namespace HelloWindow {

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput(GLFWwindow *window);

	int main()
	{

		void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		void processInput(GLFWwindow *window);

		// Initialize the GLFW library
		glfwInit();

		// Tell GLFW  that the major and minor version of OpenGL to use is 3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// Tell GLFW that we want to use core-profile, meaning that we'll get
		// access to a smaller subset of OpenGL features
		// (without backwards-compatible features we no longer need)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create a window and it's context
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

		if (window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}

		// Set the current context
		glfwMakeContextCurrent(window);

		// Registers a callback function on the window that gets called
		// each time the window is rezied, so the moment the user rezies the
		// window, the viewport is adjusted as well.
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// Initialize GLAD (the thing that managers function pointers for OpenGL)
		// before we call any OpenGL function
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		// game / render loop
		while (!glfwWindowShouldClose(window))
		{
			// Input
			processInput(window);

			// Rendering
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Check and call events and swap the buffers
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// clear all previously allocated GLFW resources
		glfwTerminate();
		return 0;
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// Tell OpenGL the size of the rendering window so OpenGL knows how we want to display
		// the data and coordinates with respect to the window.
		glViewport(0, 0, width, height);
	}


	void processInput(GLFWwindow *window)
	{
		// Processes user input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

}