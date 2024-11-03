#ifndef RANDOM_UTIL_H
#define RANDOM_UTIL_H

#include <random>

int GetRandomNumber(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}

#endif // RANDOM_UTIL_H