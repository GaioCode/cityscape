#include "standardBuilding.h"

namespace sheep
{
    StandardBuilding::StandardBuilding(wolf::Program* programParam, const std::string& positionUniformParam)
        : Building(programParam, positionUniformParam), standardCube1(nullptr)
    {
        // For every component generated, raise this value by the component's height
        // float yOffset = 0.0f;
        
        // const float COMPONENT_WIDTH = 1.0f;
        // const float COMPONENT_HEIGHT = 1.0f;

        // for (int i = 0; i < 3; ++i)
        // {

        //     standardCubeVector[i].translate(0.0f, yOffset, 0.0f);

        //     yOffset += 1.0f;
        // }

        standardCube1 = new StandardCube(programParam, positionUniformParam);

    }

    StandardBuilding::~StandardBuilding()
    {
        delete standardCube1;
    }

    void StandardBuilding::render(const std::string& worldUniform, const std::string& projectionViewUniform,
    const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        standardCube1->scale(scaleVector.x, scaleVector.y, scaleVector.z);
        standardCube1->translate(translateVector.x, translateVector.y, translateVector.z);
        standardCube1->rotate(rotateX, rotateY, rotateZ);

        standardCube1->render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
    }
}