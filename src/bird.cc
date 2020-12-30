#include "bird.h"

#include "ariamis/engine.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

Bird::Bird(){
    velocity = glm::vec3(0);

    addBehavior("move", [](Object *o){
        Bird *bird = (Bird*)o;
        float dt = Engine::getDeltaTime();
        bird->position += bird->velocity * dt;
        // bird->rotation = glm::quatLookAt(glm::normalize(bird->velocity - glm::vec3(1, 0, 0)), glm::vec3(0, 1, 0));
    });
}
