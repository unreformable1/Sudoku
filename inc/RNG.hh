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