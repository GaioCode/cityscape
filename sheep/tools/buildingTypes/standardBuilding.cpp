#include "standardBuilding.h"



namespace sheep
{
    static const int NUM_VERTICES = 36;
    const int NUM_STANDARD_CUBES = 3;
    std::vector<float> initialYOffsets;

    int StandardBuilding::numStandardBuildings = 0;
    
    StandardBuilding::StandardBuilding(wolf::Program* programParam, const std::string& positionUniformParam)
        : Building(programParam, positionUniformParam)
    {  
        numStandardBuildings++;

        float yOffset = 0.0f;

        int random = rand() % 8 + 3;

        for (int i = 0; i < random; i++)
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

        // Update vertex and index buffers with new data
        createBuffers();

    }

    StandardBuilding::~StandardBuilding()
    {
        numStandardBuildings--;
    }

    void StandardBuilding::render(const std::string& worldUniform, const std::string& projectionViewUniform,
                                  const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        Building::render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
    }
}