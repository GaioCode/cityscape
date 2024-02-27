// #pragma once
// #include "polygonStructures.h"
// #include <vector>
// #include <string>

// namespace sheep
// {
//     class Skybox
//     {
//         public:
//             Skybox(wolf::Program* programParam, const std::string& positionUniformParam,
//                    const std::vector<std::string>& texturePaths);

//             ~Skybox();

//             void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
//                         const std::string& textureUniform, const glm::mat4& projectionViewMatrix);

//         private:
//             void loadTextures(const std::vector<std::string>& texturePaths);

//             static wolf::Program* program;
//             static wolf::Texture* textureManager;
//             static wolf::VertexDeclaration* vao;
//             static wolf::VertexBuffer* positionVBO;
//             static wolf::IndexBuffer* indexBuffer;

//             GLboolean isGenerated;
//     }
// }