#include "standardBuilding.h"

namespace sheep
{
    
    StandardBuilding::StandardBuilding(wolf::Program* programParam, const std::string& positionUniformParam)
        : Building(programParam, positionUniformParam)
    {  

        float yOffset = 0.0f;

        RandomNumberGenerator& rng = RandomNumberGenerator::getInstance();
        int random = RandomNumberGenerator::getInstance().getRandomNumber(3, 12);

        // for (int i = 0; i < random; i++)
        // {
        //     // Add vertices for this cube, with yOffset applied to the y component

        //     for (auto vertex : cubeUniqueVertices)
        //     {
        //         vertex.y += yOffset; // Apply yOffset to the y component
        //         buildingVertices.push_back(vertex);
        //     }

        //     // Add indices for this cube, offset by the current number of vertices

        //     unsigned short currentOffset = i * cubeUniqueVertices.size();

        //     for (auto index : cubeIndices)
        //     {
        //         buildingIndices.push_back(index + currentOffset);
        //     }

        //     // For every component generated, raise this value by the component's height
        //     yOffset += 1.0f;
        // }

        // TODO: Fix this problem

        // std::vector<unsigned short> tempIndices = Component::cubeStandardIndices();

        // // Use cubeStandardIndices to get the indices for the standard building
        // buildingIndices.insert(buildingIndices.end(), tempIndices.begin(), tempIndices.end());

        for (int i = 0; i < random; i++)
        {
            // Add vertices for this cube, with yOffset applied to the y component

            std::vector<VertexPosTex5D> tempVertices = 
                Component::cubeStandardVertices(glm::vec3(0.0f, yOffset, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

            buildingVertices.insert(buildingVertices.end(), tempVertices.begin(), tempVertices.end());

            // Add indices for this cube, offset by the current number of vertices

            unsigned short currentOffset = i * cubeUniqueVertices.size();

            for (auto index : cubeIndices)
            {
                buildingIndices.push_back(index + currentOffset);
            }

            // For every component generated, raise this value by the component's height
            yOffset += 1.0f;
        }

        // Create vertex and index buffers
        createBuffers();

    }

    StandardBuilding::~StandardBuilding()
    {
        
    }

    void StandardBuilding::render(const std::string& worldUniform, const std::string& projectionViewUniform,
                                  const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        Building::render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
    }
}