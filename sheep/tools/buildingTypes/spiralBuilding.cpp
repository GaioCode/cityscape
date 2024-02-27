#include "spiralBuilding.h"

namespace sheep
{
    
    SpiralBuilding::SpiralBuilding(wolf::Program* programParam, const std::string& positionUniformParam,
                                       const std::string& texture, int baseHeight, int spiralHeight,
                                       const TextureSet& textureSet, const TextureSet& quarterTextureSet)
        : Building(programParam, positionUniformParam, texture, textureSet)
    {  

        float yOffset = 0.0f;
        float rotateOffset = 0.0f;
        float spiralSize = 1.0f;
        const float SIZE_RATIO = 1.0f / (spiralHeight + 3);
        std::vector<VertexPosTex5D> tempVertices;

        // Base
        
        for (int i = 0; i < baseHeight + spiralHeight; i++)
        {
            // Add base first. Then, add spirals

            if (i < baseHeight - 1)
            {
                tempVertices = Component::cubeStandardVertices(glm::vec3(0.0f, yOffset, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
                yOffset += 1.0f;
            }
            else if (i < baseHeight)
            {
                tempVertices = Component::cubeStandardVertices(glm::vec3(0.0f, yOffset, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
                yOffset += 0.6f;
            }
            else
            {
                // Reinitialize to accomodate quarterTextureSet (since all base buildings have been initialized)
                windowT = textureCoordsMap[quarterTextureSet.window];

                // Add small cubes with some rotation to illustrate a spiral building
                tempVertices = Component::cubeStandardVertices(glm::vec3(0.0f, yOffset, 0.0f), 
                    glm::vec3(0.0f, glm::radians(rotateOffset), 0.0f), glm::vec3(spiralSize, 0.2f, spiralSize));
                yOffset += 0.2f;
                rotateOffset += 15.0f;
                spiralSize -= SIZE_RATIO;
            }

            // Apply textures
            // Top and Bottom Faces

            ComponentHelper::applyTextureRegion(tempVertices, roofT, 0, 3);
            ComponentHelper::applyTextureRegion(tempVertices, roofT, 4, 7);

            // Front, Back, Left, and Right Faces
            
            if (i == 0)
            {
                // Front Face
                ComponentHelper::applyTextureRegion(tempVertices, doorT, 8, 11);

                // Back, Left, Right
                ComponentHelper::applyTextureRegion(tempVertices, baseT, 12, 23);   
            }
            else
            {
                ComponentHelper::applyTextureRegion(tempVertices, windowT, 8, 23);
            }


            buildingVertices.insert(buildingVertices.end(), tempVertices.begin(), tempVertices.end());

            // Add indices for this object, offset by the current number of vertices

            unsigned short currentOffset = i * cubeUniqueVertices.size();

            for (auto index : cubeIndices)
            {
                buildingIndices.push_back(index + currentOffset);
            }
        }

        // Create vertex and index buffers
        createBuffers();

    }

    SpiralBuilding::~SpiralBuilding()
    {
        
    }

    void SpiralBuilding::render(const std::string& worldUniform, const std::string& projectionViewUniform,
                                  const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        Building::render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
    }
}