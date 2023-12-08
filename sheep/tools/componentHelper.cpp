#include "componentHelper.h"

namespace sheep
{
    const float EPSILON = 1e-6f;        // A very small number used for comparisons

    std::vector<VertexPositionTexture5D> ComponentHelper::generatePolygonSides(int numSides)
    {
        std::vector<VertexPositionTexture5D> vertices;

        if (numSides < 3) {
            throw std::invalid_argument("Polygon must have 3 or more sides.");
        }

        float diameter = 1.0f;
        float height = 1.0f;

        float angleIncrement = 2.0f * PI / numSides; // Angle between each vertex on the side
        float radius = diameter / 2.0f; // Radius of the circumscribed circle
        float halfHeight = height / 2.0f; // Center the height around the origin

        // Iterate for each side to calculate vertices
        for (int i = 0; i < numSides; ++i) {
            float angle1 = i * angleIncrement;
            float angle2 = (i + 1) * angleIncrement;

            // Calculate the vertex positions based on the circumscribed circle's radius
            // Bottom vertices
            VertexPositionTexture5D v1{radius * std::cos(angle1), -halfHeight, radius * std::sin(angle1), 0.0f, 0.0f};
            VertexPositionTexture5D v2{radius * std::cos(angle2), -halfHeight, radius * std::sin(angle2), 1.0f, 0.0f};

            // Top vertices
            VertexPositionTexture5D v3{radius * std::cos(angle1), halfHeight, radius * std::sin(angle1), 0.0f, 1.0f};
            VertexPositionTexture5D v4{radius * std::cos(angle2), halfHeight, radius * std::sin(angle2), 1.0f, 1.0f};

            // Triangle 1
            vertices.push_back(v1);
            vertices.push_back(v3);
            vertices.push_back(v2);

            // Triangle 2
            vertices.push_back(v2);
            vertices.push_back(v3);
            vertices.push_back(v4);
        }

        return vertices;
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

}