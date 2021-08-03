#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "Transform.hpp"
#include "Fonts.hpp"
#include "Buffers.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Graphics {
    public:
        Graphics(MeshFactory* meshFactory);

        Shape* createRectangle(float width, float height);
        Shape* createOval(float width, float height);

        void renderText(std::string text, float scale);

        void setColor(float r, float g, float b, float a);

        void setPosition(float x, float y);

        void setFont(Font* newFont);

        void translate(float originX, float originY);

        void calculateProjection(float width, float height);

    private:
        CoordSystem* coordSystem;
        MeshFactory* meshFactory;

        float red = 0.0f;
        float green = 0.0f;
        float blue = 0.0f;
        float alpha = 0.0f;

        float x = 0.0f;
        float y = 0.0f;

        Font* currentFont;

        glm::mat4 projection;

        TextBuffers* tb;
};

namespace graphics {
    extern Graphics* g;
}

#endif