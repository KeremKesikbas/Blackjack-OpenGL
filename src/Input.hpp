#ifndef KEYINPUT_HPP
#define KEYINPUT_HPP

#include "Window.hpp"

#include <map>

class KeyInput {
    public:
        KeyInput(Window* window);

        std::map<int, int> keys;
};

class MouseInput {
    public:
        MouseInput(Window* window);

        double x = 0.0f;
        double y = 0.0f;

        bool isOnScreen = false;

        std::map<int, int> buttons;
};

namespace inputManager {
    extern KeyInput* key_input;

    bool keyPressed(const char* key);
    bool keyReleased(const char* key);
    bool keyRepeated(const char* key);

    bool keyPressed(int key);
    bool keyReleased(int key);
    bool keyRepeated(int key);

    //////////////////////////////////

    extern MouseInput* mouse_input;
    
    bool buttonPressed(int button);
    bool buttonReleased(int button);
    bool buttonRepeated(int button);
}

#endif