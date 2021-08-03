#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Mesh.hpp"
#include "MeshFactory.hpp"

#include <string>

#include <vector>

class CoordSystem {
    public:
        CoordSystem(float originX, float originY);

        void calculatePixelSize(int width, int height);

        void translateOrigin(float x, float y);

        float getPixelWidth();
        float getPixelHeight();

        float getOriginX();
        float getOriginY();

    private:
        float originX;
        float originY;

        float pixelWidth;
        float pixelHeight;
};

class Shape {
    public:
        Shape(Mesh* mesh);

        /////////////////////////////

        void draw();

        /////////////////////////////

        void setRed(float red);
        void setGreen(float green);
        void setBlue(float blue);
        void setAlpha(float alpha);

        void changeRed(float delta);
        void cangeGreen(float delta);
        void changeBlue(float delta);
        void changeAlpha(float delta);

        void changeColor(float deltaRed, float deltaGreen, float deltaBlue, float deltaAlpha);
        void setColor(float red, float green, float blue, float alpha);

        float getRed();
        float getGreen();
        float getBlue();
        float getAlpha();

        /////////////////////////////
        
        void setX(float x);
        void setY(float y);

        void translateX(float delta);
        void translateY(float delta);

        void translate(float deltaX, float deltaY);
        void setPosition(float x, float y);

        float getX();
        float getY();

        /////////////////////////

        void setWidth(float width);
        void setHeigth(float height);

        void changeWidth(float delta);
        void changeHeight(float delta);

        void changeSize(float deltaWidth, float deltaHeight);
        void setSize(float width, float height);

        void scale(float value);

        float getWidth();
        float getHeight();

        ////////////////////////

        void rotate(float delta);
        void setAngle(float angle);

        float getAngle();

        ////////////////////////

        void addTexture(unsigned int textureID);
        void removeTexture(unsigned int textureID);

        void setColorMode(ColorMode mode);

        ColorMode getColorMode();

    private:
        Mesh* mesh;
};

namespace cs {
    extern CoordSystem* coordSystem;
}

#endif