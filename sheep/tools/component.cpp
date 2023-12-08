#include "component.h"

namespace sheep
{
    wolf::Program* Component::program = nullptr;
    wolf::VertexDeclaration* Component::vao = nullptr;

    int Component::numComponents = 0;

    Component::Component(wolf::Program* programParam, const std::string& positionUniformParam)
        : rotateX(0.0f), rotateY(0.0f), rotateZ(0.0f), scaleVector(glm::vec3(1.0f)), translateVector(glm::vec3(0.0f))
    {
        numComponents++;

        if (numComponents == 1)
        {
            printf("Component class not initialized. Initializing...\n");

            program = programParam;
            vao = new wolf::VertexDeclaration();

            printf("Successfully initialzed Component class.\n");
        }
    }

    // Pure virtual destructor
    Component::~Component()
    {
        numComponents--;

        if (numComponents == 0)
        {
            printf("Destructing Component class...\n");
            
            delete vao;

            printf("Component class destructed.\n");
        }
    }

    void Component::render(const std::string& worldUniform, const std::string& projectionViewUniform,
                           const glm::mat4& projectionViewMatrix)
    {
        // Convert object space to world space

        glm::mat4 worldMatrix = 
            glm::translate(glm::mat4(1.0f), translateVector) *
            glm::rotate(glm::mat4(1.0f), rotateZ, glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::rotate(glm::mat4(1.0f), rotateY, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), rotateX, glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), scaleVector);

        // Set uniforms
        
        program->SetUniform(projectionViewUniform, projectionViewMatrix);
        program->SetUniform(worldUniform, worldMatrix);
    }

    void Component::translate(GLfloat x, GLfloat y, GLfloat z)
    {
        translateVector = glm::vec3(x, y, z);
    };

    void Component::scale(GLfloat x, GLfloat y, GLfloat z)
    {
        scaleVector = glm::vec3(x, y, z);
    };

    void Component::rotate(GLfloat x, GLfloat y, GLfloat z)
    {
        rotateX = x;
        rotateY = y;
        rotateZ = z;
    };
}