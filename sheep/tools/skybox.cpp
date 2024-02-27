// #include "skybox.h"

// namespace sheep {
//     wolf::Program* Skybox::program = nullptr;
//     wolf::Texture* Skybox::textureManager = nullptr;
//     wolf::VertexDeclaration* Skybox::vao nullptr;
//     wolf::VertexBuffer* Skybox::positionVBO = nullptr;
//     wolf::IndexBuffer* Skybox::indexBuffer = nullptr;

//     Skybox::Skybox(wolf::Program* programParam, const std::string& positionUniformParam, 
//                    const std::vector<std::string>& texturePaths)
//     {
//         program = programParam;
//         vao = new wolf::VertexDeclaration();

//         // Create buffers
//         positionVBO = wolf::BufferManager::CreateVertexBuffer(skyboxVertices.data(), sizeof(VertexPos3D)
//         * skyboxVertices.size());
//         indexBuffer = wolf::BufferManager::CreateIndexBuffer(skyboxIndices.data(), skyboxIndices.size());

//         // Use parent VAO and assign VBOs and Texture Unit to it

//         vao->Begin();
//         vao->SetVertexBuffer(positionVBO);
//         vao->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
//         vao->End();

//         // TODO: Figure this part out

//         loadTextures(texturePaths);

//     }

//     Skybox::~Skybox() {
//         delete vao;
//         wolf::BufferManager::DestroyBuffer(positionVBO);
//         wolf::BufferManager::DestroyBuffer(indexBuffer);
//         wolf::TextureManager::DestroyTexture(textureManager);
//     }

//     void Skybox::render() {
//         // Bind the skybox texture
//         // Bind the VAO
//         // Configure any necessary render states (like disabling depth writing)
//         // Draw the cube
//         // Restore any render states if needed
//     }

//     void Skybox::loadTextures(const std::vector<std::string>& texturePaths) {
//         // Load the 6 textures for the skybox and create a texture cube map
//     }

// }
