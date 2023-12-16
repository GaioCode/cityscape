#include "textureMap.h"

namespace sheep
{
    std::map<TextureType, TextureRegion> textureCoordsMap =
    {
        {TextureType::Glass1Window, {0.0f, 0.0f, 0.125f, 0.125f}},
        {TextureType::Glass2Window, {0.125f, 0.0f, 0.250f, 0.125f}},
        {TextureType::Glass3Window, {0.250f, 0.0f, 0.375f, 0.125f}},
        {TextureType::Glass1Door, {0.375f, 0.0f, 0.500f, 0.125f}},
        {TextureType::Glass2Door, {0.500f, 0.0f, 0.625f, 0.125f}},
        {TextureType::Glass2Base, {0.625f, 0.0f, 0.750f, 0.125f}},
        {TextureType::Glass3Door, {0.750f, 0.0f, 0.875f, 0.125f}},
        {TextureType::Glass3Base, {0.875f, 0.0f, 1.0f, 0.125f}},
        {TextureType::Brick1Window, {0.0f, 0.125f, 0.125f, 0.250f}},
        {TextureType::Brick2Window, {0.125f, 0.125f, 0.250f, 0.250f}},
        {TextureType::Brick3Window, {0.250f, 0.125f, 0.375f, 0.250f}},
        {TextureType::Brick1Door, {0.375f, 0.125f, 0.500f, 0.250f}},
        {TextureType::Brick2Door, {0.500f, 0.125f, 0.625f, 0.250f}},
        {TextureType::Brick3Door, {0.625f, 0.125f, 0.750f, 0.250f}},
        {TextureType::GlassRoof, {0.750f, 0.125f, 0.875f, 0.250f}},
        {TextureType::Brick1Roof, {0.875f, 0.125f, 1.0f, 0.250f}},
        {TextureType::Brick2Roof, {0.0f, 0.250f, 0.125f, 0.375f}},
        {TextureType::Brick3Roof, {0.125f, 0.250f, 0.250f, 0.375f}}
    };

    // Base, Door, Window, Roof
    std::vector<TextureSet> textureSets =
    {
        {TextureType::Glass1Window, TextureType::Glass1Door, TextureType::Glass1Window, TextureType::GlassRoof},
        {TextureType::Glass2Base, TextureType::Glass2Door, TextureType::Glass2Window, TextureType::GlassRoof},
        {TextureType::Glass3Base, TextureType::Glass3Door, TextureType::Glass3Window, TextureType::GlassRoof},
        {TextureType::Brick1Window, TextureType::Brick1Door, TextureType::Brick1Window, TextureType::Brick1Roof},
        {TextureType::Brick2Window, TextureType::Brick2Door, TextureType::Brick2Window, TextureType::Brick2Roof},
        {TextureType::Brick3Window, TextureType::Brick3Door, TextureType::Brick3Window, TextureType::Brick3Roof},
    };
}