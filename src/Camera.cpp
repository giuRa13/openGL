#include "Camera.hpp"
#include "Input.hpp"


Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
    GLfloat startvelocity, GLfloat startTurnSpeed)
{
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    moveSpeed = startvelocity;
    turnSpeed = startvelocity;

    update();
}

Camera::~Camera()
{ }


void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}


glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::vec3 Camera::getCameraDirection()
{
    return glm::normalize(front);
}

void Camera::keyControl(GLfloat deltaTime)
{
    GLfloat velocity = moveSpeed * deltaTime;

    if(Input::Instance()->IsKeyPressed())
    {
        if(Input::Instance()->GetKeyDown() == 'a')
            position -= right * velocity;
        else if(Input::Instance()->GetKeyDown() == 'd')
            position += right * velocity;
        else if(Input::Instance()->GetKeyDown() == 'w')
            position += front * velocity;
        else if(Input::Instance()->GetKeyDown() == 's')
            position -= front * velocity;
        else if(Input::Instance()->GetKeyDown() == 'i')
            pitch += 1;
        else if(Input::Instance()->GetKeyDown() == 'k')
            pitch -= 1;
        else if(Input::Instance()->GetKeyDown() == 'j')
            yaw -= 1;
        else if(Input::Instance()->GetKeyDown() == 'l')
            yaw += 1; 
    }

    update();
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if(pitch > 89.0f)
        pitch = 89.0f;

    if(pitch < -89.0f)
        pitch = -89.0f;

    update();
}

void Camera::SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport(x, y, width, height);
}