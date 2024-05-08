#include "tutorial/tutorial.h"
#include <math.h>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "user_input/user_input.h"
#include "shader_class/shader_class.h"

// settings
static unsigned int SCR_WIDTH = 1920;
static unsigned int SCR_HEIGHT = 1080;

int tutorial()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader_01("./Shader_Source/Vertex_Shader_GLTriangles.vs", "./Shader_Source/Fragment_Shader_01_GLTriangles.fs");
	Shader ourShader_02("./Shader_Source/Vertex_Shader_GLTriangles.vs", "./Shader_Source/Fragment_Shader_02_GLTriangles.fs");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float vertices1[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // top  left
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top  right
	};

	float vertices2[] = {
		 -0.75f, -0.75f, 0.0f,
		 -0.75f, -0.25f, 0.0f,
		 -0.5f, -0.25f, 0.0f,
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
	glGenBuffers(2, VBOs);
	// first triangle setup
	// --------------------
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
	// second triangle setup
	// ---------------------
	glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	glEnableVertexAttribArray(0);
	// glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound 
	// (like binding element buffer objects, or enabling/disabling vertex attributes)



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader_01.use();

		float timeValue = glfwGetTime();
		float oscValue = sin(timeValue) / 2.0f + 0.5f;
		ourShader_01.setFloat("colorScale", oscValue);
		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, sizeof(vertices1) / 3, GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);

		//ourShader_02.use();
		//ourShader_02.setFloat("hOffset", 4.0f);
		//glBindVertexArray(VAOs[1]);
		//glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices2) / 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0); // No need to unbind every loop

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
