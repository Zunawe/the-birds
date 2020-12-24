#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>

class Mesh{
    private:
        struct Vertex{
            float x;
            float y;
            float z;
            float nx;
            float ny;
            float nz;

            bool operator==(const Vertex &a) const{
                return x == a.x &&
                    y == a.y &&
                    z == a.z &&
                    nx == a.nx &&
                    ny == a.ny &&
                    nz == a.nz;
            }

            bool operator!=(const Vertex &a) const{
                return !(*this == a);
            }

            Vertex& operator=(const Vertex &a){
                x = a.x;
                y = a.y;
                z = a.z;
                nx = a.nx;
                ny = a.ny;
                nz = a.nz;

                return *this;
            }
        };

        std::vector<Vertex> vertices;
        std::vector<unsigned int> triangles;
    public:
		static const unsigned int VERTEX_SIZE = sizeof(Vertex);

        unsigned int addVertex(float x, float y, float z);
        unsigned int addVertex(glm::vec3 v);
        unsigned int addVertex(float x, float y, float z, float nx, float ny, float nz);
        unsigned int addVertex(glm::vec3 position, glm::vec3 normal);

        void setVertexPosition(unsigned int i, float x, float y, float z);
        void setVertexPosition(unsigned int i, glm::vec3 v);

        void setVertexNormal(unsigned int i, float x, float y, float z);
        void setVertexNormal(unsigned int i, glm::vec3 v);

        void removeVertex(unsigned int i);

        unsigned int addTriangle(unsigned int i1, unsigned int i2, unsigned int i3);
        unsigned int addTriangle(glm::vec3 v);

        void removeTriangle(unsigned int i);

        float* getVertices();
        unsigned int* getIndices();

        unsigned int getNumVertices();
        unsigned int getNumTriangles();
};

#endif
