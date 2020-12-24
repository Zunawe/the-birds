#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "mesh.h"
#include "bird.h"

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
		throw std::runtime_error("Failed to initialize GLFW");
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
		throw std::runtime_error("Failed to Load GLAD");
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

	Bird::setMesh(mesh);

	Shader shader;
	shader.loadFile("data/vertex.glsl", GL_VERTEX_SHADER);
	shader.loadFile("data/fragment.glsl", GL_FRAGMENT_SHADER);
	shader.link();

	Bird::setShader(shader);

	Bird bird;

	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);

		bird.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
