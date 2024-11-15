#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>
#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

static const char* vShader = "../shaders/shader.vert";
static const char* fShader = "../shaders/shader.frag";

const float toRadians = 3.14159265f / 180.0f;
float curAngle = 0.0f;
//bool direction = true;
//float triOffset = 0.0f;
//float triMaxOffset = 0.7;
//float triIncrement = 0.00005f;

void CreateTriangle()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f, //BL
		0.0f, -1.0f, 1.0f,  //back
		1.0f, -1.0f, 0.0f,	//BR
		0.0f, 1.0f, 0.0f	//TOP
	};
	unsigned int indices[] = {
		0, 3, 1,  // side
		1, 3, 2,  // side
		2, 3, 0,  // front face
		0, 1, 2	  // base
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFile(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window();
	mainWindow.Initialize();
    mainWindow.GetOpenGLVersionInfo();
	
    CreateTriangle();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);


	while (!mainWindow.getShouldClose())
	{
		glfwPollEvents();
        glfwSetKeyCallback(mainWindow.getWindow(), glfw_onKey);

        /*if(direction)
            triOffset += triIncrement;
        else
            triOffset -= triIncrement;

        if (abs(triOffset) >= triMaxOffset)
            direction = !direction;

		curAngle += 0.001f;
		if(curAngle >= 360)
			curAngle -= 360;*/

		glClearColor(0.25f, 0.47f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /////////////////////////////////
        shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f,-2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f,-2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		glUseProgram(0);
        ////////////////////////////////

		glfwSwapBuffers(mainWindow.getWindow());
	}

    return 0;
}