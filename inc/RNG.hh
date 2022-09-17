#pragma once

#include <random>


class RNG
{
public:
    static int get(const int& min, const int& max);


private:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<int> distrib;
};

std::random_device RNG::rd{};
std::mt19937 RNG::gen(rd());
std::uniform_int_distribution<int> RNG::distrib{};

int RNG::get(const int& min, const int& max)
{
    return min + distrib(gen) % max;
}