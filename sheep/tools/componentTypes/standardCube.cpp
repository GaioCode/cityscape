#include "standardCube.h"

namespace sheep
{
    const int NUM_VERTICES = 36;

    StandardCube::StandardCube(wolf::Program* programParam, const std::string& positionUniformParam)
        : Component(programParam, positionUniformParam), positionVBO(nullptr), textureManager(nullptr)
    {
        // Add data to positionVBO

        positionVBO = wolf::BufferManager::CreateVertexBuffer(cubeVertices.data(), sizeof(VertexPositionTexture5D)
            * NUM_VERTICES);

        // Use parent VAO and assign VBOs and Texture Unit to it

        vao->Begin();
        vao->SetVertexBuffer(positionVBO);
        vao->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        vao->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        vao->End();

        // Create Texture for this specific child class

        textureManager = wolf::TextureManager::CreateTexture("data/textures/brick.png");
    }

    StandardCube::~StandardCube()
    {
            wolf::TextureManager::DestroyTexture(textureManager);
            wolf::BufferManager::DestroyBuffer(positionVBO);
    }

    void StandardCube::render(const std::string& worldUniform, const std::string& projectionViewUniform,
    const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        Component::render(worldUniform, projectionViewUniform, projectionViewMatrix);

        // Set texture uniform
        program->SetUniform("tex", 0);		// TODO: Take in from parameter instead of hardcoding

        program->Bind();        // Bind here to fix shifting (wolf issue)

        vao->Bind();
        textureManager->Bind(0);
        glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
    }
}