#include "Cursor.hpp"

#include "TextureManager.hpp"

Cursor::Cursor(int type, GLFWwindow* window) {
    glfwCursor = glfwCreateStandardCursor(type);

    this->window = window;
}

Cursor::Cursor(const char* iconPath, int x, int y, GLFWwindow* window) {
    /*GLFWimage icon;

    int width;
    int height;
    int nrChannels;

    icon.pixels = stbi_load(iconPath, &width, &height, &nrChannels, 0);

    icon.width = width;
    icon.height = height;

    glfwCursor = glfwCreateCursor(&icon, x, y);

    this->window = window;*/
}

void Cursor::destroy() {
    glfwDestroyCursor(glfwCursor);
}

void Cursor::hide() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    disabled = false;
    hiding = true;
}

void Cursor::show() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    hiding = false;
    disabled = false;
}

void Cursor::disable() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    disabled = true;
    hiding = false;
}

GLFWcursor* Cursor::getGLFWcursor() {
    return glfwCursor;
}

bool Cursor::isHiding() {
    return hiding;
}

bool Cursor::isDisabled() {
    return disabled;
}

// cursorManager
GLFWwindow* cursorManager::glfwWindow;

std::vector<Cursor*> cursorManager::cursorList;

Cursor* cursorManager::cursor = nullptr;

void cursorManager::activateCursor(int index) {

    if (cursor != nullptr) {
        cursorList.push_back(cursor);
    }

    cursor = cursorList.at(index);

    glfwSetCursor(glfwWindow, cursor->getGLFWcursor());
}

void cursorManager::createCursor(int type) {
    cursorList.push_back(new Cursor(type, glfwWindow));

    activateCursor(cursorList.size() - 1);
}

void cursorManager::createCursor(const char* iconPath, int x, int y) {
    cursorList.push_back(new Cursor(iconPath, x, y, glfwWindow));

    activateCursor(cursorList.size() - 1);
}

void cursorManager::deleteCursor(int index) {
    cursorList.at(index)->destroy();

    auto it = cursorList.begin() + index;

    cursorList.erase(it);
}