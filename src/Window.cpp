#include "Window.hpp"
#include "Input.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

Window::Window()
{
    width = 800;
    height = 600;

	xChange = 0.0f;
	yChange = 0.0f;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
    width = windowWidth;
    height = windowHeight;

	xChange = 0.0f;
	yChange = 0.0f;
}


bool Window::Initialize()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout <<"Error initializing SDL" <<std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    mainWindow = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MAXIMIZED);

    if(mainWindow == nullptr)
    {
        std::cout <<"Error initializing SDL window" <<std::endl;
        return false;
    }

    context = SDL_GL_CreateContext(mainWindow);

    if(context == nullptr)
    {
        std::cout <<"Error initializing OpenGL context" <<std::endl;
        return false;
    }

    gladLoadGL();
    if(!gladLoadGL())
    {
        std::cout <<"Error Glad loading extensions" <<std::endl;
		return false;
    }
   
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init("#version 450");
	ImGui_ImplSDL2_InitForOpenGL(mainWindow, context);

	return true;
}

void Window::Present() //SwapBuffer
{
    SDL_GL_SwapWindow(mainWindow);
}

void Window::Shutdown()
{
	SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

Window::~Window()
{
	Shutdown();
}

void Window::GetOpenGLVersionInfo()
{
    std::cout <<"\nVendor: " <<glGetString(GL_VENDOR) <<std::endl;
    std::cout <<"Renderer: " <<glGetString(GL_RENDERER) <<std::endl;
    std::cout <<"Version: " <<glGetString(GL_VERSION) <<std::endl;
    std::cout <<"Shadong Language: " <<glGetString(GL_SHADING_LANGUAGE_VERSION) <<std::endl;
    std::cout <<"\n";
}



/*void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if(theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//printf("X:%.4f, Y:%.4f\n", theWindow->xChange, theWindow->yChange);
}*/


GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}