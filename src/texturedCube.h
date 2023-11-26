#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "../sheep/structures/basicStructures.h"

class TexturedCube
{
    public:
       TexturedCube(wolf::Program* programParam, const std::string& positionUniformParam, const std::string& colorUniformParam);

       ~TexturedCube();

       void update(float dt);

       void render(const std::string& worldUniform, const std::string& projectionViewUniform,
       const glm::mat4& projectionViewMatrix);

       void render(const std::string& worldUniform, const std::string& viewUniform, const std::string& projectionUniform,
       const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

        // Set the cube to a new location in world space
        // param x - x value to translate
        // param y - y value to translate
        // param z - z value to translate
        void translate(GLfloat x, GLfloat y, GLfloat z);

        // Change the cube's side length to change the entire cube's size
        // param x - x value to scale
        // param y - y value to scale
        // param z - z value to scale
        void scale(GLfloat x, GLfloat y, GLfloat z);

        // Rotate the cube by its angle and decide whether to rotate in x, y, and/or z
        // param x - Rotate x coordinate in radians (float).
        // param y - Rotate y coordinate in radians (float).
        // param z - Rotate z coordinate in radians (float).
        void rotate(GLfloat x, GLfloat y, GLfloat z);
        
        // Change cube RGB and Alpha value
        // param color - vec4 of red, green, blue, and alpha GLfloat values
        void setColor(const glm::vec4& color);      // TODO: Remove later

    private:
        GLfloat rotateX = 0.0f;
        GLfloat rotateY = 0.0f;
        GLfloat rotateZ = 0.0f;
        glm::vec3 translateVector = glm::vec3(0.0f);
        glm::vec4 colorVector = glm::vec4(0.0f);        // TODO: Remove later
        glm::vec3 scaleVector = glm::vec3(1.0f);
        float time = 0;

};