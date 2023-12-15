#include "cityscape.h"

Cityscape::~Cityscape()
{
    printf("Destructing Cityscape World...\n");

    wolf::ProgramManager::DestroyProgram(mainProgram);

    delete camera;

    // for (auto building : standardBuildings)
    // {
    //     delete building;
    // }

    for (auto building : polygonBuildings)
        {
            delete building;
        }

    // delete texturedCube1;
    // texturedCube1 = nullptr;

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

        isRegen = GL_TRUE;
    }

    // Reinitialize this section if regenerating world

    if (isRegen)
    {

        // Render objects

        float xOffset = 0.0f;
        float zOffset = 0.0f;
        int count = 0;
        
        // TODO: Remove later
        // for (int i = 0; i < 20; i++)
        // {
        //     for (int j = 0; j < 20; j++)
        //     {

        //         standardBuildings.push_back(new sheep::StandardBuilding(mainProgram, "position"));
        //         standardBuildings[count]->translate(xOffset, 0.0f, zOffset);

        //         zOffset += 2.0f;
        //         count++;
        //     }
        //     zOffset = 0.0f;
        //     xOffset += 2.0f;
        // }
        
        int heightRandom = 1;
        int sidesRandom = 3;

        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                // TODO: Put this somewhere better later
                RandomNumberGenerator& rng = RandomNumberGenerator::getInstance();
                heightRandom = RandomNumberGenerator::getInstance().getRandomNumber(3, 8);
                sidesRandom = RandomNumberGenerator::getInstance().getRandomNumber(3, 8);

                std::cout << "Building " << count << ": Height - " << heightRandom << ", Sides - " << sidesRandom << std::endl;

                polygonBuildings.push_back(new sheep::PolygonBuilding(mainProgram, "position", heightRandom, sidesRandom));
                polygonBuildings[count]->translate(xOffset, 0.0f, zOffset);

                zOffset += 2.0f;
                count++;
            }
            zOffset = 0.0f;
            xOffset += 2.0f;
        }

        // texturedCube1 = new TexturedCube(mainProgram, "position");

        isRegen = GL_FALSE;
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

    // TODO: Remove later
    // for (auto building : standardBuildings)
    // {
    //     building->render("world", "projectionView", "textureUniform", projectionViewMatrix);
    // }

    for (auto building : polygonBuildings)
    {
        building->render("world", "projectionView", "textureUniform", projectionViewMatrix);
    }

    // texturedCube1->render("world", "projectionView", "textureUniform", projectionViewMatrix);
}

void Cityscape::regenerate()
{
    printf("Regenerating world...\n");

    // for (auto building : standardBuildings)
    // {
    //     delete building;
    // }

    for (auto building : polygonBuildings)
    {
        delete building;
    }

    // standardBuildings.clear();

    polygonBuildings.clear();

    // delete texturedCube1;
    // texturedCube1 = nullptr;

    isRegen = GL_TRUE;

    init();
}
