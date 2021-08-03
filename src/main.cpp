#include <iostream>

#include "ShaderProgram.hpp"
#include "Window.hpp"
#include "stats.hpp"
#include "FrameTimer.hpp"
#include "Buffers.hpp"
#include "MeshFactory.hpp"
#include "Input.hpp"
#include "Cursor.hpp"
#include "TextureManager.hpp"
#include "Transform.hpp"
#include "Fonts.hpp"
#include "shaderSources.hpp"
#include "Graphics.hpp"

#include <glad/glad.h>
#include <algorithm>

using namespace std;

bool init();

void windowEvents();
void windowHints();

void glSettings();

Window* window;

Program* shaderProgram;

MeshFactory* meshFactory;

bool control = true;

Shape* rect;

int main(int argc, char *argv[]) {

    control = init();

    window->frameTimer->isRunning = control;

    int counter = 0;

    while (window->frameTimer->isRunning) {
        glClear(GL_COLOR_BUFFER_BIT);

        windowEvents();
    }

    window->quit();

    return 0;
}

////////////////////////////////////

bool init() {
    if (!glfwInit()) {
        return false;
    }

    windowHints();

    window = new Window(TITLE.c_str(), WIDTH, HEIGHT);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }

    if (window == NULL) {
        glfwTerminate();
        return false;
    }

    window->centerLocation();

    window->setBackgroundColor(30, 30, 30);

    // Input
    inputManager::key_input = new KeyInput(window);
    inputManager::mouse_input = new MouseInput(window);

    // Cursor
    cursorManager::glfwWindow = window->getGLFWwindow();

    // OpenGL Settings
    glSettings();

    // Object Shader Program
    programs::object = new Program();

    if (!programs::object->init(o_vertex_source, o_fragment_source)) {
        return false;
    }

    // Text Shader Program
    programs::text = new Program();

    if (!programs::text->init(t_vertex_source, t_fragment_source)) {
        return false;
    }

    // Init graphics
    cs::coordSystem = new CoordSystem(-(WIDTH/2), -(HEIGHT/2));

    graphics::g = new Graphics(new MeshFactory());

    // Freetype Lib
    if (fonts::init()) {
        return false;
    }

    // Loading Textures
    textureManager::createTextures();

    // Loading Fonts
    fonts::open_sans = new Font("data/fonts/open_sans/", 30);

    graphics::g->setFont(fonts::open_sans);

    fonts::open_sans->changeMode(LIGHT);

    return true;
}

/////////////////////////////////////////////

void windowEvents() {
    window->pollEvents();
    window->swapBuffers();

    window->frameTimer->WaitUntilNext();
    window->frameTimer->countFPS();

    window->windowShouldClose();
}

////////////////////////////////////////////

void windowHints() {
    glfwWindowHint(GLFW_DECORATED, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void glSettings() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}