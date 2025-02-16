// C++ libraries
#include "glm/detail/type_vec.hpp"
#include <stdio.h>
#include <string.h>

// OpenGL function loader
#include <glad/glad.h>

// Window Manager
#include <GLFW/glfw3.h>

// JoePhys Headers
#include <renderer.hpp>
#include <shapes.hpp>

// functions
void windowResizeCallback(GLFWwindow*, int, int);

struct Window
{
	GLFWwindow* handle = nullptr;
	int width = 800;
	int height = 800;
	std::string title = "JoePhys! (Use WASD + Up Down Left & Right)";
};

Window window;
Renderer renderer;

int main()
{
	// Initialise GLFW
	glfwInit();

	// Create window using GLFW
	window.handle = glfwCreateWindow(window.width, window.height, window.title.c_str(), NULL, NULL);
	if (window.handle == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window.handle);

	// Assign window resize callback function
	glfwSetFramebufferSizeCallback(window.handle, windowResizeCallback);


	// Load all openGL functions using glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Initialise renderer
	renderer.init();

	// TEMPORARY SHAPES
	Circle tempCirc;
	tempCirc.position = glm::vec2(0.0f, 0.0f);
	tempCirc.radius = 50;
	tempCirc.colour = glm::vec4(0.3f, 1.0f, 0.3f, 1.0f);

	Circle tempCircTwo;
	tempCircTwo.position = glm::vec2(0.0f, 0.0f);
	tempCircTwo.radius = 50;
	tempCircTwo.colour = glm::vec4(0.3f, 1.0f, 0.3f, 1.0f);

	Line tempLine;
	tempLine.layer = 1;
	tempLine.thickness = 40;
	tempLine.start_position = glm::vec2(200.0f, -200.0f);
	tempLine.end_position = glm::vec2(100.0f, 200.0f);
	tempLine.colour = glm::vec4(0.3f, 0.3f, 1.0f, 1.0f);

	// game loop
	while (!glfwWindowShouldClose(window.handle))
	{
		// should close window?
		// --------------------
		if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window.handle, true);

		// render scene
		// ------------

		// set background to be red
		glClearColor(0.92f, 0.28f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.renderLine(&tempLine);
		renderer.renderCircle(&tempCirc);
		renderer.renderCircle(&tempCircTwo);

		// TEMPORARY LINE MOVEMENT CODE
		// ----------------------------
		
		if (glfwGetKey(window.handle, GLFW_KEY_UP))
			tempLine.end_position = glm::vec2(tempLine.end_position.x, tempLine.end_position.y + 2.5f);
		if (glfwGetKey(window.handle, GLFW_KEY_DOWN))
			tempLine.end_position = glm::vec2(tempLine.end_position.x, tempLine.end_position.y - 2.5f);

		if (glfwGetKey(window.handle, GLFW_KEY_LEFT))
			tempLine.end_position = glm::vec2(tempLine.end_position.x - 2.5f, tempLine.end_position.y);
		if (glfwGetKey(window.handle, GLFW_KEY_RIGHT))
			tempLine.end_position = glm::vec2(tempLine.end_position.x + 2.5f, tempLine.end_position.y);

		if (glfwGetKey(window.handle, GLFW_KEY_W))
			tempLine.start_position = glm::vec2(tempLine.start_position.x, tempLine.start_position.y + 2.5f);
		if (glfwGetKey(window.handle, GLFW_KEY_S))
			tempLine.start_position = glm::vec2(tempLine.start_position.x, tempLine.start_position.y - 2.5f);

		if (glfwGetKey(window.handle, GLFW_KEY_A))
			tempLine.start_position = glm::vec2(tempLine.start_position.x - 2.5f, tempLine.start_position.y);
		if (glfwGetKey(window.handle, GLFW_KEY_D))
			tempLine.start_position = glm::vec2(tempLine.start_position.x + 2.5f, tempLine.start_position.y);

		tempCirc.position = tempLine.start_position;
		tempCircTwo.position = tempLine.end_position;

		// swap buffers and poll input events
		// ----------------------------------
		glfwSwapBuffers(window.handle);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// This function is called by GLFW every time the window is resized
void windowResizeCallback(GLFWwindow* window_handle, int width, int height)
{
	// Set gl viewport to be the same resolution as our window
	glViewport(0, 0, width, height);
	// Update window width and height variables accordingly
	window.width = width;
	window.height = height;
	// Update renderer's projection matrix so that coordinate system matches window dimensions
	renderer.updateViewMatrix(width, height);
}
