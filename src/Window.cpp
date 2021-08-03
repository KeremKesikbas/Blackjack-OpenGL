#include "Window.hpp"

#include <algorithm>

Window::Window(const char* title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;

    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    for (int i = 0; i < monitorCount; i++) {
        monitorList.push_back(*monitors);
    }

    monitor = glfwGetPrimaryMonitor();

    GLFWwindow = glfwCreateWindow(width, height, title, NULL, NULL);

    getFocus();
    makeContextCurrent();

    glfwSwapInterval(0);
}

void Window::setWidth(int width) {
    this->width = width;

    glfwSetWindowSize(GLFWwindow, width, height);
    
    updateRatio();
}

void Window::setHeight(int height) {
    this->height = height;

    glfwSetWindowSize(GLFWwindow, width, height);

    updateRatio();
}

void Window::setSize(int width, int height) {
    this->width = width;
    this->height = height;

    glfwSetWindowSize(GLFWwindow, width, height);

    updateRatio();

    if (centered) {
        centerLocation();
    }

    maximized = false;
}

void Window::setLocation(int x, int y) {
    this->x = x;
    this->y = y;

    glfwSetWindowPos(GLFWwindow, x, y);

    centered = false;
}

void Window::setBackgroundColor(int r, int g, int b) {
    float red = (float)r / 255.0f;
    float green = (float)g / 255.0f;
    float blue = (float)b / 255.0f;

    glClearColor(red, green, blue, 1.0f);
}

void Window::show() {
    glfwShowWindow(GLFWwindow);
}

void Window::hide() {
    glfwHideWindow(GLFWwindow);
}

void Window::quit() {
    glfwDestroyWindow(GLFWwindow);
    glfwTerminate();

    frameTimer->destroy();
}

void Window::toggleFullscreen() {
    fullscreen = !fullscreen;

    glfwDestroyWindow(GLFWwindow);

    if (fullscreen) {
        GLFWwindow = glfwCreateWindow(width, height, title, monitor, NULL);
    }
    
    else {
        GLFWwindow = glfwCreateWindow(width, height, title, NULL, NULL);
    }
}

void Window::toggleVysnc() {
    vsync = !vsync;

    frameTimer->setWaiting(!vsync);

    if (vsync) {
        glfwSwapInterval(1);
    }

    else {
        glfwSwapInterval(0);
    }
}

void Window::updateRatio() {
    int gcd = std::__gcd(width, height);

    ratioX = width/gcd;
    ratioY = height/gcd;
}

void Window::getFocus() {
    glfwFocusWindow(GLFWwindow);
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(GLFWwindow);
}

void Window::centerLocation() {
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    if (!mode)
        return;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    x = monitorX + (mode->width - width) / 2;
    y = monitorY + (mode->height - height) / 2;

    glfwSetWindowPos(GLFWwindow, x, y);

    centered = true;
}

void Window::changeMonitor(int index) {
    monitor = monitorList.at(index);
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

int Window::getRatioX() {
    return ratioX;
}

int Window::getRatioY() {
    return ratioY;
}

int Window::getX() {
    return x;
}

int Window::getY() {
    return y;
}

bool Window::isFullscreen() {
    return fullscreen;
}

bool Window::isVsyncOn() {
    return vsync;
}

const char* Window::getTitle() {
    return title;
}

GLFWwindow* Window::getGLFWwindow() {
    return GLFWwindow;
}

GLFWmonitor* Window::getMonitor() {
    return monitor;
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(GLFWwindow);
}

void Window::windowShouldClose() {
    if (glfwWindowShouldClose(GLFWwindow)) {
        quit();
    }
}

void Window::maximize() {
    glfwMaximizeWindow(GLFWwindow);

    maximized = true;
}

int Window::getMaxResolutionX() {
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    return mode->width;
}

int Window::getMaxResolutionY() {
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    return mode->height;
}

const char* Window::getGLFWversion() {
    return glfwGetVersionString();
}

const char* Window::catchError() {
    const char* description;

    glfwGetError(&description);

    return description;
}