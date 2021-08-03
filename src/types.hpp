#ifndef TYPES_HPP
#define TYPES_HPP

#include <glm/glm.hpp>

#include <vector>

//////////////////////////

const int POSITION_VECTOR_SIZE = 2;
const int POSITION_DATA_STARTING_INDEX = 0;
const int POSITION_BUFFER_INDEX = 0;

/////////////////////////

const int TEXTURE_VECTOR_SIZE = 2;
const int TEXTURE_DATA_STARTING_INDEX = POSITION_VECTOR_SIZE;
const int TEXTURE_BUFFER_INDEX = 1;

//////////////////////////

const int TOTAL_VECTOR_SIZE = 4;

//////////////////////////

enum ShapeType {
    TRIANGLE,
    RECTANGLE,
    CIRCLE,
};

///////////////////////// - Texture coors

const glm::vec2 TOP_LEFT = glm::vec2(0.0f, 1.0f);
const glm::vec2 TOP_RIGHT = glm::vec2(1.0f, 1.0f);
const glm::vec2 BOTTOM_LEFT = glm::vec2(0.0f, 0.0f);
const glm::vec2 BOTTOM_RIGHT = glm::vec2(1.0f, 0.0f);

////////////////////////

enum ColorMode {
    COLOR,
    TEXTURE,
    MIX
};

////////////////////////

class BufferData {
    public:
        glm::vec2 position;
        glm::vec2 textureCoors;
};

typedef std::vector<unsigned int> IndexList;
typedef std::vector<BufferData> BufferDataList;

#endif