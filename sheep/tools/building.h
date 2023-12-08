#pragma once
#include "../../wolf/wolf.h"
#include "../../samplefw/Sample.h"
#include "../structures/basicStructures.h"
#include <vector>
#include <stdexcept>

namespace sheep
{
    class Building
    {
        public:

            Building(wolf::Program* programParam, const std::string& positionUniformParam);

            virtual ~Building() = 0;

            virtual void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                                const std::string& textureUniform, const glm::mat4& projectionViewMatrix) = 0;

            // Set the building to a new location in world space
            // param x - x value to translate
            // param y - y value to translate
            // param z - z value to translate
            void translate(GLfloat x, GLfloat y, GLfloat z);

            // Change the building's side length to change the entire cube's size
            // param x - x value to scale
            // param y - y value to scale
            // param z - z value to scale
            void scale(GLfloat x, GLfloat y, GLfloat z);

            // Rotate the building by its angle and decide whether to rotate in x, y, and/or z
            // param x - Rotate x coordinate in radians (float).
            // param y - Rotate y coordinate in radians (float).
            // param z - Rotate z coordinate in radians (float).
            void rotate(GLfloat x, GLfloat y, GLfloat z);

        protected:
            GLfloat rotateX, rotateY, rotateZ;
            glm::vec3 translateVector, scaleVector;

            // Each building will have a unique ID
            int buildingID;

        private:
            // Increase counter for each new building created. This counter does not decrease if a building is deleted.
            static int buildingIDCount;
    };
}