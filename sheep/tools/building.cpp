#include "building.h"

namespace sheep
{
    

    wolf::Program* Building::program = nullptr;
    wolf::VertexDeclaration* Building::vao = nullptr;

    int Building::numBuildings = 0;

    Building::Building(wolf::Program* programParam, const std::string& positionUniformParam)
        : rotateX(0.0f), rotateY(0.0f), rotateZ(0.0f), scaleVector(glm::vec3(1.0f)), translateVector(glm::vec3(0.0f))
    {

        numBuildings++;

        if (numBuildings == 1)
        {
            printf("Building class not initialized. Initializing...\n");

            program = programParam;
            vao = new wolf::VertexDeclaration();

            printf("Successfully initialzed Building class.\n");
        }

    }

    // Pure virtual destructor
    Building::~Building()
    {
        numBuildings--;

        if (numBuildings == 0)
        {
            printf("Destructing Building class...\n");
            
            delete vao;

            printf("Building class destructed.\n");
        }
    }

    void Building::render(const std::string& worldUniform, const std::string& projectionViewUniform, 
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

    void Building::translate(GLfloat x, GLfloat y, GLfloat z)
    {
        translateVector = glm::vec3(x, y, z);
    };

    void Building::scale(GLfloat x, GLfloat y, GLfloat z)
    {
        scaleVector = glm::vec3(x, y, z);
    };

    void Building::rotate(GLfloat x, GLfloat y, GLfloat z)
    {
        rotateX = x;
        rotateY = y;
        rotateZ = z;
    };

    
}