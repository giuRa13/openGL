#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


class Camera
{

public:
    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
        GLfloat startMoveSpeed, GLfloat startTurnSpeed);
    ~Camera();

    void keyControl(GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);

    glm::vec3 getCameraPosition();
    glm::mat4 calculateViewMatrix();
    glm::vec3 getCameraDirection();

    void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw; //left/right
    GLfloat pitch; //up/down

    GLfloat moveSpeed;
    GLfloat turnSpeed;

    void update();

};