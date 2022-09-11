#pragma once

#include <random>


class RNG
{
public:
    RNG();
    int get(const int& min, const int& max);


private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distrib;
};

RNG::RNG()
:   gen(rd()) {}

int RNG::get(const int& min, const int& max)
{
    return min + distrib(gen) % max;
}