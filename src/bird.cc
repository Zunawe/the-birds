#include "bird.h"

#include <math.h>
#include "ariamis/engine.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

Bird::Bird(){
    velocity = glm::vec3(0);

    addBehavior("move", [](Object *o){
        Bird *bird = (Bird*)o;
        float dt = Engine::getDeltaTime();
        bird->position += bird->velocity * dt;
        bird->rotation = glm::quat(1, 0, 0, 0);
        bird->rotate(acos(glm::dot(glm::normalize(bird->velocity), glm::vec3(1, 0, 0))), glm::cross(glm::vec3(1, 0, 0), glm::normalize(bird->velocity)));
    });
}
