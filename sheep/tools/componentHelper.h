#pragma once
#include "../../wolf/wolf.h"
#include "../structures/basicStructures.h"
#include "../structures/polygonStructures.h"
#include <vector>
#include <stdexcept>

namespace sheep
{
    class ComponentHelper
    {
        public:
            // Generate any legal polygon sides, excluding the top and bottom faces. The polygon is generated using
            // PI and trigonometric values, so it has angle differences when being generated.
            static std::vector<VertexPositionTexture5D> generatePolygonSides(int numSides);

            // Very small sine numbers are rounded to 0
            static float roundedSin(float angle);

            // Very small cosine numbers are rounded to 0
            static float roundedCos(float angle);
    };
}

