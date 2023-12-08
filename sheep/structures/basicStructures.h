#pragma once
#include "../../wolf/wolf.h"

namespace sheep
{
    struct VertexPosition2D
    {
        GLfloat x, y;
    };

    struct VertexPosition3D
    {
        GLfloat x, y, z;
    };

    struct VertexPositionTexture5D
    {
        GLfloat x, y, z;
        GLfloat u, v;
    };
}

