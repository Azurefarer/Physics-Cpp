#include "user_input/user_input.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// process all input: Query GLFW about certain keys
// on this render loop and react accordigly.
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed 
// (by user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure viewport matches the new window size.
	glViewport(0, 0, width, height);
}
