#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Buffers.hpp"
#include "types.hpp"
#include "ShaderProgram.hpp"

#include <vector>

class Mesh {
    public:
        Mesh(Buffers* buffers, unsigned int indexCount);

        void draw();

        void setUniforms();

        glm::vec2 position = glm::vec2(0.0f, 0.0f);
        glm::vec2 scale = glm::vec2(1.0f, 1.0f);
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        std::vector<unsigned int> textures;

        float angle = 0.0f;

        ColorMode mode = COLOR;

    private:

        Buffers* buffers;

        unsigned int indexCount;
};

#endif