#include "standardBuilding.h"

namespace sheep
{
    
    StandardBuilding::StandardBuilding(wolf::Program* programParam, const std::string& positionUniformParam,
                                       const std::string& texture, int height,
                                       TextureType base, TextureType door, TextureType window, TextureType roof)
        : Building(programParam, positionUniformParam, texture, base, door, window, roof)
    {  

        float yOffset = 0.0f;

        // Retrieve texture regions

        
        
        for (int i = 0; i < height; i++)
        {
            // Add vertices for this object, with yOffset applied to the y component

            std::vector<VertexPosTex5D> tempVertices = 
                Component::cubeStandardVertices(glm::vec3(0.0f, yOffset, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

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