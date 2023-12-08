#include "cityscape.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Cityscape::~Cityscape()
{
    printf("Destructing Cityscape World...\n");
    wolf::ProgramManager::DestroyProgram(mainProgram);
    printf("Cityscape World destructed successfully.\n");

    // TODO: Remove later
    delete standardBuilding1;
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
        
        // TODO: Remove later
        standardBuilding1 = new sheep::StandardBuilding(mainProgram, "position");
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
    standardBuilding1->render("world", "projectionView", "textureUniform", projectionViewMatrix);
}
