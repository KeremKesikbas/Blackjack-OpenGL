#include "Transform.hpp"

#include "stats.hpp"

////////////////////////
// CoordSystem
////////////////////////

CoordSystem* cs::coordSystem;

CoordSystem::CoordSystem(float originX, float originY) {
    this->originX = originX;
    this->originY = originY;

    calculatePixelSize(WIDTH, HEIGHT);
}

void CoordSystem::calculatePixelSize(int width, int height) {
    pixelWidth = 1.0f / (width / 2);
    pixelHeight = 1.0f / (height / 2); 
}

void CoordSystem::translateOrigin(float x, float y) {
    originX += x;
    originY += y;
}

float CoordSystem::getPixelWidth() {
    return pixelWidth;
}

float CoordSystem::getPixelHeight() {
    return pixelHeight;
}

float CoordSystem::getOriginX() {
    return originX;
}

float CoordSystem::getOriginY() {
    return originY;
}

///////////////////
// Shape
///////////////////

Shape::Shape(Mesh* mesh) {
    this->mesh = mesh;
}

/////////////////////////////

void Shape::draw() {
    mesh->draw();
}

/////////////////////////////

void Shape::setRed(float red) {
    mesh->color.r = red / 255.0f;
}

void Shape::setGreen(float green) {
    mesh->color.g = green / 255.0f;
}

void Shape::setBlue(float blue) {
    mesh->color.b = blue / 255.0f;
}

void Shape::setAlpha(float alpha) {
    mesh->color.a = alpha / 255.0f;
}

void Shape::changeRed(float delta) {
    mesh->color.r += delta / 255.0f;
}

void Shape::cangeGreen(float delta) {
    mesh->color.g += delta / 255.0f;
}

void Shape::changeBlue(float delta) {
    mesh->color.b += delta / 255.0f;
}

void Shape::changeAlpha(float delta) {
    mesh->color.a += delta / 255.0f;
}

void Shape::changeColor(float deltaRed, float deltaGreen, float deltaBlue, float deltaAlpha) {
    mesh->color.r += deltaRed / 255.0f;
    mesh->color.g += deltaGreen / 255.0f;
    mesh->color.b += deltaBlue / 255.0f;
    mesh->color.a += deltaAlpha / 255.0f;
}

void Shape::setColor(float red, float green, float blue, float alpha) {
    mesh->color.r = red / 255.0f;
    mesh->color.g = green / 255.0f;
    mesh->color.b = blue / 255.0f;
    mesh->color.a = alpha / 255.0f;
}

float Shape::getRed() {
    return mesh->color.r * 255.0f;
}

float Shape::getGreen() {
    return mesh->color.g * 255.0f;
}

float Shape::getBlue() {
    return mesh->color.b * 255.0f;
}

float Shape::getAlpha() {
    return mesh->color.a * 255.0f;
}

/////////////////////////////

void Shape::setX(float x) {
    float originX = cs::coordSystem->getOriginX() * cs::coordSystem->getPixelWidth();
    float posX = cs::coordSystem->getPixelWidth() * x;
    float xOffset = mesh->scale.x / 2.0f;

    mesh->position.x = posX + xOffset + originX;
}

void Shape::setY(float y) {
    float originY = -cs::coordSystem->getOriginY() * cs::coordSystem->getPixelHeight();
    float posY = -cs::coordSystem->getPixelHeight() * y;
    float yOffset = -mesh->scale.y / 2.0f;

    mesh->position.y = posY + yOffset + originY;
}

void Shape::translateX(float delta) {
    mesh->position.x += cs::coordSystem->getPixelWidth() * delta;
}

void Shape::translateY(float delta) {
    mesh->position.y += cs::coordSystem->getPixelHeight() * delta;
}

void Shape::translate(float deltaX, float deltaY) {
    mesh->position.x += cs::coordSystem->getPixelWidth() * deltaX;
    mesh->position.y += cs::coordSystem->getPixelHeight() * deltaY;
}

void Shape::setPosition(float x, float y) {
    float originX = cs::coordSystem->getOriginX() * cs::coordSystem->getPixelWidth();
    float posX = cs::coordSystem->getPixelWidth() * x;
    float xOffset = mesh->scale.x / 2.0f;

    mesh->position.x = posX + xOffset + originX;

    float originY = -cs::coordSystem->getOriginY() * cs::coordSystem->getPixelHeight();
    float posY = -cs::coordSystem->getPixelHeight() * y;
    float yOffset = -mesh->scale.y / 2.0f;

    mesh->position.y = posY + yOffset + originY;
}

float Shape::getX() {
    float result = mesh->position.x;

    result -= cs::coordSystem->getOriginX() * cs::coordSystem->getPixelWidth();
    result -= mesh->scale.x / 2.0f;

    result /= cs::coordSystem->getPixelWidth();

    return result;
}

float Shape::getY() {
    float result = mesh->position.y;

    result += cs::coordSystem->getOriginY() * cs::coordSystem->getPixelHeight();
    result += mesh->scale.y / 2.0f;

    result /= -cs::coordSystem->getPixelHeight();

    return result;
}

/////////////////////////

void Shape::setWidth(float width) {
    mesh->scale.x = cs::coordSystem->getPixelWidth() * width;
}

void Shape::setHeigth(float height) {
    mesh->scale.y = cs::coordSystem->getPixelHeight() * height;
}

void Shape::changeWidth(float delta) {
    mesh->scale.x += cs::coordSystem->getPixelWidth() * delta;
}

void Shape::changeHeight(float delta) {
    mesh->scale.y += cs::coordSystem->getPixelHeight() * delta;
}

void Shape::changeSize(float deltaWidth, float deltaHeight) {
    mesh->scale.x += cs::coordSystem->getPixelWidth() * deltaWidth;
    mesh->scale.y += cs::coordSystem->getPixelHeight() * deltaHeight;
}

void Shape::setSize(float width, float height) {
    mesh->scale.x = cs::coordSystem->getPixelWidth() * width;
    mesh->scale.y = cs::coordSystem->getPixelHeight() * height;
}

void Shape::scale(float value) {
    mesh->scale.x *= value;
    mesh->scale.y *= value;
}

float Shape::getWidth() {
    return mesh->scale.x / cs::coordSystem->getPixelWidth();
}

float Shape::getHeight() {
    return mesh->scale.y / cs::coordSystem->getPixelHeight();
}

////////////////////////

void Shape::rotate(float delta) {
    mesh->angle += delta;
}

void Shape::setAngle(float angle) {
    mesh->angle = angle;
}

float Shape::getAngle() {
    return mesh->angle;
}

////////////////////////

void Shape::setColorMode(ColorMode mode) {
    mesh->mode = mode;
}

ColorMode Shape::getColorMode() {
    return mesh->mode;
}

///////////////////////

void Shape::addTexture(unsigned int textureID) {
    if (mesh->textures.size() < 1) {
        mesh->textures.push_back(textureID);
    }
}

void Shape::removeTexture(unsigned int textureID) {
    for (int i = 0; i < mesh->textures.size(); i++) {
        if (mesh->textures.at(i) == textureID) {
            auto it = mesh->textures.begin() + i;

            mesh->textures.erase(it);

            break;
        }
    }
}