#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "mesh.h"

GLFWwindow *window;
int width, height;

/**
 * GLFW callback for when the window is resized. Resets the viewport and records
 * the new width and height.
 */
void resizeWindow(GLFWwindow * /*window*/, int newWidth, int newHeight){
	glViewport(0, 0, newWidth, newHeight);
	width = newWidth;
	height = newHeight;
}

/**
 * Create the GLFW window that will contain the GL context and initialize
 * things that require said context. You should do this before creating any
 * other instances of anything from this library.
 */
GLFWwindow* createWindow(const char *name){
	glfwDestroyWindow(window);

	if(!glfwInit()){
		std::cout << "Failed to initialize GLFW" << std::endl;
		return nullptr;
	}

	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = mode->width;
	height = mode->height;

	window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);

	if(!gladLoadGL()){
		std::cout << "Failed to Load GLAD" << std::endl;
	}

	glfwSetFramebufferSizeCallback(window, resizeWindow);

	return window;
}

/**
 * Closes the window after the current frame finishes rendering.
 */
void quit(){
	glfwSetWindowShouldClose(window, true);
}

int main(){
    createWindow("The Birds");

	glViewport(0, 0, width, height);

	Mesh mesh;

	mesh.addVertex(-0.5f, -0.5f, 0.0f);
	mesh.addVertex(0.5f, -0.5f, 0.0f);
	mesh.addVertex(0.5f, 0.5f, 0.0f);
	mesh.addVertex(-0.5f, 0.5f, 0.0f);
	mesh.addTriangle(0, 2, 3);
	mesh.addTriangle(0, 1, 2);

	Shader shader;
	shader.loadFile("data/vertex.glsl", GL_VERTEX_SHADER);
	shader.loadFile("data/fragment.glsl", GL_FRAGMENT_SHADER);
	shader.link();

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, Mesh::VERTEX_SIZE * mesh.getNumVertices(), mesh.getVertices(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.getNumTriangles() * 3, mesh.getIndices(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);


	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
