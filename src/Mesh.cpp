#include "Mesh.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include "TextureManager.hpp"

//////////////////////////
// Mesh
//////////////////////////

Mesh::Mesh(Buffers* buffers, unsigned int indexCount){
    this->buffers = buffers;
    this->indexCount = indexCount;
}

// Drawing Functions

void Mesh::draw() {
    programs::object->use();

    if (mode != COLOR) {
        for (int i = 0; i < textures.size(); i++) {
            textureManager::activateTexture(textures.at(i), i);
        }
    }

    buffers->activate();

    setUniforms();

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    if (mode != COLOR) {
        for (int i = 0; i < textures.size(); i++) {
            textureManager::deactivateTexture(i);
        }
    }

    buffers->deactivate();
}

void Mesh::setUniforms() {
    // Color
    glUniform4fv(programs::object->getUniform("color"), 1, (GLfloat*)&color);
    glUniform1i(programs::object->getUniform("mode"), (GLint)mode);

    // Translation
    auto mtxPosition = glm::translate(glm::mat3(1), position);

    glUniformMatrix3fv(programs::object->getUniform("translate"), 1, false, (GLfloat*)&mtxPosition);

    // Angle
    auto mtxAngle = glm::rotate(glm::mat3(1), glm::radians(angle));

    glUniformMatrix3fv(programs::object->getUniform("angle"), 1, false, (GLfloat*)&mtxAngle);

    // Scale
    auto mtxScale = glm::scale(glm::mat3(1), scale);

    glUniformMatrix3fv(programs::object->getUniform("scale"), 1, false, (GLfloat*)&mtxScale);
}