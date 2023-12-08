#include "standardBuilding.h"

namespace sheep
{
    const int NUM_STANDARD_CUBES = 3;
    std::vector<float> initialYOffsets;

    StandardBuilding::StandardBuilding(wolf::Program* programParam, const std::string& positionUniformParam)
        : Building(programParam, positionUniformParam)
    {

        float yOffset = 0.0f;

        for (int i = 0; i < NUM_STANDARD_CUBES; i++)
        {

            standardCubes.push_back(new StandardCube(programParam, positionUniformParam));

            initialYOffsets.push_back(yOffset);

            // For every component generated, raise this value by the component's height
            yOffset += 1.0f;

            printf("%f\n", yOffset);
        }

    }

    StandardBuilding::~StandardBuilding()
    {
        for (auto* cube : standardCubes)
        {
            delete cube;
        }
    }

    void StandardBuilding::render(const std::string& worldUniform, const std::string& projectionViewUniform,
    const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        for (size_t i = 0; i < standardCubes.size(); i++)
        {
            auto* cube = standardCubes[i];
            cube->scale(scaleVector.x, scaleVector.y, scaleVector.z);
            cube->rotate(rotateX, rotateY, rotateZ);
            cube->translate(translateVector.x, translateVector.y + initialYOffsets[i], translateVector.z);
            
            // TODO: We want to add translate values, so we need the cube's ori values and add new one
            cube->render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
        }
    }
}