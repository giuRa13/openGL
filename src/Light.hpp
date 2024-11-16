#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


class Light
{

public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
        GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
    ~Light();

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
        GLfloat difuseIntensityLocation, GLfloat directionLocation);


private:
    glm::vec3 colour;
    GLfloat ambientIntensity;

    glm::vec3 direction;
    GLfloat diffuseIntensity;
};