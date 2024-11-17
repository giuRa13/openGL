#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


class Light
{

public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);
    ~Light();

    //void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat difuseIntensityLocation);

protected:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};