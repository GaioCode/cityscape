#pragma once
#include "basicStructures.h"
#include <map>

namespace sheep
{
    enum class TextureType
    {
        Glass1Window, Glass2Window, Glass3Window,
        Glass1Door, Glass2Door, Glass2Base, Glass3Door, Glass3Base,
        Brick1Window, Brick2Window, Brick3Window,
        Brick1Door, Brick2Door, Brick3Door,
        GlassRoof,
        Brick1Roof, Brick2Roof, Brick3Roof
    };

    struct TextureSet
    {
        TextureType base;       // First floor's sides
        TextureType door;       // First floor's door
        TextureType window;     // Windows or walls for the entire building
        TextureType roof;       // Top and bottom face
        
    };

    extern std::map<TextureType, TextureRegion> textureCoordsMap;
    extern std::vector<TextureSet> textureSets;
}

