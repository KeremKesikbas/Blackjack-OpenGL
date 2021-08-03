#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>

#include <glad/glad.h>
#include <glfw3.h>

#include "FrameTimer.hpp"
#include "stats.hpp"

class Window {
    public:
        Window(const char* title, int width, int height);

        const char* getTitle();
        
        int getWidth();
        int getHeight();

        int getRatioX();
        int getRatioY();

        int getX();
        int getY();

        void setWidth(int width);
        void setHeight(int height);

        void setSize(int width, int height);

        void setBackgroundColor(int r, int g, int b);

        void updateRatio();

        void setLocation(int x, int y);

        bool isFullscreen();
        bool isVsyncOn();

        void toggleFullscreen();
        void toggleVysnc();
        
        void hide();
        void show();
        void quit();

        void getFocus();
        void makeContextCurrent();
        void centerLocation();

        void changeMonitor(int index);

        void pollEvents();
        void swapBuffers();

        void windowShouldClose();

        void maximize();

        int getMaxResolutionX();
        int getMaxResolutionY();

        const char* getGLFWversion();
        const char* catchError();

        GLFWwindow* getGLFWwindow();
        GLFWmonitor* getMonitor();

        FrameTimer* frameTimer = new FrameTimer(FRAME_LIMIT);

    private:
        const char* title = TITLE.c_str();

        int width = WIDTH;
        int height = HEIGHT;

        int ratioX = 1;
        int ratioY = 1;

        int x = 0;
        int y = 0;

        int monitorCount;

        int r;
        int g;
        int b;

        bool fullscreen = false;
        bool centered = false;
        bool vsync = false;
        bool maximized = false;

        GLFWwindow* GLFWwindow;
        GLFWmonitor* monitor;

        std::vector<GLFWmonitor*> monitorList;
};

#endif