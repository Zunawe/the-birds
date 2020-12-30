#include <cstdlib>
#include <ctime>
#include <memory>
#include <iostream>
#include <math.h>

#include "glm/ext.hpp"

#include "ariamis/engine.h"
#include "ariamis/scene.h"
#include "ariamis/obj_loader.h"
#include "ariamis/light.h"
#include "ariamis/material.h"

#include "bird.h"

void setCameraMovement();
Mesh createBirdMesh();
Material createBirdMaterial();
glm::vec3 wind(glm::vec3 position);

glm::vec3 wind(glm::vec3 position, float time){
	float x = pow(cos(0.03 * position.x * position.x), 2);
	float y = 0.0f;
	float z = sin(0.03f * position.x * position.y);
	return glm::vec3((x * cos(time / 10)) - (z * sin(time / 10)), y, (x * sin(time / 10)) + (z * cos(time / 10)));
}

void boids1(Bird &me, const std::vector<std::shared_ptr<Object>> &birds){
	glm::vec3 center(0, 0, 0);
	for(auto it = birds.begin(); it != birds.end(); ++it){
		if((*it).get() != &me){
			if(glm::length((*it)->position - me.position) < 10.0f){
				center += (*it)->position;
			}
		}
	}
	center /= birds.size() - 1;

	me.velocity += (center - me.position) * 0.003f;
}

void boids2(Bird &me, const std::vector<std::shared_ptr<Object>> &birds){
	glm::vec3 avoidance(0, 0, 0);
	for(auto it = birds.begin(); it != birds.end(); ++it){
		if((*it).get() != &me){
			if(glm::length((*it)->position - me.position) < 3.0f){
				avoidance += me.position - (*it)->position;
			}
		}
	}

	me.velocity += avoidance * 0.003f;
}

void boids3(Bird &me, const std::vector<std::shared_ptr<Object>> &birds){
	glm::vec3 direction(0, 0, 0);
	for(auto it = birds.begin(); it != birds.end(); ++it){
		if((*it).get() != &me){
			if(glm::length((*it)->position - me.position) < 7.0f){
				direction += ((Bird*)(*it).get())->velocity;
			}
		}
	}
	direction /= birds.size() - 1;

	me.velocity += direction * 0.0012f;
}

void boids4(Bird &me){
	float boundary = 18.0f;
	if(glm::length(me.position) > boundary){
		me.velocity -= glm::normalize(me.position) * (glm::length(me.position) - boundary) * 0.01f;
	}
}

void boids5(Bird &me){
	float maxSpeed = 10.0f;
	if(glm::length(me.velocity) >= maxSpeed){
		me.velocity = glm::normalize(me.velocity) * maxSpeed;
	}
}

void boids6(Bird &me, float now){
	me.velocity += wind(me.position, now) * 0.016f;
}

float randomFloat(float min, float max){
	return min + (rand() / (RAND_MAX / (max - min)));
}

int main(){
	srand(time(0));

	Engine::createWindow("Birds");
	glClearColor(4.0f / 255.0f, 11.0f / 255.0f, 15.0f / 255.0f, 1.0f);

	Scene scene;

    Mesh birdMesh = createBirdMesh();
	Material birdMaterial = createBirdMaterial();
	glm::vec3 initialVelocity(randomFloat(-3.0f, 3.0f), randomFloat(-3.0f, 3.0f), randomFloat(-3.0f, 3.0f));
    for(unsigned int i = 0; i < 80; ++i){
	    std::shared_ptr<Bird> bird(new Bird());
	    bird->renderer.setMesh(birdMesh);
		bird->renderer.setMaterial(birdMaterial);
        bird->position = glm::vec3(randomFloat(-10.0f, 10.0f), randomFloat(-10.0f, 10.0f), randomFloat(-10.0f, 10.0f));
        bird->velocity = initialVelocity + glm::vec3(randomFloat(-3.0f, 3.0f), randomFloat(-3.0f, 3.0f), randomFloat(-3.0f, 3.0f));
        scene.objects.push_back(bird);

        bird->addBehavior("boids", [&scene](Object *o){
			float now = Engine::getTime();
			Bird *bird = (Bird*)o;

			boids1(*bird, scene.objects);
			boids2(*bird, scene.objects);
			boids3(*bird, scene.objects);
			boids4(*bird);
			boids5(*bird);
			boids6(*bird, now);
        });
    }

	// Lights
	std::shared_ptr<PointLight> pointLight(new PointLight());
	pointLight->position = glm::vec4(0, 0, 0, 1);
	pointLight->diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	pointLight->ambient = glm::vec3(0.4f, 0.4f, 0.4f);
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

    camera.setPosition(glm::vec3(0, 15, 45));
    camera.lookAt(glm::vec3(0, 0, 0));

	Engine::registerKeyEvent(GLFW_KEY_ESCAPE, [](float /*dt*/){
		Engine::quit();
	});

	Engine::playScene(scene);
}

Mesh createBirdMesh(){
    Mesh mesh;

    mesh.addVertex(glm::vec3(0.5f, 0.0f, 0.0f));
    mesh.addVertex(glm::vec3(-0.5f, 0.25f, 0.25f));
    mesh.addVertex(glm::vec3(-0.5f, 0.25f, -0.25f));

    mesh.addVertex(glm::vec3(0.5f, 0.0f, 0.0f));
    mesh.addVertex(glm::vec3(-0.5f, 0.25f, -0.25f));
    mesh.addVertex(glm::vec3(-0.5f, -0.25f, -0.25f));

    mesh.addVertex(glm::vec3(0.5f, 0.0f, 0.0f));
    mesh.addVertex(glm::vec3(-0.5f, -0.25f, -0.25f));
    mesh.addVertex(glm::vec3(-0.5f, -0.25f, 0.25f));

    mesh.addVertex(glm::vec3(0.5f, 0.0f, 0.0f));
    mesh.addVertex(glm::vec3(-0.5f, -0.25f, 0.25f));
    mesh.addVertex(glm::vec3(-0.5f, 0.25f, 0.25f));

    mesh.addVertex(glm::vec3(-0.5f, 0.25f, 0.25f));
    mesh.addVertex(glm::vec3(-0.5f, -0.25f, -0.25f));
    mesh.addVertex(glm::vec3(-0.5f, 0.25f, -0.25f));

    mesh.addVertex(glm::vec3(-0.5f, 0.25f, 0.25f));
    mesh.addVertex(glm::vec3(-0.5f, -0.25f, 0.25f));
    mesh.addVertex(glm::vec3(-0.5f, -0.25f, -0.25f));

    mesh.addTriangle(0, 1, 2);
    mesh.addTriangle(3, 4, 5);
    mesh.addTriangle(6, 7, 8);
    mesh.addTriangle(9, 10, 11);
    mesh.addTriangle(12, 13, 14);
    mesh.addTriangle(15, 16, 17);

    mesh.calculateFaceNormals(false);

    return mesh;
}

Material createBirdMaterial(){
	Material material;
	material.diffuse = glm::vec3(37.0f / 255.0f, 168.0f / 255.0f, 146.0f / 255.0f);
	return material;
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
