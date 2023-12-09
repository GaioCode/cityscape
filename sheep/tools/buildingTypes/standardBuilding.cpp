#include "standardBuilding.h"

namespace sheep
{
    static const int NUM_VERTICES = 36;
    const int NUM_STANDARD_CUBES = 3;
    std::vector<float> initialYOffsets;

    wolf::VertexBuffer* StandardBuilding::positionVBO = nullptr;
    wolf::IndexBuffer* StandardBuilding::indexBuffer = nullptr;
    wolf::Texture* StandardBuilding::textureManager = nullptr;

    int StandardBuilding::numStandardBuildings = 0;
    
    StandardBuilding::StandardBuilding(wolf::Program* programParam, const std::string& positionUniformParam)
        : Building(programParam, positionUniformParam)
    {  
        numStandardBuildings++;

        float yOffset = 0.0f;

        for (int i = 0; i < NUM_STANDARD_CUBES; i++)
        {
            // Add vertices for this cube, with yOffset applied to the y component
            for (auto vertex : cubeUniqueVertices)
            {
                vertex.y += yOffset; // Apply yOffset to the y component
                buildingVertices.push_back(vertex);
            }

            // Add indices for this cube, offset by the current number of vertices
            unsigned short currentOffset = i * cubeUniqueVertices.size();
            for (auto index : cubeIndices)
            {
                buildingIndices.push_back(index + currentOffset);
            }

            // For every component generated, raise this value by the component's height
            yOffset += 1.0f;
        }

        if (numStandardBuildings == 1)
        {
            printf("StandardBuilding class not initialized. Initializing...\n");

            // printf("%f, %f\n", buildingVertices.size(), buildingIndices.size());

            // Add data to positionVBO

            positionVBO = wolf::BufferManager::CreateVertexBuffer(buildingVertices.data(), sizeof(VertexPositionTexture5D)
                * buildingVertices.size());

            // Create Index Buffer Object (IBO)
            indexBuffer = wolf::BufferManager::CreateIndexBuffer(buildingIndices.data(), buildingIndices.size());

            // Use parent VAO and assign VBOs and Texture Unit to it

            vao->Begin();
            vao->SetVertexBuffer(positionVBO);
            vao->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
            vao->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
            vao->End();

            // Create Texture for this specific child class

            textureManager = wolf::TextureManager::CreateTexture("data/textures/brick.png");

            printf("Successfully initialzed StandardBuilding class.\n");
        }

    }

    StandardBuilding::~StandardBuilding()
    {
        numStandardBuildings--;

        if (numStandardBuildings == 0)
        {
             printf("Destructing StandardBuilding class...\n");

            wolf::TextureManager::DestroyTexture(textureManager);
            wolf::BufferManager::DestroyBuffer(positionVBO);
            wolf::BufferManager::DestroyBuffer(indexBuffer);

            printf("StandardBuilding class destructed.\n");
        }
    }

    void StandardBuilding::render(const std::string& worldUniform, const std::string& projectionViewUniform,
    const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        Building::render(worldUniform, projectionViewUniform, projectionViewMatrix);

        // Set texture uniform

        program->SetUniform("tex", 0);

        program->Bind();        // Bind here to fix shifting (wolf issue)

        vao->Bind();
        textureManager->Bind(0);
        indexBuffer->Bind();
        // glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
        glDrawElements(GL_TRIANGLES, buildingIndices.size(), GL_UNSIGNED_SHORT, 0);

    }
}