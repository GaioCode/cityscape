#pragma once
#include "building.h"

namespace sheep
{
    class BuildingManager
    {
        public:
            // static enum BuildingType;

            BuildingManager();

            ~BuildingManager();

            // Provide a number of buildings and generate them randomly
            void generateRandomBuildings(int numBuilding);

        private:

    };
}