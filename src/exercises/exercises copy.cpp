#include "exercises/exercises.h"
#include <math.h>
#include <iostream>
#include <array>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "user_input/user_input.h"
#include "shader_class/shader_class.h"
#include "stb_image/stb_image.h"
#include "triangle/triangle.h"


// settings
static unsigned int SCR_WIDTH = 1920;
static unsigned int SCR_HEIGHT = 1080;

// GLSL source code
// Moved into their own files, accessed by Shader_Class now

int exercises() {
	// glEnable(GL_DEBUG_OUTPUT);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader our_shader_01
	(
		"./src/shader_source/vertex_shader_practice.vs", 
		"./src/shader_source/fragment_shader_01_practice.fs"
	);
	const auto ready_01 = our_shader_01.ready();
	if (!ready_01) {
		std::cout << "ready " << ready_01 << std::endl;
		return -1;
	}
	Shader our_shader_02(
		"./src/shader_source/vertex_shader_practice.vs", 
		"./src/shader_source/fragment_shader_02_practice.fs"
	);
	const auto ready_02 = our_shader_02.ready();
	if (!ready_01) {
		std::cout << "ready " << ready_02 << std::endl;
		return -1;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float* obj = sphere(1.0f);
	std::array<float, 9> equilateral_triangle = create_triangle_mesh(Triangle::Equilateral);

	std::array<float, 32> vertices1 = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	std::array<float, 18> vertices2 = {
		 1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f,
		 -1.0f, 0.0f, 0.0f,
		 0.0f, -1.0f, 0.0f,
		 0.0f, 0.0f, -1.0f,
	};
	std::array<unsigned int, 30> indices = {
	    0, 1, 2,
		0, 1, 5,
		0, 4, 2,
		0, 4, 5,
		3, 1, 2,
		3, 1, 5,
		3, 4, 2,
		3, 4, 5,
	};

	unsigned int VBO[] = {0, 0}, VAO[] = {0, 0};
	gen_gl_objs(VAO, VBO);

	// first triangle setup
	bind_gl_objs(VAO, VBO, equilateral_triangle);	
	vert_attrib_pointer_config();

	unsigned int EBO[1] = {0};
	write_to_element_buffer(EBO, indices);

	// Texture stuff
	unsigned int texture01 = 0, texture02 = 0;
	// texture 1
	glGenTextures(1, &texture01);
	glBindTexture(GL_TEXTURE_2D, texture01);
	set_texture_params();
	int width = 0, height = 0, nrChannels = 0;
	unsigned char *data1 = stbi_load("../src/container.jpg", &width, &height, &nrChannels, 0);
	if (data1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);

	glGenTextures(1, &texture02);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture02);
	set_texture_params();
	unsigned char* data2 = stbi_load("./src/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data2);

	our_shader_01.use(); // don't forget to activate the shader before setting uniforms!
	// Why are these values passed in as just 1, I don't get what kind fo information is conveyed with this
	our_shader_01.setInt("texture01", 0); // needs to be a zero
	if (our_shader_01.error()) {
		std::cout << "texture01: " << "name does not correspond to an active uniform varible name" << std::endl;
		return -1;
	}
	our_shader_01.setInt("texture02", 1);
	if (our_shader_01.error()) {
		std::cout << "texture02" << "name does not correspond to an active uniform varible name" << std::endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture01);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture02);

		our_shader_01.use();
		float time = glfwGetTime();
		our_shader_01.setFloat("time", time);

		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	std::cout << "out of while loop" << std::endl;
	// glDeleteProgram(our_shader_01.id());
	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteVertexArrays(1, &VAO[1]);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteBuffers(1, &EBO[0]);

	glfwTerminate();
	return 0;
}

// Auxilliary fcts for readability
void gen_gl_objs(unsigned int *VAO, unsigned int *VBO) {
	// Safe, only throws error if the number of objs to gen is negative.
	glGenVertexArrays(sizeof(VAO)/sizeof(VAO[0]), VAO);
	if (sizeof(VAO)/sizeof(VAO[0]) < 0) {
		std::cout << "ERROR: VAO length is negative" << std::endl;
	}
	glGenBuffers(sizeof(VBO)/sizeof(VBO[0]), VBO);
	if (sizeof(VBO)/sizeof(VBO[0]) < 0) {
		std::cout << "ERROR: VBO length is negative" << std::endl;
	}
}

void vert_attrib_pointer_config() {
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void write_to_element_buffer(unsigned int *EBO, std::array<unsigned int, 30> indices) {
	glGenBuffers(1, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
}

void set_texture_params() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// Fcts to create assorted geometries.
float* sphere(float radius) {
	static float out[18];
	int k = 0;
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (i==j) {
				out[k] = radius; // Diagonal matrix construction
				out[k+9] = -radius;
				k++;
			}
			else {out[k] = 0; k++;}
		}
	}
	return out;
}
