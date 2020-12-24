#ifndef BIRD_H
#define BIRD_H

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
        glm::vec3 scale;
        glm::vec3 rotation;
    public:
        static void setMesh(Mesh &m);
        static void setShader(Shader &s);

        void draw(glm::mat4 view, glm::mat4 projection);
};

#endif
