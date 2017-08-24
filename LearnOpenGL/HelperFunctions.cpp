#include "HelperFunctions.h"

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