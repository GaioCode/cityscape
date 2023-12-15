#pragma once
#include "../building.h"

namespace sheep
{
    class PolygonBuilding : public Building
    {
        public:

            PolygonBuilding(wolf::Program* programParam, const std::string& positionUniformParam, int height, int sides);

            ~PolygonBuilding() override;

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                        const std::string& textureUniform, const glm::mat4& projectionViewMatrix);

        private:
    };
}