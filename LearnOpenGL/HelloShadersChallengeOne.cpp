#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_s.h"

namespace HelloShadersChallengeOne {

	// Constants
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput(GLFWwindow *window);

	int main()
	{
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

		// Build shaders
		Shader ourShader("Assets//Shaders//shader_challenge_one.vs", "Assets//Shaders//shader.fs");

		// Vertices of our triangle in normalized device coordinates
		float vertices[] = {
			// positions         // colors
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
		};

		// Generate a Vertex Array Object, referenced by ID
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);

		// Generate one vertex buffer object ID, and store in it the address provided
		unsigned int VBO;
		glGenBuffers(1, &VBO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		// Bind the VBO buffer to the GL_ARRAY_BUFFER.
		// Then copy our vertices into the currently bound buffer, GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Tell OpenGL how to interpret our vertex data

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's
		// bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// game / render loop
		while (!glfwWindowShouldClose(window))
		{
			// Input
			processInput(window);

			// Rendering
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Render the triangle
			ourShader.use();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			// Check and call events and swap the buffers
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

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

//int main() {
//
//	return HelloShadersChallengeOne::main();
//
//}