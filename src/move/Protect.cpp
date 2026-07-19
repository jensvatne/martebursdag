#include "move/Special_effect.h"
#include "pokemon/Pokemon.h"
#include <cmath>
#include <iostream>
#include <random>

bool protectConsecutiveChance (Pokemon& pokemon) {
    double sjanse = 1 / pow(2, pokemon.getConsecutiveProtect());

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distrib(0, 99);

    int roll = distrib(generator);

    if (roll < sjanse * 100 ) {
        return true;
    } else {
        return false;
    }
}
