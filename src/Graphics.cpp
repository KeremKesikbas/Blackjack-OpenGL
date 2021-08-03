#include "Graphics.hpp"

#include "ShaderProgram.hpp"
#include "stats.hpp"

#include <string>
#include <map>

Graphics* graphics::g;

Graphics::Graphics(MeshFactory* meshFactory) {
    this->meshFactory = meshFactory;

    calculateProjection((float)WIDTH, (float)HEIGHT);

    tb = new TextBuffers();
}

Shape* Graphics::createRectangle(float width, float height) {
    Shape* shape = new Shape(meshFactory->createMesh(RECTANGLE));

    shape->setWidth(width);
    shape->setHeigth(height);

    shape->setX(x);
    shape->setY(y);

    shape->setColor(red, green, blue, alpha);

    return shape;
}

Shape* Graphics::createOval(float width, float height) {
    Shape* shape = new Shape(meshFactory->createMesh(CIRCLE));

    shape->setWidth(width);
    shape->setHeigth(height);

    shape->setX(x);
    shape->setY(y);

    shape->setColor(red, green, blue, alpha);

    return shape;
}

#include <iostream>

void Graphics::renderText(std::string text, float scale) {
    programs::text->use();

    glUniformMatrix4fv(programs::text->getUniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform4f(programs::text->getUniform("textColor"), red, green, blue, alpha);

    tb->activate();

    std::map<char, Character> chars = currentFont->getChars();

    float deltaX = x;

    float xOffset = chars[text.at(0)].bearing.x;

    for (int i = 0; i < text.size(); i++) {
        Character ch = chars[text.at(i)];

        float xpos = deltaX + ch.bearing.x * scale - xOffset;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos,     ypos,       0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f }
        };
        
        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        tb->activate();

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        deltaX += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::setColor(float r, float g, float b, float a) {
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

void Graphics::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Graphics::setFont(Font* newFont) {
    currentFont = newFont;
}

void Graphics::translate(float originX, float originY) {
    cs::coordSystem->translateOrigin(originX, originY);
}

void Graphics::calculateProjection(float width, float height) {
    glViewport(0, 0, width, height);

    projection = glm::ortho(0.0f, width, height, 0.0f);
}