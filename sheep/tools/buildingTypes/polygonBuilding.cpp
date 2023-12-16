#include "polygonBuilding.h"

namespace sheep
{
    
    PolygonBuilding::PolygonBuilding(wolf::Program* programParam, const std::string& positionUniformParam,
                                     const std::string& texture, int height, int sides,
                                     TextureType base, TextureType door, TextureType window, TextureType roof)
        : Building(programParam, positionUniformParam, texture, base, door, window, roof)
    {  

        float yOffset = 0.0f;
        unsigned short currentOffset = 0;

        for (int i = 0; i < height; i++)
        {
            currentOffset = buildingVertices.size();

            // Add vertices for this object, with yOffset applied to the y component

            std::vector<VertexPosTex5D> tempVertices = 
                Component::polygonVertices(sides, glm::vec3(0.0f, yOffset, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

            // Apply textures
            // Top and Bottom Faces

            // Center top vertice + center bottom vertice + top and bottom outer vertices - 1 (zero index inclusive)
            int numTBVertices = 2 + (sides * 2);

            ComponentHelper::applyTextureRegion(tempVertices, roofT, 0, numTBVertices - 1);

            // Front, Back, Left, and Right Faces
            

            if (i == 0)
            {
                // Front Face
                ComponentHelper::applyTextureRegion(tempVertices, doorT, numTBVertices, numTBVertices + 3);

                // Back, Left, Right
                ComponentHelper::applyTextureRegion(tempVertices, baseT, numTBVertices + 4, numTBVertices + 3 + 4 * (sides - 1));   
            }
            else
            {
                ComponentHelper::applyTextureRegion(tempVertices, windowT, numTBVertices, numTBVertices - 1 + 4 * (sides));
            }

            buildingVertices.insert(buildingVertices.end(), tempVertices.begin(), tempVertices.end());

            // Add indices for this object, offset by the current number of vertices

            std::vector<unsigned short> tempIndices = Component::polygonIndices(sides);

            for (auto index : tempIndices)
            {
                buildingIndices.push_back(index + currentOffset);
            }

            // For every component generated, raise this value by the component's height
            yOffset += 1.0f;
        }

        // Create vertex and index buffers
        createBuffers();
    }

    PolygonBuilding::~PolygonBuilding()
    {

    }

    void PolygonBuilding::render(const std::string& worldUniform, const std::string& projectionViewUniform,
                                  const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        Building::render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
    }
}