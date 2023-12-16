#include "componentHelper.h"

namespace sheep
{
    const float EPSILON = 1e-6f;        // A very small number used for comparisons

    // std::vector<VertexPositionTexture5D> ComponentHelper::generatePolygonSidesOnly(int numSides)
    // {
    //     std::vector<VertexPositionTexture5D> vertices;

    //     if (numSides < 3) {
    //         throw std::invalid_argument("Polygon must have 3 or more sides.");
    //     }

    //     float diameter = 1.0f;
    //     float height = 1.0f;

    //     float angleIncrement = 2.0f * PI / numSides; // Angle between each vertex on the side
    //     float radius = diameter / 2.0f; // Radius of the circumscribed circle
    //     float halfHeight = height / 2.0f; // Center the height around the origin

    //     // Iterate for each side to calculate vertices
    //     for (int i = 0; i < numSides; ++i) {
    //         float angle1 = i * angleIncrement;
    //         float angle2 = (i + 1) * angleIncrement;

    //         // Calculate the vertex positions based on the circumscribed circle's radius
    //         // Bottom vertices
    //         VertexPositionTexture5D v1{radius * std::cos(angle1), -halfHeight, radius * std::sin(angle1), 0.0f, 0.0f};
    //         VertexPositionTexture5D v2{radius * std::cos(angle2), -halfHeight, radius * std::sin(angle2), 1.0f, 0.0f};

    //         // Top vertices
    //         VertexPositionTexture5D v3{radius * std::cos(angle1), halfHeight, radius * std::sin(angle1), 0.0f, 1.0f};
    //         VertexPositionTexture5D v4{radius * std::cos(angle2), halfHeight, radius * std::sin(angle2), 1.0f, 1.0f};

    //         // Triangle 1
    //         vertices.push_back(v1);
    //         vertices.push_back(v3);
    //         vertices.push_back(v2);

    //         // Triangle 2
    //         vertices.push_back(v2);
    //         vertices.push_back(v3);
    //         vertices.push_back(v4);
    //     }

    //     return vertices;
    // }

    // std::vector<VertexPosTex5D> ComponentHelper::generatePolygon(int numSides)
    // {
    //     std::vector<VertexPosTex5D> vertices;

    //     if (numSides < 3) {
    //         throw std::invalid_argument("Polygon must have 3 or more sides.");
    //     }

    //     float diameter = 1.0f;
    //     float height = 1.0f;

    //     float angleIncrement = 2.0f * PI / numSides; // Angle between each vertex on the side
    //     float radius = diameter / 2.0f; // Radius of the circumscribed circle
    //     float halfHeight = height / 2.0f; // Center the height around the origin

    //     // Vertex for the center of the top and bottom faces
    //     VertexPosTex5D topCenter{0.0f, halfHeight, 0.0f, 0.5f, 0.5f};
    //     VertexPosTex5D bottomCenter{0.0f, -halfHeight, 0.0f, 0.5f, 0.5f};

    //     // Iterate for each side to calculate vertices
    //     for (int i = 0; i < numSides; ++i) {
    //         float angle1 = i * angleIncrement;
    //         float angle2 = (i + 1) * angleIncrement;

    //         // Calculate the vertex positions based on the circumscribed circle's radius
    //         // Bottom vertices
    //         VertexPosTex5D v1{radius * std::cos(angle1), -halfHeight, radius * std::sin(angle1), 
    //                           (std::cos(angle1) + 1.0f) / 2.0f, (std::sin(angle1) + 1.0f) / 2.0f};
    //         VertexPosTex5D v2{radius * std::cos(angle2), -halfHeight, radius * std::sin(angle2), 
    //                           (std::cos(angle2) + 1.0f) / 2.0f, (std::sin(angle2) + 1.0f) / 2.0f};

    //         // Top vertices
    //         VertexPosTex5D v3{radius * std::cos(angle1), halfHeight, radius * std::sin(angle1), 
    //                           (std::cos(angle1) + 1.0f) / 2.0f, (std::sin(angle1) + 1.0f) / 2.0f};
    //         VertexPosTex5D v4{radius * std::cos(angle2), halfHeight, radius * std::sin(angle2), 
    //                           (std::cos(angle2) + 1.0f) / 2.0f, (std::sin(angle2) + 1.0f) / 2.0f};

    //         // Side Triangles
    //         vertices.push_back(v1);
    //         vertices.push_back(v3);
    //         vertices.push_back(v2);

    //         vertices.push_back(v2);
    //         vertices.push_back(v3);
    //         vertices.push_back(v4);

    //         // Bottom face triangles
    //         vertices.push_back(bottomCenter);
    //         vertices.push_back(v1);
    //         vertices.push_back(v2);

    //         // Top face triangles
    //         vertices.push_back(topCenter);
    //         vertices.push_back(v3);
    //         vertices.push_back(v4);
    //     }

    //     return vertices;
    // }

    std::vector<VertexPosTex5D> ComponentHelper::generatePolygonUniqueVertices(int numSides)
    {

        std::vector<VertexPosTex5D> vertices;

        if (numSides < 3)
        {
            throw std::invalid_argument("Polygon must have at least 3 sides.");
        }

        float diameter = 1.0f;
        float halfHeight = 0.5f;
        float angleIncrement = 2.0f * PI / numSides;
        float radius = diameter / 2.0f;

        // Center points for top and bottom
        VertexPosTex5D topCenter{0.0f, halfHeight, 0.0f, 0.5f, 0.5f};
        VertexPosTex5D bottomCenter{0.0f, -halfHeight, 0.0f, 0.5f, 0.5f};
        vertices.push_back(topCenter);
        vertices.push_back(bottomCenter);

        std::vector<VertexPosTex5D> tempSideVertices;

        // Calculate the unique vertices around the rim
        for (int i = 0; i < numSides; ++i)
        {
            float angle = i * angleIncrement;
            float x = radius * std::cos(angle);
            float z = radius * std::sin(angle);

            VertexPosTex5D topVertex{x, halfHeight, z, (std::cos(angle) + 1.0f) / 2.0f, 
                                     (std::sin(angle) + 1.0f) / 2.0f};
            VertexPosTex5D bottomVertex{x, -halfHeight, z, (std::cos(angle) + 1.0f) / 2.0f,
                                        (std::sin(angle) + 1.0f) / 2.0f};
            vertices.push_back(topVertex);
            vertices.push_back(bottomVertex);
        }

        for (int i = 0; i < numSides; i++)
        {
            VertexPosTex5D tempVertices;
            tempVertices = vertices[i * 2 + 2];
            tempVertices.u = 0.0f;
            tempVertices.v = 0.0f;

            vertices.push_back(tempVertices);

            tempVertices = vertices[i * 2 + 3];
            tempVertices.u = 0.0f;
            tempVertices.v = 1.0f;

            vertices.push_back(tempVertices);

            tempVertices = i != numSides - 1 ? vertices[i * 2 + 4] : tempVertices = vertices[2];
            tempVertices.u = 1.0f;
            tempVertices.v = 0.0f;

            vertices.push_back(tempVertices);

            tempVertices = i != numSides - 1 ? vertices[i * 2 + 5] : tempVertices = vertices[3];
            tempVertices.u = 1.0f;
            tempVertices.v = 1.0f;

            vertices.push_back(tempVertices);
        }

        return vertices;
    }

    std::vector<unsigned short> ComponentHelper::generatePolygonIndices(int numSides)
    {

        std::vector<unsigned short> indices;

        // Indices for the top and bottom faces
        for (int i = 0; i < numSides; ++i) {
            // Top face
            indices.push_back(0); // Top center
            indices.push_back(2 + i * 2); // Top vertex of current side
            indices.push_back(2 + ((i + 1) % numSides) * 2); // Top vertex of next side

            // Bottom face
            indices.push_back(1); // Bottom center
            indices.push_back(3 + ((i + 1) % numSides) * 2); // Bottom vertex of next side
            indices.push_back(3 + i * 2); // Bottom vertex of current side
        }

        // Start index for side vertices
        int count = 2 + (numSides * 2);

        for (int i = 0; i < numSides; i++)
        {
            // Triangle 1
            for (int j = 0; j < 3; j++)
            {
                indices.push_back(count + j);
            }

            // Triangle 2
            for (int j = 1; j < 4; j++)
            {
                indices.push_back(count + j);
            }

            count += 4;
        }

        return indices;
    }


    std::vector<VertexPosTex5D> ComponentHelper::transform(std::vector<VertexPosTex5D> vertices,
                                                           glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale)
    {
        glm::mat4 transformMatrix = 
            glm::translate(glm::mat4(1.0f), translate) *
            glm::rotate(glm::mat4(1.0f), rotate.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::rotate(glm::mat4(1.0f), rotate.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), rotate.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), scale);

        for (auto& vertex : vertices)
        {
            glm::vec4 rotatedVertex = transformMatrix * glm::vec4(vertex.x, vertex.y, vertex.z, 1.0f);
            vertex.x = rotatedVertex.x;
            vertex.y = rotatedVertex.y;
            vertex.z = rotatedVertex.z;
        }

        return vertices;
    }

    void ComponentHelper::applyTextureRegion(std::vector<VertexPosTex5D>& vertices, TextureRegion& region,
                                   int startOffset, int endOffset)
    {
        if (startOffset > endOffset || endOffset > vertices.size()) {
        throw std::invalid_argument("Invalid range for applying texture region");
        }
        
        for (int i = startOffset; i <= endOffset; ++i) {
            vertices[i].u = region.uMin + vertices[i].u * (region.uMax - region.uMin);
            vertices[i].v = region.vMin + vertices[i].v * (region.vMax - region.vMin);
        }
    }

    float ComponentHelper::roundedSin(float angle) {
        float result = std::sin(angle);
        if (std::abs(result) < EPSILON)
            result = 0.0f;
        return result;
    }

    float ComponentHelper::roundedCos(float angle) {
        float result = std::cos(angle);
        if (std::abs(result) < EPSILON)
            result = 0.0f;
        return result;
    }

    void ComponentHelper::printVerticesInfo(std::vector<VertexPosTex5D> vertices, const std::string& vectorName)
    {
        // Print buildingVertices
        printf("Component Vertices for: ");
        std::cout << vectorName << std::endl;
        for (const auto& vertex : vertices) {
            printf("(%f, %f, %f, %f, %f) ", vertex.x, vertex.y, vertex.z, vertex.u, vertex.v);
        }
        printf("\n");
    }

    void ComponentHelper::printIndicesInfo(std::vector<unsigned short> indices, const std::string& vectorName)
    {
        printf("Component Indices for: ");
        std::cout << vectorName << std::endl;
        for (const auto& index : indices) {
            printf("%hu ", index);
        }
        printf("\n");
    }

}