#include "cityscape.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Cityscape::~Cityscape()
{
    printf("Destructing Cityscape World...\n");
    wolf::ProgramManager::DestroyProgram(mainProgram);
    // wolf::ProgramManager::DestroyProgram(mainProgramTexture);   // TODO: Merge programs later
    printf("Cityscape World destructed successfully.\n");
    // delete cube1;       // TODO: Remove later
    delete texturedCube1;   // TODO: Remove later
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
        // cube1 = new Cube(mainProgram, "position", "color");     // TODO: Remove later
        texturedCube1 = new TexturedCube(mainProgram, "position");     // TODO: Remove later

        // cube1->translate(0.0f, 0.0f, 0.0f);
        texturedCube1->scale(2.0f, 8.0f, 3.5f);
        texturedCube1->translate(2.0f, 2.0f, 2.0f);
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

    // cube1->render("world", "projectionView", projectionViewMatrix);     // TODO: Remove later
    texturedCube1->render("world", "projectionView", "textureUniform", projectionViewMatrix);     // TODO: Remove later
}
