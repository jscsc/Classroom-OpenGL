#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace HelloTriangleChallegeTwo {

	// Constants
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	// Shaders
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

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


		// -------------------------------------------------------------------------
		// SHADER SETUP
		// -------------------------------------------------------------------------

		// Create a vertex shader referenced by ID
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Attach shader source code to the shader object and compile
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		// Check for sharder compile success
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Now create the fragment shader using the same process
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Create a shader program object, referenced by ID
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();

		// Attach the previously compiled shaders to the program object and then link
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// Check and see if linking worked
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// Activate the shader program
		glUseProgram(shaderProgram);

		// Delete the shader objects once they have been linked, they are not needed anymore
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// -------------------------------------------------------------------------
		// VERTEX SETUP
		// -------------------------------------------------------------------------

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float firstTriangle[] = {
			-0.9f, -0.5f, 0.0f,  // left 
			-0.0f, -0.5f, 0.0f,  // right
			-0.45f, 0.5f, 0.0f,  // top 
		};
		float secondTriangle[] = {
			0.0f, -0.5f, 0.0f,  // left
			0.9f, -0.5f, 0.0f,  // right
			0.45f, 0.5f, 0.0f   // top 
		};
		unsigned int VBOs[2], VAOs[2];
		// we can also generate multiple VAOs or buffers at the same time
		glGenVertexArrays(2, VAOs);
		glGenBuffers(2, VBOs);

		// Setup the first triangle
		glBindVertexArray(VAOs[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// No need to unbind at all as we directly bind a different VAO the next few lines
		// glBindVertexArray(0); 

		// Setup the second triangle
		// ---------------------
		glBindVertexArray(VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
		// Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		// not really necessary as well, but beware of calls that could affect VAOs while this one is bound
		// (like binding element buffer objects, or enabling/disabling vertex attributes)
		// glBindVertexArray(0);

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

			// draw our first triangle
			glUseProgram(shaderProgram);
			glBindVertexArray(VAOs[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindVertexArray(VAOs[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			// Check and call events and swap the buffers
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glDeleteVertexArrays(2, VAOs);
		glDeleteBuffers(2, VBOs);

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

//int main()
//{
//
//	return HelloTriangleChallegeTwo::main();
//
//}