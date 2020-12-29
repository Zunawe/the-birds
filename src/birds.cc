#include <memory>

#include "glm/ext.hpp"

#include "ariamis/engine.h"
#include "ariamis/scene.h"
#include "ariamis/obj_loader.h"
#include "ariamis/light.h"

void setCameraMovement();
Mesh createBirdMesh();

int main(){
	Engine::createWindow("Birds");

	Scene scene;

	std::shared_ptr<Object> bird(new Object());
	bird->renderer.setMesh(createBirdMesh());

	bird->position = glm::vec3(0, 0, 0);

	scene.objects.push_back(bird);

	// Lights
	std::shared_ptr<PointLight> pointLight(new PointLight());
	pointLight->position = glm::vec4(0, 1, -3, 1);
	pointLight->diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
	pointLight->ambient = glm::vec3(0.7f, 0.7f, 0.7f);
	pointLight->specular = glm::vec3(0.4f, 0.4f, 0.4f);
	pointLight->kc = 1.0f;
	pointLight->kl = 0.05f;
	pointLight->kq = 0.001f;
	scene.lights.push_back(pointLight);

	// Input
	Camera &camera = scene.camera;
	Engine::registerKeyEvent(GLFW_KEY_ESCAPE, [](float /*dt*/){
		Engine::quit();
	});

    camera.setPosition(glm::vec3(0, 5, 12));
    camera.lookAt(glm::vec3(0, 0, 0));

	Engine::registerKeyEvent(GLFW_KEY_ESCAPE, [](float /*dt*/){
		Engine::quit();
	});

	Engine::playScene(scene);
}

Mesh createBirdMesh(){
    Mesh mesh;

    mesh.addVertex(glm::vec3(-0.5f, 0.0f, 0.0f));
    mesh.addVertex(glm::vec3(0.5f, 0.25f, 0.25f));
    mesh.addVertex(glm::vec3(0.5f, 0.25f, -0.25f));

    mesh.addVertex(glm::vec3(-0.5f, 0.0f, 0.0f));
    mesh.addVertex(glm::vec3(0.5f, 0.25f, -0.25f));
    mesh.addVertex(glm::vec3(0.5f, -0.25f, -0.25f));

    mesh.addVertex(glm::vec3(-0.5f, 0.0f, 0.0f));
    mesh.addVertex(glm::vec3(0.5f, -0.25f, -0.25f));
    mesh.addVertex(glm::vec3(0.5f, -0.25f, 0.25f));

    mesh.addVertex(glm::vec3(-0.5f, 0.0f, 0.0f));
    mesh.addVertex(glm::vec3(0.5f, -0.25f, 0.25f));
    mesh.addVertex(glm::vec3(0.5f, 0.25f, 0.25f));

    mesh.addVertex(glm::vec3(0.5f, 0.25f, 0.25f));
    mesh.addVertex(glm::vec3(0.5f, -0.25f, -0.25f));
    mesh.addVertex(glm::vec3(0.5f, 0.25f, -0.25f));

    mesh.addVertex(glm::vec3(0.5f, 0.25f, 0.25f));
    mesh.addVertex(glm::vec3(0.5f, -0.25f, 0.25f));
    mesh.addVertex(glm::vec3(0.5f, -0.25f, -0.25f));

    mesh.addTriangle(0, 1, 2);
    mesh.addTriangle(3, 4, 5);
    mesh.addTriangle(6, 7, 8);
    mesh.addTriangle(9, 10, 11);
    mesh.addTriangle(12, 13, 14);
    mesh.addTriangle(15, 16, 17);

    mesh.calculateFaceNormals(false);

    return mesh;
}

void setCameraMovement(Camera &camera){
	float speedMultiplier = 2.0f;
	Engine::registerKeyEvent(GLFW_KEY_W, [&camera, speedMultiplier](float dt){
		camera.moveRelative(glm::vec3(0, 0, 1), dt * speedMultiplier);
	});
	Engine::registerKeyEvent(GLFW_KEY_S, [&camera, speedMultiplier](float dt){
		camera.moveRelative(glm::vec3(0, 0, -1), dt * speedMultiplier);
	});
	Engine::registerKeyEvent(GLFW_KEY_A, [&camera, speedMultiplier](float dt){
		camera.moveRelative(glm::vec3(-1, 0, 0), dt * speedMultiplier);
	});
	Engine::registerKeyEvent(GLFW_KEY_D, [&camera, speedMultiplier](float dt){
		camera.moveRelative(glm::vec3(1, 0, 0), dt * speedMultiplier);
	});
	Engine::registerKeyEvent(GLFW_KEY_SPACE, [&camera, speedMultiplier](float dt){
		camera.moveRelative(glm::vec3(0, 1, 0), dt * speedMultiplier);
	});
	Engine::registerKeyEvent(GLFW_KEY_LEFT_SHIFT, [&camera, speedMultiplier](float dt){
		camera.moveRelative(glm::vec3(0, -1, 0), dt * speedMultiplier);
	});

	// Need to set yaw and pitch based on the original camera position
	float yaw = glm::degrees(atan(camera.getForward().z / camera.getForward().x));
	float pitch = glm::degrees(asin(camera.getForward().y));
	double lastX, lastY;
	float sensitivity = 0.1f;
	glfwGetCursorPos(Engine::getWindow(), &lastX, &lastY);
	Engine::registerMouseMoveEvent([&yaw, &pitch, &lastX, &lastY, &camera, sensitivity](double x, double y){
		double dx = (x - lastX) * sensitivity;
		double dy = (y - lastY) * sensitivity;

		lastX = x;
		lastY = y;

		yaw += dx;
		pitch -= dy;

		yaw = yaw > 360.0f ? yaw - 360.0f : (yaw < 0.0 ? yaw + 360.0f : yaw);
		pitch = pitch > 89.0f ? 89.0f : (pitch < -89.0f ? -89.0f : pitch);

		glm::vec3 cameraForward;
		cameraForward.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		cameraForward.y = sin(glm::radians(pitch));
		cameraForward.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

		camera.setForward(cameraForward);
	});
}
