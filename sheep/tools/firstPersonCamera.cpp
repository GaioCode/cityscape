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
    const glm::vec3 INITIAL_CAMERA_POSITION = glm::vec3(0.0f, 0.0f, 4.0f);

    // Defefault position where the camera looks
    const glm::vec3 INITIAL_LOOK_AT = glm::vec3(0.0f, 0.0f, 0.0f);

    // Default initial camera yaw position
    const float INITIAL_YAW = -90.0f;

    // DEfault initial camera pitch position
    const float INITIAL_PITCH = 9.0f;

    // Affects how much the camera moves when the mouse moves
    const float MOUSE_SENSITIVITY = 0.1f;

    // Set how long a barrel roll should last
    const float BARREL_ROLL_DURATION = 5.0f;

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

        cameraPositionVector = INITIAL_CAMERA_POSITION;
        updateCameraDirection();
        updateCameraRight();
        updateCameraUp();
        cameraFrontVector = glm::normalize(INITIAL_LOOK_AT - INITIAL_CAMERA_POSITION);

        yaw = INITIAL_YAW;
        pitch = INITIAL_PITCH;

        mouseLastPosition = application->getMousePos();

        // Set cursor at the middle of the screen at all times
        glfwSetInputMode(application->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    FirstPersonCamera::~FirstPersonCamera()
    {

    }

    void FirstPersonCamera::update(float dt)
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Keyboard WASD camera movements

        // Make the camera move faster when sprint key is pressed

        if (application->isKeyDown(341))    // Left Control
            cameraSpeed = CAMERA_SPEED_SPRINT * deltaTime;
        else
            cameraSpeed = CAMERA_SPEED_NORMAL * deltaTime;

        // WASD camera movements

        glm::vec3 forwardVectorNoY = glm::normalize(glm::vec3(cameraFrontVector.x, 0.0f, cameraFrontVector.z));
        glm::vec3 rightVectorNoY = glm::normalize(glm::cross(forwardVectorNoY, UP_VECTOR));

        if (application->isKeyDown('w'))
        {
            cameraPositionVector += cameraSpeed * forwardVectorNoY;
        }
        if (application->isKeyDown('s'))
        {
            cameraPositionVector -= cameraSpeed * forwardVectorNoY;
        }
        if (application->isKeyDown('a'))
        {
            cameraPositionVector -= rightVectorNoY * cameraSpeed;
        }
        if (application->isKeyDown('d'))
        {
            cameraPositionVector += rightVectorNoY * cameraSpeed;
        }
        
        // Ascend/descend camera movements

        if (application->isKeyDown(32))   // Spacebar
        {
            cameraPositionVector.y += cameraSpeed;
        }
        if (application->isKeyDown(340))     // Left Shift
        {
            cameraPositionVector.y -= cameraSpeed;
        }

        // Mouse camera movements

        mouseCallback(application->getMousePos());

        // Barrel Rolling

        if (application->isKeyDown('b') && !isBarrelRolling)
        {
            isBarrelRolling = true;
            barrelRollStartTime = glfwGetTime();
        }

    }

    void FirstPersonCamera::setCameraPosition(glm::vec3 newVector)
    {
        cameraPositionVector = newVector;
    }

    void FirstPersonCamera::updateCameraDirection()
    {
        cameraDirection = glm::normalize(cameraPositionVector - CAMERA_TARGET_VECTOR);
    }

    void FirstPersonCamera::updateCameraRight()
    {
        cameraRightVector = glm::normalize(glm::cross(UP_VECTOR, cameraDirection));
    }

    void FirstPersonCamera::updateCameraUp()
    {
        cameraUpVector = glm::cross(cameraDirection, cameraRightVector);
    }

    void FirstPersonCamera::mouseCallback(glm::vec2 mousePosition)
    {
        // Get current mouse position to prevent screen from suddenly jumping to current mouse position on initial
        // mouse movement
        if (isFirstMouseInput)
        {
            mouseLastPosition = mousePosition;
            isFirstMouseInput = GL_FALSE;
        }

        glm::vec2 mousePositionOffset;
        mousePositionOffset.x = mousePosition.x - mouseLastPosition.x;
        mousePositionOffset.y = mouseLastPosition.y - mousePosition.y;
        mouseLastPosition = mousePosition;

        mousePositionOffset = mousePositionOffset * MOUSE_SENSITIVITY;

        yaw += mousePositionOffset.x;
        pitch += mousePositionOffset.y;

        // Prevent camera from going out of bounds
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
                
        if (yaw > 180.0f)
            yaw = -180.0f;
        if (yaw < -180.0f)
            yaw = 180.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        cameraFrontVector = glm::normalize(direction);
    }

    glm::mat4 FirstPersonCamera::getProjectionMatrix(int width, int height)
    {
        return glm::perspective(fov, (float)width / (float)height, nearPlane, farPlane);
    }

    glm::mat4 FirstPersonCamera::getViewMatrix()
    {
        glm::vec3 up = cameraUpVector;

        if (isBarrelRolling)
        {
            float elapsedTime = glfwGetTime() - barrelRollStartTime;
            if (elapsedTime < BARREL_ROLL_DURATION)
            {
                roll = -(360.0f / BARREL_ROLL_DURATION) * elapsedTime;
                glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(roll), cameraFrontVector);
                up = glm::vec3(rotation * glm::vec4(cameraUpVector, 0.0f));
            }
            else
            {
                isBarrelRolling = false;
                roll = 0.0f;
            }
        }

        return glm::lookAt(cameraPositionVector, cameraPositionVector + cameraFrontVector, up);   
    }

    void FirstPersonCamera::printCameraInfo() const
    {
        std::cout << "Camera Position: " << glm::to_string(cameraPositionVector);
        std::cout << ", Camera Front: " << glm::to_string(cameraFrontVector);
        printf(", pitch: %f, yaw: %f\n", pitch, yaw);
    }
}