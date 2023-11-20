#pragma once
#include "../../wolf/wolf.h"

namespace sheep
{
    class FirstPersonCamera
    {
        public:
            // Initialize program application and get current mouse position.
            FirstPersonCamera(wolf::App* pApp);

            ~FirstPersonCamera();
            void update(float dt);


            // Deduct the current camera position with target (origin) vector to get the actual camera's position.
            void setCameraPosition(glm::vec3 newVector);
            void updateCameraDirection();
            void updateCameraRight();
            void updateCameraUp();
            void setFrontVector(glm::vec3 newVector);
            
            // Returns the projection matrix.
            glm::mat4 getProjectionMatrix(int width, int height);

            // Returns the view matrix.
            glm::mat4 getViewMatrix();
            
            // TODO: Fill up camera methods

        private:
            wolf::App* application = nullptr;
            glm::vec2 lastMousePosition = glm::vec2(0.0f);

            // Perspective values

            float fov = glm::radians(60.0f);
            float nearPlane = 0.1f;
            float farPlane = 1000.0f;

            // View values

            // TODO: Make these value constant so we can edit it, or have it initalized, instead of initializing here
            // Where the camera is at
            glm::vec3 cameraPositionVector = glm::vec3(0.0f);

            // Camera's actual direction after deducting camera position with target
            // (camera's origin direction)
            glm::vec3 cameraDirection = glm::vec3(0.0f);

            // Camera up axis after cross product of x-axis and z-axis
            glm::vec3 cameraUpVector = glm::vec3(0.0f);

            // The positive x-axis of camera space
            glm::vec3 cameraRightVector = glm::vec3(0.0f);

            // the point where the camera looks at
            glm::vec3 cameraFrontVector;

            // The speed where the camera moves
            float cameraSpeed;

            // Time between current and last frame
            float deltaTime;

            // Time of last frame
            float lastFrame;

            // Time of current frame
            float currentFrame;


    };
}

