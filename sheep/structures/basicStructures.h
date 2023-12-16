#pragma once
#include "../../wolf/wolf.h"

namespace sheep
{
    struct VertexPos2D
    {
        GLfloat x, y;
    };

    struct VertexPos3D
    {
        GLfloat x, y, z;
    };

    struct VertexPosTex5D
    {
        GLfloat x, y, z;
        GLfloat u, v;
    };

    struct TextureRegion
    {
        float uMin, vMin, uMax, vMax;
    };
}

