#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stdio.h>

class Window
{

public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);
    ~Window();

    bool Initialize();
    void Present();
    void Shutdown();

    SDL_Window* getWindow() { return mainWindow; }
    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }

    GLfloat getXChange();
    GLfloat getYChange();

    void GetOpenGLVersionInfo();


private:
    SDL_Window *mainWindow;
    SDL_GLContext context;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;
    void createCallbacks();
    static void handleKeys();
    //static void handleMouse(GLFWwindow* window, double xPos, double yPos);

};


