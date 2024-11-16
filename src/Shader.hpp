#pragma once

#include <glad/glad.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>


class Shader
{

public:
    Shader();
    ~Shader();

    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFile(const char* vertexPath, const char* fragmentPath);
    std::string ReadFile(const char* filePath);

    void UseShader();
    void ClearShaders();

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    
    GLuint GetAmbientIntensityLocation();
    GLuint GetAmbientColourLocation();


private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView;
    GLuint uniformAmbientIntensity, uniformAmbientColor;

    void CompileShaders(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

};