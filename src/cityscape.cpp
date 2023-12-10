#include "cityscape.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


Cityscape::~Cityscape()
{
    printf("Destructing Cityscape World...\n");

    wolf::ProgramManager::DestroyProgram(mainProgram);

    delete camera;

    for (auto building : standardBuildings)
    {
        delete building;
    }

    printf("Cityscape World destructed successfully.\n");
}

void Cityscape::init()
{
    // Initialize program for the first time
    if (!mainProgram)
    {
        glEnable(GL_DEPTH_TEST);

        mainProgram = wolf::ProgramManager::CreateProgram("data/texture.vsh", "data/texture.fsh");
        this->camera = new sheep::FirstPersonCamera(m_pApp);

        // Render objects

        float xOffset = 0.0f;
        float zOffset = 0.0f;
        int count = 0;
        
        // TODO: Remove later
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                standardBuildings.push_back(new sheep::StandardBuilding(mainProgram, "position"));
                standardBuildings[count]->translate(xOffset, 0.0f, zOffset);

                zOffset += 2.0f;
                count++;
            }
            zOffset = 0.0f;
            xOffset += 2.0f;
        }
    }
}

void Cityscape::update(float dt)
{
    time += dt;
    camera->update(dt);
}

void Cityscape::render(int width, int height)
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projectionMatrix = camera->getProjectionMatrix(width, height);
    glm::mat4 viewMatrix = camera->getViewMatrix();

    glm::mat4 projectionViewMatrix = projectionMatrix * viewMatrix;

    // TODO: Remove later
    for (auto building : standardBuildings)
    {
        building->render("world", "projectionView", "textureUniform", projectionViewMatrix);
    }
}
