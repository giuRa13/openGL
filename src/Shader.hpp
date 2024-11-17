#pragma once

#include <glad/glad.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "CommonValues.hpp"


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
    GLuint GetDiffuseIntensityLocation();
    GLuint GetDirectionLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetShininessLocation();
    GLuint GetEyePositionLocation();

    void SetDirectionalLight(DirectionalLight* dLight);
    void SetPointLight(PointLight* pLight, unsigned int lightCount);
    void SetSpotLight(SpotLight* sLight, unsigned int lightCount);


private:
    int pointLightCount;
    int spotLightCount;

    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition;
    //GLuint uniformAmbientIntensity, uniformAmbientColor;
    //GLuint uniformDiffuseIntensity, uniformDirection;
    GLuint uniformSpecularIntensity, uniformShininess;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformDirection;
    }uniformDirectionalLight;

    GLuint uniformPointLightCount;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
    }uniformPointLight[MAX_POINT_LIGHTS];

    GLuint uniformSpotLightCount;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;

        GLuint uniformDirection;
        GLuint uniformEdge;
    }uniformSpotLight[MAX_SPOT_LIGHTS];


    void CompileShaders(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

};