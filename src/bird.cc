#include <iostream>
#include "bird.h"

Mesh *Bird::mesh = nullptr;
Shader *Bird::shader = nullptr;
unsigned int Bird::VAO = 0;
unsigned int Bird::VBO = 0;
unsigned int Bird::EBO = 0;

void Bird::setMesh(Mesh &m){
    mesh = &m;

    if (VAO == 0){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ARRAY_BUFFER, Mesh::VERTEX_SIZE * mesh->getNumVertices(), mesh->getVertices(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->getNumTriangles() * 3, mesh->getIndices(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
}

void Bird::draw(glm::mat4 view, glm::mat4 projection){
    glm::mat4 model = glm::mat4(1);
	glm::mat4 modelViewProjection = projection * view * model;
	shader->setUniform("modelViewProjection", modelViewProjection);

    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Bird::mesh->getNumTriangles() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Bird::setShader(Shader &s){
    shader = &s;
}
