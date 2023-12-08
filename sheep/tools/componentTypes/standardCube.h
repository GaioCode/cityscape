#pragma once
#include "../component.h"

namespace sheep
{
    class StandardCube : public Component
    {
        public:
            StandardCube(wolf::Program* programParam, const std::string& positionUniformParam);

            ~StandardCube() override;

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
            const std::string& textureUniform, const glm::mat4& projectionViewMatrix);

        private:
            wolf::VertexBuffer* positionVBO;
            wolf::Texture* textureManager;
    };
}