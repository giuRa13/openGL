#pragma once

#include "Light.hpp"


class DirectionalLight : public Light
{

public:
    DirectionalLight();
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
        GLfloat aIntensity, GLfloat dIntensity,
        GLfloat xDir, GLfloat yDir, GLfloat zDir);
    ~DirectionalLight();

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
        GLfloat difuseIntensityLocation, GLfloat directionLocation);


private:
    glm::vec3 direction;

};