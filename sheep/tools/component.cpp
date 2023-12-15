#include "component.h"

namespace sheep
{
    std::vector<VertexPosTex5D> Component::cubeStandardVertices()
    {
        return cubeUniqueVertices;
    }

    std::vector<VertexPosTex5D> Component::cubeStandardVertices(glm::vec3 translate,
        glm::vec3 rotate, glm::vec3 scale)
    {
        return ComponentHelper::transform(cubeUniqueVertices, translate, rotate, scale);
    }

    std::vector<unsigned short> Component::cubeStandardIndices()
    {
        return cubeIndices;
    }

    std::vector<VertexPosTex5D> Component::polygonVertices(int sides)
    {
        return ComponentHelper::generatePolygonUniqueVertices(sides);
    }

    std::vector<VertexPosTex5D> Component::polygonVertices(int sides, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale)
    {
        return ComponentHelper::transform(ComponentHelper::generatePolygonUniqueVertices(sides), translate, rotate, scale);
    }

    std::vector<unsigned short> Component::polygonIndices(int sides)
    {
        return ComponentHelper::generatePolygonIndices(sides);
    }

}