#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "../sheep/sheep.h"
#include "randomNumberGenerator.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

// Objects (unused)
#include "cube.h"
#include "texturedCube.h"

class Cityscape: public Sample
{
    public:
        Cityscape(wolf::App* pApp)
            : Sample(pApp, "Generated Cityscape Object") {}
        ~Cityscape();

        void init() override;
        void update(float dt) override;
        void render(int width, int height) override;

        // Regenerates the world
        void regenerate();

    private:
        wolf::Program* mainProgram = 0;
        sheep::FirstPersonCamera* camera;
        sheep::EntityManager* entityManager;
        GLfloat time = 0;

        

};