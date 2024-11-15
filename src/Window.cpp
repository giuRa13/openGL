#include "Window.hpp"
#include <iostream>

Window::Window()
{
    width = 800;
    height = 600;

	for(size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
    width = windowWidth;
    height = windowHeight;

	for(size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;
}


int Window::Initialize()
{
    if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(mainWindow);
	createCallbacks();
	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init Glad" << std::endl;
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}


Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

void Window::GetOpenGLVersionInfo()
{
    std::cout <<"\nVendor: " <<glGetString(GL_VENDOR) <<std::endl;
    std::cout <<"Renderer: " <<glGetString(GL_RENDERER) <<std::endl;
    std::cout <<"Version: " <<glGetString(GL_VERSION) <<std::endl;
    std::cout <<"Shadong Language: " <<glGetString(GL_SHADING_LANGUAGE_VERSION) <<std::endl;
    std::cout <<"\n";
}


void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}


void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if(key >= 0 && key < 1024)
	{
		if(action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("Presssed: key n°%d\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("Released: key n°%d\n", key);
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
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
}


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