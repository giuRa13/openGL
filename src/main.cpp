#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>
#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Light.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;
Texture brickTexture;
Texture brickTexture2;
Light mainLight;

static const char* vShader = "../shaders/shader.vert";
static const char* fShader = "../shaders/shader.frag";

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
const float toRadians = 3.14159265f / 180.0f;
float curAngle = 0.0f;
//bool direction = true;
//float triOffset = 0.0f;
//float triMaxOffset = 0.7;
//float triIncrement = 0.00005f;

void CreateTriangle()
{
	GLfloat verticesP[] = { 
		-0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, //left front
		-0.5f, -0.5f, -0.5f, 	1.0f, 0.0f, //left front
		0.5f, -0.5f, -0.5f,  	0.0f, 0.0f, //right back
		0.5f, -0.5f,  0.5f,     1.0f, 0.0f, //right front
		0.0f, 1.5f,  0.0f, 	0.5f, 1.0f // top
	};
	GLuint indicesP[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, //BL
		0.0f, -0.5f, 0.5f,  	0.5f, 0.0f, //back
		0.5f, -0.5f, 0.0f,  	1.0f, 0.0f, ///BR
		0.0f, 0.5f, -0.0f,   	0.5f, 1.0f ///TOP
	};
	unsigned int indices[] = {
		0, 3, 1,  // side
		1, 3, 2,  // side
		2, 3, 0,  // front face
		0, 1, 2	  // base
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(verticesP, indicesP, 25, 18);
	meshList.push_back(obj3);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFile(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialize();
    mainWindow.GetOpenGLVersionInfo();
	
    CreateTriangle();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.0f, 0.005f);

	brickTexture = Texture("../textures/bricks_white.jpg");
	brickTexture.LoadTexture();
	brickTexture2 = Texture("../textures/bricks_yellow.jpg");
	brickTexture2.LoadTexture();

	mainLight = Light(1.0f, 1.0f, 1.0f, 1.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	GLuint uniformAmbientIntensity = 0, uniformAmbientColour = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);


	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime;  // (now - lastTime)*1000 / SDL_GetPerformanceFrequency();
		lastTime = now;

		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        /*if(direction)
			triOffset += triIncrement;
		else
			triOffset -= triIncrement;

		if (abs(triOffset) >= triMaxOffset)
			direction = !direction;

		curAngle += 0.001f;
		if(curAngle >= 360)
			curAngle -= 360;*/

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearColor(0.25f, 0.47f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /////////////////////////////////
        shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();

		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f,-2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f,-2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture2.UseTexture();
		//meshList[1]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f,-3.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		meshList[2]->RenderMesh();

		glUseProgram(0);
        ////////////////////////////////

		//glfwSwapBuffers(mainWindow.getWindow());
		mainWindow.swapBuffers();
	}

    return 0;
}