#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "../sheep/sheep.h"
#include "cube.h"
#include "texturedCube.h"
#include "buildings/normalBuilding.h"

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

    private:
        wolf::Program* mainProgram = 0;
        sheep::FirstPersonCamera* camera;
        GLfloat time = 0;

        // TODO: Remove later
        TexturedCube* texturedCube1;
        // NormalBuilding* normalBuilding1;
        sheep::StandardBuilding* standardBuilding1;
        
};