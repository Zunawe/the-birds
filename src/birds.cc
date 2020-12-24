#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "mesh.h"
#include "bird.h"
#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

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

	Camera camera;
	camera.setPosition(glm::vec3(0, 0, 1));
	camera.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

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

    	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);
		bird.draw(camera.getViewMatrix(), projection);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
