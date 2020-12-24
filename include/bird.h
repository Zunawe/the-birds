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
    public:
        static void setMesh(Mesh &m);
        static void setShader(Shader &s);

        void draw();
};

#endif
