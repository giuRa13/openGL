#include "Light.hpp"


Light::Light() 
{ 
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
{
    colour = glm::vec3(red, green, blue);
    ambientIntensity = aIntensity;
}

Light::~Light(){ }


void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation)
{
    // bind the 3 colour value to ambientColorLocation
    glUniform3f(ambientColorLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
}