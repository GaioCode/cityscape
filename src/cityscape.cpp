#include "cityscape.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Cityscape::~Cityscape()
{
    printf("Destructing Cityscape World...\n");
    wolf::ProgramManager::DestroyProgram(mainProgram);
    printf("Cityscape World destructed successfully.\n");

    // TODO: Remove later
    delete texturedCube1;   
    // delete normalBuilding1;
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
        texturedCube1 = new TexturedCube(mainProgram, "position");    

        // normalBuilding1 = new NormalBuilding(mainProgram, "position", 
        // sheep::ComponentHelper::generatePolygonSides(6, 1.0f, 1.0f));     

        // standardBuilding1 = new sheep::StandardBuilding(mainProgram, "position",    
        // sheep::ComponentHelper::generatePolygonSides(4, 1.0f, 1.0f));

        // standardBuilding1->translate(0.0f, 1.0f, 0.0f);
        // standardBuilding1->rotate(0.0f, glm::radians(45.0f), 0.0f);

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
    texturedCube1->render("world", "projectionView", "textureUniform", projectionViewMatrix);
    // normalBuilding1->render("world", "projectionView", "textureUniform", projectionViewMatrix);
    standardBuilding1->render("world", "projectionView", "textureUniform", projectionViewMatrix);
}
