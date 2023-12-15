#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "../sheep/sheep.h"
#include "cube.h"
#include "texturedCube.h"
#include "randomNumberGenerator.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

// Objects
#include "cube.h"


class Cityscape: public Sample
{
    public:
        Cityscape(wolf::App* pApp) : Sample(pApp, "Generated Cityscape Object") {}
        ~Cityscape();

        void init() override;
        void update(float dt) override;
        void render(int width, int height) override;

        // Regenerates the world
        void regenerate();

    private:
        wolf::Program* mainProgram = 0;
        sheep::FirstPersonCamera* camera;
        GLfloat time = 0;

        GLboolean isRegen = GL_FALSE;

        // TODO: Remove later
        std::vector<sheep::StandardBuilding*> standardBuildings;
        std::vector<sheep::PolygonBuilding*> polygonBuildings;
        TexturedCube* texturedCube1;

};