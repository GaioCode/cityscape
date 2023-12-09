#pragma once
#include "../../wolf/wolf.h"
#include "../../samplefw/Sample.h"
#include "component.h"
#include <vector>

namespace sheep
{
    class Building
    {
        public:

            Building(wolf::Program* programParam, const std::string& positionUniformParam);

            virtual ~Building() = 0;

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                        const glm::mat4& projectionViewMatrix);

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

            static wolf::Program* program;
            static wolf::VertexDeclaration* vao;

            std::vector<VertexPositionTexture5D> buildingVertices;
            std::vector<unsigned short> buildingIndices;

        private:

            static int numBuildings;
    };
}