#pragma once
#include "../building.h"
#include "../componentTypes/standardCube.h"

namespace sheep
{
    class StandardBuilding : public Building
    {
        public:

            StandardBuilding(wolf::Program* programParam, const std::string& positionUniformParam);

            ~StandardBuilding() override;

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
            const std::string& textureUniform, const glm::mat4& projectionViewMatrix) override;

        private:
            std::vector<StandardCube*> standardCubes;
    };
}