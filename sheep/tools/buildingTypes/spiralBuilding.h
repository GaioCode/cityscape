#pragma once
#include "../building.h"

namespace sheep
{
    class SpiralBuilding : public Building
    {
        public:

            SpiralBuilding(wolf::Program* programParam, const std::string& positionUniformParam,
                             const std::string& texture, int baseHeight, int spiralHeight,
                             const TextureSet& textureSet, const TextureSet& quarterTextureSet);

            ~SpiralBuilding() override;

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                        const std::string& textureUniform, const glm::mat4& projectionViewMatrix);
    };
}