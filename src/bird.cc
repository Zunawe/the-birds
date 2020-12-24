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

void Bird::setShader(Shader &s){
    shader = &s;
}

Bird::Bird(){
    position = glm::vec3(0);
    scales = glm::vec3(1);
    rotation = glm::quat(1, 0, 0, 0);
}

void Bird::translate(glm::vec3 v){
    position += v;
}

void Bird::scale(glm::vec3 v){
    scales *= v;
}

void Bird::scale(float a){
    scale(glm::vec3(a));
}

void Bird::rotate(float theta, glm::vec3 axis){
    rotation = glm::rotate(rotation, theta, axis);
}

void Bird::draw(glm::mat4 view, glm::mat4 projection){
    glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, position);
	model = glm::scale(model, scales);
	model = ((glm::mat4)rotation) * model;

	glm::mat4 modelViewProjection = projection * view * model;

	shader->setUniform("modelViewProjection", modelViewProjection);

    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Bird::mesh->getNumTriangles() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
