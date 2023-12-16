#pragma once
#include "../../src/randomNumberGenerator.h"
#include "../structures/basicStructures.h"
#include "../structures/textureMap.h"
#include <vector>
#include <map>

// Entities
#include "land.h"
#include "buildingTypes/standardBuilding.h"
#include "buildingTypes/polygonBuilding.h"

namespace sheep
{

    class EntityManager
    {
        public:

            EntityManager(int gridSize, wolf::Program* program, const std::string& positionUniform);

            ~EntityManager();

            void regenerateEntities(int gridSize);

            void render(const std::string& worldUniform, const std::string& projectionViewUniform, 
                        const std::string& textureUniform, const glm::mat4& projectionViewMatrix);

            void clearEntities();

        private:

            int gridSize;
            wolf::Program* program;
            std::string positionUniform;

            // Entities
            std::vector<Land*> landVector;
            std::vector<StandardBuilding*> standardBuildings;
            std::vector<PolygonBuilding*> polygonBuildings;

            void generateEntities();

            void addBuilding(int x, int z);
    };
}