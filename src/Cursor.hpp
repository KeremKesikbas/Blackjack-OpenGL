#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <glfw3.h>

#include <vector>

class Cursor {
    public:
        Cursor(int type, GLFWwindow* window);
        Cursor(const char* iconPath, int x, int y, GLFWwindow* window);

        void destroy();

        void hide();
        void show();
        void disable();

        GLFWcursor* getGLFWcursor();

        bool isHiding();
        bool isDisabled();

    private:
        bool hiding = false;
        bool disabled = false;

        GLFWcursor* glfwCursor;
        GLFWwindow* window;
};

namespace cursorManager {
    extern GLFWwindow* glfwWindow;

    extern std::vector<Cursor*> cursorList;

    extern Cursor* cursor;

    void createCursor(int type);
    void createCursor(const char* iconPath, int x, int y);

    void activateCursor(int index);

    void deleteCursor(int index);
}

#endif