#include "MeshFactory.hpp"

//////////////////////////
// MeshData
//////////////////////////

MeshData::MeshData(Buffers* buffers, unsigned int indexCount) {
    this->buffers = buffers;
    this->indexCount = indexCount;
}

///////////////////////////////////
// MeshFactory
//////////////////////////////////

MeshFactory::MeshFactory() {
    loadTriangle();
    loadRectangle();
    loadCircle();
}

Mesh* MeshFactory::createMesh(ShapeType type) {
    auto it = loadedShapes.find(type);

    return new Mesh(it->second.buffers, it->second.indexCount);
}

void MeshFactory::buildMesh(ShapeType type, BufferDataList bfl, IndexList indices) {
    Buffers* buffers = new Buffers();

    buffers->build(bfl, indices);

    MeshData sd(buffers, indices.size());
    
    loadedShapes.insert(std::pair<ShapeType, MeshData>(type, sd));
}

void MeshFactory::loadTriangle() {
    BufferDataList bfl;

    BufferData b1;
    BufferData b2;
    BufferData b3;

    b1.position = glm::vec2(-0.5f, 0.0f);
    b2.position = glm::vec2(0.0f, 0.5f);
    b3.position = glm::vec2(0.5f, 0.0f);

    bfl.push_back(b1);
    bfl.push_back(b2);
    bfl.push_back(b3);

    IndexList indices;

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    
    buildMesh(TRIANGLE, bfl, indices);
}

void MeshFactory::loadRectangle() {
    BufferData bfs[4];

    BufferDataList bfl;
    IndexList indices;

    bfs[0].position = glm::vec2(-0.5f, 0.5f);
    bfs[1].position = glm::vec2(-0.5f, -0.5f);
    bfs[2].position = glm::vec2(0.5f, -0.5f);
    bfs[3].position = glm::vec2(0.5f, 0.5f);
    bfs[0].textureCoors = BOTTOM_LEFT;
    bfs[1].textureCoors = TOP_LEFT;
    bfs[2].textureCoors = TOP_RIGHT;
    bfs[3].textureCoors = BOTTOM_RIGHT;

    for (int i = 0; i < 4; i++) {
        bfl.push_back(bfs[i]);
    }

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    buildMesh(RECTANGLE, bfl, indices);
}

void MeshFactory::loadCircle() {
    float detailLevel = 0.3f;

    int vertexCount = (int)(detailLevel * 360.0f);

    float angle = 360.0f/vertexCount;

    int triangleCount = vertexCount - 2;
    
    BufferDataList bfl;
    IndexList indices;

    for (int i = 0; i < vertexCount; i++) {
        float cAngle = angle * i;

        float x = 0.5f * cos(glm::radians(cAngle));
        float y = 0.5f * sin(glm::radians(cAngle));

        BufferData current;

        current.position = glm::vec2(x, y);

        bfl.push_back(current);
    }

    for (int i = 0; i < triangleCount; i++) {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }

    buildMesh(CIRCLE, bfl, indices);
}