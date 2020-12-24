#include "mesh.h"

unsigned int Mesh::addVertex(float x, float y, float z){
    return addVertex(x, y, z, 0.0f, 0.0f, 0.0f);
}

unsigned int Mesh::addVertex(glm::vec3 v){
    return addVertex(v.x, v.y, v.z, 0.0f, 0.0f, 0.0f);
}

unsigned int Mesh::addVertex(float x, float y, float z, float nx, float ny, float nz){
    Vertex v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.nx = nx;
    v.ny = ny;
    v.nz = nz;

    vertices.push_back(v);
    return vertices.size() - 1;
}

unsigned int Mesh::addVertex(glm::vec3 position, glm::vec3 normal){
    return addVertex(position.x, position.y, position.z, normal.x, normal.y, normal.z);
}

void Mesh::setVertexPosition(unsigned int i, float x, float y, float z) {
    vertices[i].x = x;
    vertices[i].y = y;
    vertices[i].z = z;
}

void Mesh::setVertexPosition(unsigned int i, glm::vec3 v){
    setVertexPosition(i, v.x, v.y, v.z);
}

void Mesh::setVertexNormal(unsigned int i, float x, float y, float z){
    vertices[i].nx = x;
    vertices[i].ny = y;
    vertices[i].nz = z;
}

void Mesh::setVertexNormal(unsigned int i, glm::vec3 v){
    setVertexNormal(i, v.x, v.y, v.z);
}

void Mesh::removeVertex(unsigned int i){
    vertices.erase(vertices.begin() + i);
}

unsigned int Mesh::addTriangle(unsigned int i1, unsigned int i2, unsigned int i3){
    triangles.push_back(i1);
    triangles.push_back(i2);
    triangles.push_back(i3);

    return (triangles.size() / 3) - 1;
}

unsigned int Mesh::addTriangle(glm::vec3 v){
    return addTriangle((unsigned int)v.x, (unsigned int)v.y, (unsigned int)v.z);
}

void Mesh::removeTriangle(unsigned int i){
    triangles.erase(triangles.begin() + i, triangles.begin() + i + 3);
}

float* Mesh::getVertices(){
    return &(vertices[0].x);
}

unsigned int* Mesh::getIndices(){
    return &triangles[0];
}

unsigned int Mesh::getNumVertices(){
    return vertices.size();
}

unsigned int Mesh::getNumTriangles(){
    return triangles.size() / 3;
}
