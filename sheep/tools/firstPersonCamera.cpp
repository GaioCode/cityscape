#include "firstPersonCamera.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace sheep
{
    // Changeable constant values:

    // WASD camera movement speed
    const float CAMERA_SPEED_NORMAL = 2.0f;

    // WASD camera movement speed when holding down LeftShift
    const float CAMERA_SPEED_SPRINT = 10.0f;

    // Default position when camera initially loads
    const glm::vec3 CAMERA_POSITION_VECTOR = glm::vec3(0.0f, 0.0f, 4.0f);

    // =================================================================================================================
    // =================================================================================================================

    // The original camera's direction.
    const glm::vec3 CAMERA_TARGET_VECTOR = glm::vec3(0.0f);

    // Default up vector
    const glm::vec3 UP_VECTOR = glm::vec3(0.0f, 1.0f, 0.0f);

    FirstPersonCamera::FirstPersonCamera(wolf::App* pApp) : application(pApp)
    {
        lastMousePosition = application->getMousePos();

        cameraSpeed = CAMERA_SPEED_NORMAL;

        // Initialize view values (in this chronological order):

        this->setCameraPosition(CAMERA_POSITION_VECTOR);
        this->updateCameraDirection();
        this->updateCameraRight();
        this->updateCameraUp();
        this->setFrontVector(glm::vec3(0.0f, 0.0f, -1.0f));
    }

    FirstPersonCamera::~FirstPersonCamera()
    {

    }

    void FirstPersonCamera::update(float dt)
    {
        this->currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (application->isKeyDown(340))
            cameraSpeed = CAMERA_SPEED_SPRINT * deltaTime;
        else
            cameraSpeed = CAMERA_SPEED_NORMAL * deltaTime;

        // TODO: Mouse position

        if (application->isKeyDown('w'))
        {
            this->setCameraPosition(this->cameraPositionVector + cameraSpeed * cameraFrontVector);
        }
        if (application->isKeyDown('s'))
        {
            this->setCameraPosition(this->cameraPositionVector - cameraSpeed * cameraFrontVector);
        }
        if (application->isKeyDown('a'))
        {
            this->setCameraPosition(this->cameraPositionVector - 
            glm::normalize(glm::cross(this->cameraFrontVector, this->cameraUpVector)) * this->cameraSpeed);
        }
        if (application->isKeyDown('d'))
        {
            this->setCameraPosition(this->cameraPositionVector + 
            glm::normalize(glm::cross(this->cameraFrontVector, this->cameraUpVector)) * this->cameraSpeed);
        }
    }

    void FirstPersonCamera::setCameraPosition(glm::vec3 newVector)
    {
        this->cameraPositionVector = newVector;
    }

    void FirstPersonCamera::updateCameraDirection()
    {
        this->cameraDirection = glm::normalize(this->cameraPositionVector - CAMERA_TARGET_VECTOR);
    }

    void FirstPersonCamera::updateCameraRight()
    {
        this->cameraRightVector = glm::normalize(glm::cross(UP_VECTOR, this->cameraDirection));
    }

    void FirstPersonCamera::updateCameraUp()
    {
        this->cameraUpVector = glm::cross(this->cameraDirection, this->cameraRightVector);
    }

    void FirstPersonCamera::setFrontVector(glm::vec3 newVector)
    {
        this->cameraFrontVector = newVector;
    }

    glm::mat4 FirstPersonCamera::getProjectionMatrix(int width, int height)
    {
        return glm::perspective(fov, (float)width / (float)height, this->nearPlane, this->farPlane);
    }

    glm::mat4 FirstPersonCamera::getViewMatrix()
    {

        // std::cout<<glm::to_string()<<std::endl;

        // return glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        return glm::lookAt(this->cameraPositionVector, this->cameraPositionVector + this->cameraFrontVector, 
        this->cameraUpVector);
        
    }
}