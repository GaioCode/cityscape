#include "randomNumberGenerator.h"
#include <chrono>

std::mt19937 RandomNumberGenerator::generator;

int RandomNumberGenerator::getRandomNumber(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

RandomNumberGenerator& RandomNumberGenerator::getInstance() {
    static RandomNumberGenerator instance;
    return instance;
}

RandomNumberGenerator::RandomNumberGenerator() {

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(static_cast<std::mt19937::result_type>(seed));
}