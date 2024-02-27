#pragma once
#include "../building.h"

namespace sheep
{
    class StandardBuilding : public Building
    {
        public:

            StandardBuilding(wolf::Program* programParam, const std::string& positionUniformParam,
                             const std::string& texture, int height,
                             const TextureSet& textureSet);

            ~StandardBuilding() override;

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                        const std::string& textureUniform, const glm::mat4& projectionViewMatrix);
    };
}