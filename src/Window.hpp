#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class Window
{

public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);
    ~Window();

    int Initialize();

    GLFWwindow* getWindow() { return mainWindow; }
    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    void swapBuffers() { return glfwSwapBuffers(mainWindow); }

    void GetOpenGLVersionInfo();


private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

};


