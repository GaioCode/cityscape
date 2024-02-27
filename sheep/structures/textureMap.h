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
        Brick1Roof, Brick2Roof, Brick3Roof,

        Glass1WindowHalf, Glass2WindowHalf, Glass3WindowHalf,
        Brick1WindowHalf, Brick2WindowHalf, Brick3WindowHalf,

        Glass1WindowQuarter, Glass2WindowQuarter, Glass3WindowQuarter,
        Brick1WindowQuarter, Brick2WindowQuarter, Brick3WindowQuarter,

        Land1, LandBlank,
    };

    struct TextureSet
    {
        TextureType base;       // First floor's sides
        TextureType door;       // First floor's door
        TextureType window;     // Windows or walls for the entire building
        TextureType roof;       // Top and bottom face
        
    };
    
    struct LandTextureSet
    {
        TextureType land;       // The top surface of the land, showing the actual texture
        TextureType blank;      // Placeholder texture for blank surfaces
    };

    extern std::map<TextureType, TextureRegion> textureCoordsMap;
    extern std::vector<TextureSet> textureSets;
    extern std::vector<TextureSet> halfTextureSets;
    extern std::vector<TextureSet> quarterTextureSets;
    extern std::vector<LandTextureSet> landTextureSets;
}

