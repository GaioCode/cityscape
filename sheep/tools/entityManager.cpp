#include "entityManager.h"

namespace sheep {

    const float LAND_SIZE = 4.65f;
    const std::string& bldgTexture = "data/textures/tilepack_64_bit.png";
    const std::string& landTexture = "data/textures/road_208x208_v2.png";

    EntityManager::EntityManager(int gridSize, wolf::Program* program, const std::string& positionUniform)
        : gridSize(gridSize), program(program), positionUniform(positionUniform)
    {
        generateEntities();
    }

    EntityManager::~EntityManager()
    {
        clearEntities();
    }

    void EntityManager::regenerateEntities(int gridSize)
    {
        clearEntities();

        generateEntities();
        
    }

    void EntityManager::generateEntities()
    {
        printf("EntityManager: Generating buildings...\n");

        GLfloat landXOffset = 0.0f;
        GLfloat landZOffset = 0.0f;
        const GLfloat LAND_Y_OFFSET = -1.0f;
        
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                Land* land = new Land(program, positionUniform, landTexture);
                landVector.push_back(land);
                landVector[landVector.size() - 1]->translate(landXOffset, LAND_Y_OFFSET, landZOffset);
                landVector[landVector.size() - 1]->scale(LAND_SIZE, 1.0f, LAND_SIZE);

                landZOffset += LAND_SIZE;
            }

            landZOffset = 0.0f;
            landXOffset += LAND_SIZE;
        }

        // Construct buildings

        // Offset factors
        const GLfloat INITIAL_OFFSET = -2.5f;                   // Starting location of the building with reference to land
        const GLfloat BLDG_OFFSET = 0.4f;                       // Empty space between two buildings
        const GLfloat ROAD_OFFSET = 1.5f;                       // Offset between building and road
        const GLfloat SIDEWALK_OFFSET = 0.3f;                   // Empty space between the building and sidewalk edge
        
        const GLfloat EDGE_OFFSET 
            = INITIAL_OFFSET + ROAD_OFFSET + SIDEWALK_OFFSET;   // Offset the first building from the edge
        GLfloat bldgSizeOffset = 0.0f;                          // Offset current building with the previous building's size

        // Offset calculation 

        GLfloat chunkXOffset = 0.0f;                            // Offset to the next chunk in x
        GLfloat chunkZOffset = 0.0f;                            // Offset to the next chunk in z
        GLfloat bldgXOffset = chunkXOffset + EDGE_OFFSET;
        GLfloat bldgZOffset = chunkZOffset + EDGE_OFFSET;
        GLfloat rotationAngle = 0.0f;                           // Rotates building after each building is placed

        // TODO: Move this later
        // Retrieve texture regions

        TextureType base;
        TextureType door;
        TextureType window;
        TextureType roof;        

        // TODO: Delete later
        int numBuilding = 0;

        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                // Generate 4 buildings per land chunk
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        // Randomize building type and parameters

                        RandomNumberGenerator& rng = RandomNumberGenerator::getInstance();
                        int heightRandom = rng.getRandomNumber(3, 8);
                        int sidesRandom = rng.getRandomNumber(3, 8);
                        int textureSetIndex = rng.getRandomNumber(0, textureSets.size() - 1);
                        TextureSet chosenSet = textureSets[textureSetIndex];
                        int rotationRandom = rng.getRandomNumber(0, 1);

                        // Determine the rotation based on position (k, l) in the chunk, with a bit of randomness
                        if (k == 0 && l == 0) rotationAngle = rotationRandom == 1 ? 180.0f : 270.0f;
                        if (k == 0 && l == 1) rotationAngle = rotationRandom == 1 ? 270.0f : 0.0f;
                        if (k == 1 && l == 0) rotationAngle = rotationRandom == 1 ? 90.0f : 180.0f;
                        if (k == 1 && l == 1) rotationAngle = rotationRandom == 1 ? 0.0f : 90.0f;

                        // if (rng.getRandomNumber(0, 1) == 0)        // TODO: change back later
                        if (GL_TRUE)
                        {
                            // TODO: Randomize height with a weight system later
                            StandardBuilding* building
                                = new StandardBuilding(program, positionUniform, bldgTexture, heightRandom,
                                    chosenSet.base, chosenSet.door, chosenSet.window, chosenSet.roof);
                            standardBuildings.push_back(building);
                            standardBuildings[standardBuildings.size() - 1]->translate(bldgXOffset, 0.0f, bldgZOffset);
                            standardBuildings[standardBuildings.size() - 1]->rotate(0.0f, glm::radians(rotationAngle), 0.0f);

                            bldgSizeOffset = 1.0f;
                        }
                        else
                        {
                            PolygonBuilding* building = new PolygonBuilding(program, positionUniform, bldgTexture,
                                heightRandom, sidesRandom,
                                chosenSet.base, chosenSet.door, chosenSet.window, chosenSet.roof);
                            polygonBuildings.push_back(building);
                            polygonBuildings[polygonBuildings.size() - 1]->translate(bldgXOffset, 0.0f, bldgZOffset);
                            polygonBuildings[polygonBuildings.size() - 1]->rotate(0.0f, glm::radians(rotationAngle), 0.0f);

                            bldgSizeOffset = 1.0f;
                        }

                        printf("ding! rotateOffset = %f\n", rotationAngle); 
                        
                        bldgZOffset += bldgSizeOffset + BLDG_OFFSET;    // Offset z in local chunk

                        numBuilding++;
                    }
                    bldgZOffset = chunkZOffset + EDGE_OFFSET;       // Reset z to start of local chunk
                    bldgXOffset += bldgSizeOffset + BLDG_OFFSET;    // Offset x in local chunk
                }
                // After 4 buldings placed, move on to next chunk by offsetting z first
                chunkZOffset += LAND_SIZE;  // Offset z chunk

                // Reset buildings offset in local chunk
                bldgZOffset = chunkZOffset + EDGE_OFFSET;
                bldgXOffset = chunkXOffset + EDGE_OFFSET;
            }
            // Reset z chunk offset to the beginning and start offsetting x chunk
            chunkZOffset = 0.0f;
            chunkXOffset += LAND_SIZE;

            // Reset buildings offset in local chunk, but now offset x chunk by 1
            bldgZOffset = chunkZOffset + EDGE_OFFSET;
            bldgXOffset = chunkXOffset + EDGE_OFFSET;

        }

        printf("EntityManager: %d buildings generated.\n", numBuilding);
    }

    void EntityManager::render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                               const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
    {
        for (auto land : landVector) {
            land->render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
        }

        for (auto building : standardBuildings) {
            building->render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
        }
        
        for (auto building : polygonBuildings) {
            building->render(worldUniform, projectionViewUniform, textureUniform, projectionViewMatrix);
        }
    }

    void EntityManager::clearEntities()
    {
        printf("EntityManager: Destructing buildings...\n");

        for (auto land : landVector)
        {
            delete land;
        }
        landVector.clear();

        for (auto building : standardBuildings)
        {
            delete building;
        }
        standardBuildings.clear();

        for (auto building : polygonBuildings)
        {
            delete building;
        }
        polygonBuildings.clear();

        printf("EntityManager: Buildings destructed.\n");
    }
}
