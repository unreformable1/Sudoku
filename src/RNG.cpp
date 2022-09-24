#include "RNG.hh"



std::random_device RNG::rd{};
std::mt19937 RNG::gen(rd());
std::uniform_int_distribution<int> RNG::distrib{};

int RNG::get(const int& min, const int& max)
{
    return min + distrib(gen) % max;
}