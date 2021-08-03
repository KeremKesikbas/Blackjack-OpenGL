#ifndef SHAPEFACTORY_HPP
#define SHAPEFACTORY_HPP

#include "Mesh.hpp"

#include <map>

class MeshData {
    public:
        MeshData(Buffers* buffers, unsigned int indexCount);

        Buffers* buffers;
        unsigned int indexCount;
};

class MeshFactory {
    public:
        MeshFactory();

        void loadTriangle();
        void loadRectangle();
        void loadCircle();

        void buildMesh(ShapeType type, BufferDataList bfl, IndexList indices);

        Mesh* createMesh(ShapeType type);

    private:
        std::map<ShapeType, MeshData> loadedShapes;
};

#endif