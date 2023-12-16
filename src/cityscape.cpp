#include "cityscape.h"

// Changeable Constant Values:

// Determines how many chunks to generate in the cityscape based on the grid.
// Each chunk contains 4 buildings.
// Eg. If GRID_SIZE = 10, then there are 10 x 10 = 100 chunks, so there are 400 buildings.
const int GRID_SIZE = 10;

// =================================================================================================================
// =================================================================================================================

Cityscape::~Cityscape()
{
    printf("Destructing Cityscape World...\n");

    wolf::ProgramManager::DestroyProgram(mainProgram);
    delete camera;
    delete entityManager;

    printf("Cityscape World destructed successfully.\n");
}

void Cityscape::init()
{

    // Initialize program for the first time

    if (!mainProgram)
    {
        glEnable(GL_DEPTH_TEST);

        mainProgram = wolf::ProgramManager::CreateProgram("data/texture.vsh", "data/texture.fsh");
        entityManager = new sheep::EntityManager(GRID_SIZE, mainProgram, "position");
        camera = new sheep::FirstPersonCamera(m_pApp);
    }
}

void Cityscape::update(float dt)
{
    time += dt;
    camera->update(dt);

    if (m_pApp->isKeyJustDown('r'))
    {
        regenerate();
    }
}

void Cityscape::render(int width, int height)
{

    glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projectionMatrix = camera->getProjectionMatrix(width, height);
    glm::mat4 viewMatrix = camera->getViewMatrix();

    glm::mat4 projectionViewMatrix = projectionMatrix * viewMatrix;

    entityManager->render("world", "projectionView", "tex", projectionViewMatrix);
}

void Cityscape::regenerate()
{
    printf("Regenerating world...\n");

    entityManager->regenerateEntities(GRID_SIZE);
}
