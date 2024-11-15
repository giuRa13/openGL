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


private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView;

    void CompileShaders(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

};