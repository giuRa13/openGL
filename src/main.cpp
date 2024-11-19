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
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "Material.hpp"
#include "Model.hpp"
#include "Screen.hpp"
#include "Input.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

bool isRunning = true;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 956;
const int CONSOLE_HEIGHT = 250;
const int PROPERTIES_WIDTH = 400;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;
Texture brickTexture;
Texture brickTexture2;
Texture gridTexture;
DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
Material shinyMaterial;
Material dullMaterial;
Model cottage;

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

void calcAverageNormals(unsigned int * indices, unsigned int indexcount, GLfloat * vertices, unsigned int verticesCount, 
	unsigned int vLenght, unsigned int normalOffset)
{
	for(size_t i = 0; i < indexcount; i += 3)
	{
		unsigned int in0 = indices[i] * vLenght;
		unsigned int in1 = indices[i+1] * vLenght;
		unsigned int in2 = indices[i+2] * vLenght;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 +1]- vertices[in0 +1], vertices[in1 +2] -vertices[in0 +2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 +1]- vertices[in0 +1], vertices[in2 +2] -vertices[in0 +2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 +1] += normal.y; vertices[in0 +2] += normal.z; 
		vertices[in1] += normal.x; vertices[in1 +1] += normal.y; vertices[in1 +2] += normal.z; 
		vertices[in2] += normal.x; vertices[in2 +1] += normal.y; vertices[in2 +2] += normal.z; 
	}

	for(size_t i = 0; i < verticesCount / vLenght; i++)
	{
		unsigned int nOffset = i * vLenght + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset +1], vertices[nOffset +2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset +1] = vec.y; vertices[nOffset +2] = vec.z;
	}
}

void CreateTriangle()
{
	GLfloat verticesP[] = { 
		-0.9f, -0.5f,  0.5f,  	0.0f, 0.0f, /*left front*/     0.0f, 0.0f, 0.0f,
		-0.9f, -0.5f, -0.5f, 	1.0f, 0.0f, /*left back*/     0.0f, 0.0f, 0.0f,
		0.9f, -0.5f, -0.5f,  	0.0f, 0.0f, /*right back*/     0.0f, 0.0f, 0.0f,
		0.9f, -0.5f,  0.5f,     1.0f, 0.0f, /*right front*/    0.0f, 0.0f, 0.0f,
		0.0f, 1.0f,  0.0f, 		0.5f, 1.0f, /* top*/           0.0f, 0.0f, 0.0f
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
	   -1.0f, -1.0f, -0.6f,	    0.0f, 0.0f, /*left*/       0.0f, 0.0f, 0.0f,
		0.0f, -1.0f,  1.0f,  	0.5f, 0.0f, /*back*/     0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,  	1.0f, 0.0f, /*right*/       0.0f, 0.0f, 0.0f,
		0.0f,  0.0f,  0.0f,   	0.5f, 1.0f, /*TOP*/      0.0f, 0.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 3, 1,  // side
		1, 3, 2,  // side
		2, 3, 0,  // front face
		0, 1, 2	  // base
	};

	GLfloat floorVertices[] = {
	   -10.0f, 0.0f, -10.0f,	0.0f, 0.0f, /*left back*/        0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,  	10.0f, 0.0f, /*right back*/      0.0f, -1.0f, 0.0f,
	   -10.0f, 0.0f,  10.0f,  	0.0f,  10.0f, /*left front*/     0.0f, -1.0f, 0.0f,
		10.0f, 0.0f,  10.0f,   	10.0f, 10.0f, /*right front*/    0.0f, -1.0f, 0.0f
	};
	unsigned int floorIndices[] = {
		0, 2, 1,   
		1, 2, 3,  
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);
	calcAverageNormals(indicesP, 18, verticesP, 40, 8, 5);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(verticesP, indicesP, 40, 18);
	meshList.push_back(obj3);

	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj4);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFile(vShader, fShader);
	shaderList.push_back(*shader1);
}

void RenderConsoleWindow()
{
	ImGui::Begin("Output console", nullptr,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		//ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

	auto windowPos = ImVec2(0, SCREEN_HEIGHT - CONSOLE_HEIGHT);
	auto windowSize = ImVec2(SCREEN_WIDTH - PROPERTIES_WIDTH, CONSOLE_HEIGHT);
	ImGui::SetWindowPos("Output console", windowPos);
	ImGui::SetWindowSize("Output console", windowSize);

	ImGui::End();
}

int main()
{
	mainWindow = Window(1024, 768);
	mainWindow.Initialize();
    mainWindow.GetOpenGLVersionInfo();
	
    CreateTriangle();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.0f, 0.005f);
	camera.SetViewport(0, 
				CONSOLE_HEIGHT, 
				SCREEN_WIDTH - PROPERTIES_WIDTH,
				SCREEN_HEIGHT - CONSOLE_HEIGHT);

	brickTexture = Texture("../textures/bricks_white.jpg");
	brickTexture.LoadTextureA();
	brickTexture2 = Texture("../textures/bricks_yellow.jpg");
	brickTexture2.LoadTextureA();
	gridTexture = Texture("../textures/g1572.png");
	gridTexture.LoadTextureA();

	shinyMaterial = Material(1.0f, 256);
	dullMaterial = Material(0.3f, 4);

	cottage = Model();
	cottage.LoadModel("../models/girl.obj");

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
								0.1f, 0.1f,  //2.0f, 0.3f
								0.0f, 0.0f, -1.0f); //-1.0f, -2.0f
	
	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
								0.0f, 1.0f,
								0.0f, 0.0f, 0.0f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;
	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
								0.0f, 1.0f,
								-4.0f, 2.0f, 0.0f,
								0.3f, 0.1f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
							  0.0f, 4.0f,
							  0.0f, 0.0f, 0.0f,
							  0.0f, -1.0f, 0.0f,
							  0.3f, 0.2f, 0.1f,
							  20.0f);
	spotLightCount++;
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
							  0.0f, 8.5f,
							  0.0f, 0.0f, 0.0f,
							  -10.0f, -1.0f, 0.0f,
							  1.0f, 0.2f, 0.0f,
							  20.0f);
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	//GLuint uniformAmbientIntensity = 0, uniformAmbientColour = 0;
	//GLuint uniformDiffuseIntensity = 0, uniformDirection = 0;
	GLuint uniformSpecularIntensity = 0, uniformShininess = 0, uniformEyePosition = 0;

	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	while (isRunning)
	{
		GLfloat now =  SDL_GetPerformanceCounter();
		deltaTime = (now - lastTime) / SDL_GetPerformanceFrequency();
		lastTime = now;

		Input::Instance()->Update();
        isRunning = !Input::Instance()->IsXClicked();
		if(Input::Instance()->GetKeyDown() == SDLK_ESCAPE)
            isRunning = false;

		camera.keyControl(deltaTime);
		//camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        /*if(direction)
			triOffset += triIncrement;
		else
			triOffset -= triIncrement;

		if (abs(triOffset) >= triMaxOffset)
			direction = !direction;

		curAngle += 0.001f;
		if(curAngle >= 360)
			curAngle -= 360;*/

		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearColor(0.25f, 0.47f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		RenderConsoleWindow();
		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /////////////////////////////////
        shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.1f;
		//spotLights[0].SetFlash(camera.getCameraPosition(), camera.getCameraDirection()); //attach to camera
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLight(pointLights, pointLightCount);
		shaderList[0].SetSpotLight(spotLights, spotLightCount);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f,-4.0f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f,-5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture2.UseTexture();
		meshList[1]->RenderMesh();

		/*model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.5f,-2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();*/

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		gridTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, -0.5f, -5.0f));
		//model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cottage.RenderModel();


		glUseProgram(0);
        ////////////////////////////////

		mainWindow.Present();
	}

    return 0;
}