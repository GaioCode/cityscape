#include "building.h"

namespace sheep
{
    
    wolf::Program* Building::program = nullptr;
    wolf::Texture* Building::textureManager = nullptr;

    Building::Building(wolf::Program* programParam, const std::string& positionUniformParam)
        : rotateX(0.0f), rotateY(0.0f), rotateZ(0.0f), scaleVector(glm::vec3(1.0f)), translateVector(glm::vec3(0.0f)),
          positionVBO(nullptr), indexBuffer(nullptr), vao(nullptr)
    {

            program = programParam;
            vao = new wolf::VertexDeclaration();

            textureManager = wolf::TextureManager::CreateTexture("data/textures/testing1.png");
            textureManager->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
    }

    // Pure virtual destructor
    Building::~Building()
    {
            delete vao;
            wolf::BufferManager::DestroyBuffer(positionVBO);
            wolf::BufferManager::DestroyBuffer(indexBuffer);
            wolf::TextureManager::DestroyTexture(textureManager);
    }

    void Building::render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                          const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        // Convert object space to world space

        glm::mat4 worldMatrix = 
            glm::translate(glm::mat4(1.0f), translateVector) *
            glm::rotate(glm::mat4(1.0f), rotateZ, glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::rotate(glm::mat4(1.0f), rotateY, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), rotateX, glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), scaleVector);

        // Set uniforms
        
        program->SetUniform(projectionViewUniform, projectionViewMatrix);
        program->SetUniform(worldUniform, worldMatrix);

        // Set texture uniform

        program->SetUniform("tex", 0);

        program->Bind();        // Bind here to fix shifting (wolf issue)

        vao->Bind();
        textureManager->Bind(0);
        indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, buildingIndices.size(), GL_UNSIGNED_SHORT, 0);
    }

    // void Building::updateBuffers()
    // {
    //      // Update VBO and Index Buffers

    //     wolf::BufferManager::UpdateVertexBuffer(positionVBO, buildingVertices.data(), sizeof(VertexPositionTexture5D) 
    //         * buildingVertices.size());

    //     wolf::BufferManager::UpdateIndexBuffer(indexBuffer, buildingIndices.data(), buildingIndices.size());
    // }

    void Building::createBuffers()
    {
        // Add data to positionVBO

        positionVBO = wolf::BufferManager::CreateVertexBuffer(buildingVertices.data(), sizeof(VertexPosTex5D)
            * buildingVertices.size());

        // Create Index Buffer Object (IBO)
        indexBuffer = wolf::BufferManager::CreateIndexBuffer(buildingIndices.data(), buildingIndices.size());

        // Use parent VAO and assign VBOs and Texture Unit to it

        vao->Begin();
        vao->SetVertexBuffer(positionVBO);
        vao->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        vao->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        vao->End();
    }

    void Building::printBufferContents() const
    {
        // Print buildingVertices
        printf("buildingVertices: ");
        for (const auto& vertex : buildingVertices) {
            printf("(%f, %f, %f, %f, %f) ", vertex.x, vertex.y, vertex.z, vertex.u, vertex.v);
        }
        printf("\n");

        // Print buildingIndices
        printf("buildingIndices: ");
        for (const auto& index : buildingIndices) {
            printf("%hu ", index);
        }
        printf("\n");
    }

    void Building::printBufferSize() const
    {
        printf("Building Vertices size: %lu\n", buildingVertices.size());
        printf("Building Vertices total bytes: %lu\n", sizeof(VertexPosTex5D) * buildingVertices.size());
        printf("Building Indices size: %lu\n", buildingIndices.size());
    }

    void Building::translate(GLfloat x, GLfloat y, GLfloat z)
    {
        translateVector = glm::vec3(x, y, z);
    };

    void Building::scale(GLfloat x, GLfloat y, GLfloat z)
    {
        scaleVector = glm::vec3(x, y, z);
    };

    void Building::rotate(GLfloat x, GLfloat y, GLfloat z)
    {
        rotateX = x;
        rotateY = y;
        rotateZ = z;
    };

    
}