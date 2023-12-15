#pragma once
#include "../../wolf/W_Types.h"
#include "../structures/basicStructures.h"
#include "../structures/polygonStructures.h"
#include <vector>
#include <stdexcept>
#include <iostream>

namespace sheep
{
    class ComponentHelper
    {
        public:
            // Generate any legal polygon sides, excluding the top and bottom faces. The polygon is generated using
            // PI and trigonometric values, so it has angle differences when being generated.
            static std::vector<VertexPosTex5D> generatePolygonSidesOnly(int numSides);

            static std::vector<VertexPosTex5D> generatePolygon(int numSides);

            static std::vector<VertexPosTex5D> generatePolygonUniqueVertices(int numSides);

            static std::vector<unsigned short> generatePolygonIndices(int numSides);

            static std::vector<VertexPosTex5D> transform(std::vector<VertexPosTex5D> vertices,
                                                         glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);

            // Very small sine numbers are rounded to 0
            static float roundedSin(float angle);

            // Very small cosine numbers are rounded to 0
            static float roundedCos(float angle);

            // Debug tool to print a vector of vertices
            static void printVerticesInfo(std::vector<VertexPosTex5D> vertices,  const std::string& name);

            static void printIndicesInfo(std::vector<unsigned short> indices, const std::string& vectorName);

    };
}

