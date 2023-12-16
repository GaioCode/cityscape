#pragma once
#include "../../wolf/W_Types.h"
#include "../structures/basicStructures.h"
#include "../structures/polygonStructures.h"
#include "componentHelper.h"

namespace sheep
{
    class Component
    {
        public:

            static std::vector<VertexPosTex5D> landVertices();

            static std::vector<unsigned short> landIndices();

            static std::vector<VertexPosTex5D> cubeStandardVertices();

            static std::vector<VertexPosTex5D> cubeStandardVertices(glm::vec3 translate,
            glm::vec3 rotate, glm::vec3 scale);

            static std::vector<unsigned short> cubeStandardIndices();

            static std::vector<VertexPosTex5D> polygonVertices(int sides);

            static std::vector<VertexPosTex5D> polygonVertices(int sides, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);

            static std::vector<unsigned short> polygonIndices(int sides);

    };
}