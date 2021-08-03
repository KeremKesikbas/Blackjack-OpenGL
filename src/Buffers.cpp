#include "Buffers.hpp"

#include <glad/glad.h>

Buffers::Buffers() {
    m_VBO = 0;
    m_EBO = 0;
    m_VAO = 0;
    
    glGenVertexArrays(1, &m_VAO);

    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

Buffers::~Buffers() {
    if (m_VBO) { glDeleteBuffers(1, &m_VBO); }
    if (m_EBO) { glDeleteBuffers(1, &m_EBO); }
    if (m_VAO) { glDeleteVertexArrays(1, &m_VAO); }
}

void Buffers::activate() {
    glBindVertexArray(m_VAO);
    glEnableVertexAttribArray(m_VBO);
    glEnableVertexAttribArray(m_EBO);
}

void Buffers::deactivate() {
    glBindVertexArray(0);
    glDisableVertexAttribArray(m_VBO);
    glDisableVertexAttribArray(m_EBO);
}

void Buffers::build(const BufferDataList& bufferDatas, const IndexList& indices) {
    glBufferData(GL_ARRAY_BUFFER, sizeof(BufferData) * bufferDatas.size(), &bufferDatas[0], GL_STATIC_DRAW);

    glVertexAttribPointer(POSITION_BUFFER_INDEX, POSITION_VECTOR_SIZE, GL_FLOAT, GL_FALSE, 
                        TOTAL_VECTOR_SIZE * sizeof(float), (void*)POSITION_DATA_STARTING_INDEX);

    glEnableVertexAttribArray(POSITION_BUFFER_INDEX);

    glVertexAttribPointer(TEXTURE_BUFFER_INDEX, TEXTURE_VECTOR_SIZE, GL_FLOAT, GL_FALSE, 
                        TOTAL_VECTOR_SIZE * sizeof(float), (void*)(TEXTURE_DATA_STARTING_INDEX * sizeof(float)));
    
    glEnableVertexAttribArray(TEXTURE_BUFFER_INDEX);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

/////////////////
// TextBuffers
/////////////////

TextBuffers::TextBuffers() {
    glGenVertexArrays(1, &t_VAO);
    glGenBuffers(1, &t_VBO);

    activate();

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    deactivate();
}

void TextBuffers::activate() {
    glBindVertexArray(t_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, t_VBO);
}

void TextBuffers::deactivate() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}