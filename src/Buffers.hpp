#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <glm/glm.hpp>

#include <vector>

#include "types.hpp"

class Buffers {
    public:
        Buffers();
        ~Buffers();

        void build(const BufferDataList& coordinates, const IndexList& indices);

        void activate();
        void deactivate();

    private:
        unsigned int m_VBO;
        unsigned int m_EBO;
        unsigned int m_VAO;
};

class TextBuffers {
    public:
        TextBuffers();

        void activate();
        void deactivate();

    private:
        unsigned int t_VBO;
        unsigned int t_VAO;
};

#endif