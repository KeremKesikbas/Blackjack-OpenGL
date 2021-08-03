#include "Input.hpp"

#include <cstring>
#include <cstdio>

// KeyInput

KeyInput* inputManager::key_input;

bool inputManager::keyPressed(const char* key) {
    char charKey = key[0];

    auto it = inputManager::key_input->keys.find(toupper((int)charKey));

    if (it != inputManager::key_input->keys.end()) {
        if (it->second != GLFW_RELEASE) {
            return true;
        }
    }

    return false;
}

bool inputManager::keyReleased(const char* key) {
    char charKey = key[0];

    auto it = inputManager::key_input->keys.find(toupper((int)charKey));

    if (it != inputManager::key_input->keys.end()) {
        if (it->second == GLFW_RELEASE) {
            return true;
        }
    }

    return false;
}

bool inputManager::keyRepeated(const char* key) {
    char charKey = key[0];

    auto it = inputManager::key_input->keys.find(toupper((int)charKey));

    if (it != inputManager::key_input->keys.end()) {
        if (it->second == GLFW_REPEAT) {
            return true;
        }
    }

    return false;
}

bool inputManager::keyPressed(int key) {
    auto it = inputManager::key_input->keys.find(key);

    if (it != inputManager::key_input->keys.end()) {
        if (it->second != GLFW_RELEASE) {
            return true;
        }
    }

    return false;
}

bool inputManager::keyReleased(int key) {
    auto it = inputManager::key_input->keys.find(key);

    if (it != inputManager::key_input->keys.end()) {
        if (it->second != GLFW_RELEASE) {
            return true;
        }
    }

    return false;
}

bool inputManager::keyRepeated(int key) {
    auto it = inputManager::key_input->keys.find(key);

    if (it != inputManager::key_input->keys.end()) {
        if (it->second != GLFW_RELEASE) {
            return true;
        }
    }

    return false;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {  

    auto it = inputManager::key_input->keys.find(key);

    if (it == inputManager::key_input->keys.end()) {
        inputManager::key_input->keys.insert(std::pair<int, int>(key, action));
    }

    else {
        it->second = action;
    }
}

// MouseInput

MouseInput* inputManager::mouse_input;

bool inputManager::buttonPressed(int button) {
    auto it = inputManager::mouse_input->buttons.find(button);

    if (it != inputManager::mouse_input->buttons.end()) {
        if (it->second != GLFW_RELEASE) {
            return true;
        }
    }

    return false;
}

bool inputManager::buttonReleased(int button) {
    auto it = inputManager::mouse_input->buttons.find(button);

    if (it != inputManager::mouse_input->buttons.end()) {
        if (it->second != GLFW_RELEASE) {
            return true;
        }
    }

    return false;
}

bool inputManager::buttonRepeated(int button) {
    auto it = inputManager::mouse_input->buttons.find(button);

    if (it != inputManager::mouse_input->buttons.end()) {
        if (it->second != GLFW_RELEASE) {
            return true;
        }
    }

    return false;
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    if (inputManager::mouse_input->isOnScreen) {
        inputManager::mouse_input->x = xpos;
        inputManager::mouse_input->y = ypos;
    }

    else {
        inputManager::mouse_input->x = 0.0f;
        inputManager::mouse_input->y = 0.0f;
    }
}

void cursorEnterCallback(GLFWwindow* window, int entered) {
    if (entered) {
        inputManager::mouse_input->isOnScreen = true;
    }

    else {
        inputManager::mouse_input->isOnScreen = false;
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto it = inputManager::mouse_input->buttons.find(button);

    if (it == inputManager::mouse_input->buttons.end()) {
        inputManager::mouse_input->buttons.insert(std::pair<int, int>(button, action));
    }

    else {
        it->second = action;
    }
}

// KeyInput

KeyInput::KeyInput(Window* window) {
    glfwSetKeyCallback(window->getGLFWwindow(), keyCallback);
}

// MouseInput

MouseInput::MouseInput(Window* window) {
    glfwSetCursorPosCallback(window->getGLFWwindow(), cursorPosCallback);
    glfwSetCursorEnterCallback(window->getGLFWwindow(), cursorEnterCallback);
    glfwSetMouseButtonCallback(window->getGLFWwindow(), mouseButtonCallback);
}
