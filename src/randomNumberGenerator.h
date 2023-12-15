#pragma once

#include <random>

class RandomNumberGenerator
{
    public:
        static int getRandomNumber(int min, int max);
        static RandomNumberGenerator& getInstance();

    private:
        RandomNumberGenerator();
        static std::mt19937 generator;
};
