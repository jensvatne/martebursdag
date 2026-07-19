#pragma once
#include "move/Category_moves.h"
#include "pokemon/Stats.h"
#include "misc/Status.h"
#include "misc/Type.h"

bool isCrit(bool highCrit);

int damageCalculator(int power,
    Category category,
    CalculatedStats calculatedStatsAttack,
    CalculatedStats calculatedStatsDefence,
    BattleStages battleStagesAttack,
    BattleStages battleStagesDefence,
    Status statusAttack,
    Type moveType,
    Type pokemonAttackType1,
    Type pokemonAttackType2,
    Type pokemonDefenceType1,
    Type pokemonDefenceType2,
    double typeEffectiveness,
    bool isCrit,
    int level
);
