#include "land.h"

namespace sheep
{
    
    wolf::Program* Land::program = nullptr;
    wolf::Texture* Land::textureManager = nullptr;

    Land::Land(wolf::Program* programParam, const std::string& positionUniformParam, const std::string& texture)
        : rotateX(0.0f), rotateY(0.0f), rotateZ(0.0f), scaleVector(glm::vec3(1.0f)), translateVector(glm::vec3(0.0f)),
          positionVBO(nullptr), indexBuffer(nullptr), vao(nullptr)
    {
            program = programParam;
            vao = new wolf::VertexDeclaration();

            textureManager = wolf::TextureManager::CreateTexture(texture);     // TODO: Change this later
            textureManager->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);

            landVertices = cubeUniqueVertices;
            landIndices = cubeIndices;

            // Create buffers
            positionVBO = wolf::BufferManager::CreateVertexBuffer(landVertices.data(), sizeof(VertexPosTex5D)
            * landVertices.size());
            indexBuffer = wolf::BufferManager::CreateIndexBuffer(landIndices.data(), landIndices.size());

            // Use parent VAO and assign VBOs and Texture Unit to it

            vao->Begin();
            vao->SetVertexBuffer(positionVBO);
            vao->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
            vao->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
            vao->End();

    }

    Land::~Land()
    {
            delete vao;
            wolf::BufferManager::DestroyBuffer(positionVBO);
            wolf::BufferManager::DestroyBuffer(indexBuffer);
            wolf::TextureManager::DestroyTexture(textureManager);
    }

    void Land::render(const std::string& worldUniform, const std::string& projectionViewUniform, 
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

        program->SetUniform(textureUniform, 0);

        program->Bind();        // Bind here to fix shifting (wolf issue)

        vao->Bind();
        textureManager->Bind(0);
        indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, landIndices.size(), GL_UNSIGNED_SHORT, 0);
    }

    void Land::printBufferContents() const
    {
        // Print landVertices
        printf("landVertices: ");
        for (const auto& vertex : landVertices) {
            printf("(%f, %f, %f, %f, %f) ", vertex.x, vertex.y, vertex.z, vertex.u, vertex.v);
        }
        printf("\n");

        // Print landIndices
        printf("landIndices: ");
        for (const auto& index : landIndices) {
            printf("%hu ", index);
        }
        printf("\n");
    }

    void Land::printBufferSize() const
    {
        printf("Land Vertices size: %lu\n", landVertices.size());
        printf("Land Vertices total bytes: %lu\n", sizeof(VertexPosTex5D) * landVertices.size());
        printf("Land Indices size: %lu\n", landIndices.size());
    }

    void Land::translate(GLfloat x, GLfloat y, GLfloat z)
    {
        translateVector = glm::vec3(x, y, z);
    };

    void Land::scale(GLfloat x, GLfloat y, GLfloat z)
    {
        scaleVector = glm::vec3(x, y, z);
    };

    void Land::rotate(GLfloat x, GLfloat y, GLfloat z)
    {
        rotateX = x;
        rotateY = y;
        rotateZ = z;
    };

    
}