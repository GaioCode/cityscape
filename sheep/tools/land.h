#pragma once
#include "../../wolf/wolf.h"
#include "../../samplefw/Sample.h"
#include "component.h"
#include "../../src/randomNumberGenerator.h"

#include <vector>

namespace sheep
{
    class Land
    {
        public:

            Land(wolf::Program* programParam, const std::string& positionUniformParam, const std::string& texture);

            ~Land();

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                        const std::string& textureUniform, const glm::mat4& projectionViewMatrix);

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

            // Debugging tool to print contents of vertex and index data to console
            void printBufferContents() const; 

            // Debugging tool to print size of vertex and index data to console
            void printBufferSize() const;

        private:

            GLfloat rotateX, rotateY, rotateZ;
            glm::vec3 translateVector, scaleVector;
            
            static wolf::Program* program;
            static wolf::Texture* textureManager;
            static int numLand;

            wolf::VertexDeclaration* vao;
            wolf::VertexBuffer* positionVBO;
            wolf::IndexBuffer* indexBuffer;

            std::vector<VertexPosTex5D> landVertices;
            std::vector<unsigned short> landIndices;
    };
}