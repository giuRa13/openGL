#include "Light.hpp"


Light::Light() 
{ 
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;

    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
    GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
    colour = glm::vec3(red, green, blue);
    ambientIntensity = aIntensity;

    direction = glm::vec3(xDir, yDir, zDir);
    diffuseIntensity = dIntensity;
}

Light::~Light(){ }


void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
    GLfloat difuseIntensityLocation, GLfloat directionLocation)
{
    // bind the 3 colour value to ambientColorLocation
    glUniform3f(ambientColorLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);

    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(difuseIntensityLocation, diffuseIntensity);
}