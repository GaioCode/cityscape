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
            enum ComponentType
            {
                base = 0,
                middle = 1,
                roof = 2
            };

            static std::vector<VertexPosTex5D> cubeStandardVertices();

            static std::vector<VertexPosTex5D> cubeStandardVertices(glm::vec3 translate,
            glm::vec3 rotate, glm::vec3 scale);

            static std::vector<unsigned short> cubeStandardIndices();

            static std::vector<VertexPosTex5D> polygonVertices(int sides);

            static std::vector<VertexPosTex5D> polygonVertices(int sides, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);

            static std::vector<unsigned short> polygonIndices(int sides);

    };
}