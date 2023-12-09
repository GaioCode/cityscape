#include "standardCube.h"

namespace sheep
{
    static const int NUM_VERTICES = 36;
    wolf::VertexBuffer* StandardCube::positionVBO = nullptr;
    wolf::IndexBuffer* StandardCube::indexBuffer = nullptr;
    wolf::Texture* StandardCube::textureManager = nullptr;
    int StandardCube::numChildComponents = 0;

    StandardCube::StandardCube(wolf::Program* programParam, const std::string& positionUniformParam)
        : Component(programParam, positionUniformParam)
    {
        numChildComponents++;

        if (numChildComponents == 1)
        {
            printf("StandardCube class not initialized. Initializing...\n");

            // Add data to positionVBO

            positionVBO = wolf::BufferManager::CreateVertexBuffer(uniqueCubeVertices.data(), sizeof(VertexPositionTexture5D)
                * NUM_VERTICES);

            // Create Index Buffer Object (IBO)
            indexBuffer = wolf::BufferManager::CreateIndexBuffer(cubeIndices.data(), cubeIndices.size());

            // Use parent VAO and assign VBOs and Texture Unit to it

            vao->Begin();
            vao->SetVertexBuffer(positionVBO);
            vao->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
            vao->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
            vao->End();

            // Create Texture for this specific child class

            textureManager = wolf::TextureManager::CreateTexture("data/textures/brick.png");

            printf("Successfully initialzed StandardCube class.\n");
        }
    }

    StandardCube::~StandardCube()
    {
        numChildComponents--;

        if (numChildComponents == 0)
        {
            printf("Destructing StandardCube class...\n");

            wolf::TextureManager::DestroyTexture(textureManager);
            wolf::BufferManager::DestroyBuffer(positionVBO);

            printf("StandardCube class destructed.\n");

        }
    }

    void StandardCube::render(const std::string& worldUniform, const std::string& projectionViewUniform,
    const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        Component::render(worldUniform, projectionViewUniform, projectionViewMatrix);

        // Set texture uniform
        program->SetUniform("tex", 0);

        program->Bind();        // Bind here to fix shifting (wolf issue)

        vao->Bind();
        textureManager->Bind(0);
        indexBuffer->Bind();
        // glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
        glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_SHORT, 0);
    }
}