#ifndef BIRD_H
#define BIRD_H

#include <glm/gtc/quaternion.hpp>

#include "mesh.h"
#include "shader.h"

class Bird{
    private:
        static Mesh *mesh;
        static Shader *shader;
        static unsigned int VAO;
        static unsigned int VBO;
        static unsigned int EBO;

        glm::vec3 position;
        glm::vec3 scales;
        glm::quat rotation;
    public:
        static void setMesh(Mesh &m);
        static void setShader(Shader &s);

        Bird();
        void translate(glm::vec3 v);
        void scale(glm::vec3 v);
        void scale(float a);
        void rotate(float theta, glm::vec3 axis);
        void draw(glm::mat4 view, glm::mat4 projection);
};

#endif
