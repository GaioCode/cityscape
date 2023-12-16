#pragma once
#include "../building.h"

namespace sheep
{
    class PolygonBuilding : public Building
    {
        public:

            PolygonBuilding(wolf::Program* programParam, const std::string& positionUniformParam,
                            const std::string& texture, int height, int sides,
                            TextureType base, TextureType door, TextureType window, TextureType roof);

            ~PolygonBuilding() override;

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                        const std::string& textureUniform, const glm::mat4& projectionViewMatrix);
    };
}