#include "battle/DamageCalc.h"
#include "move/Category_moves.h"
#include "pokemon/Stats.h"
#include "misc/Status.h"
#include "misc/Type.h"
#include "typechart/TypeChart.h"
#include <random>

bool isCrit(bool highCrit) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distrib(0, 15);

    int critRoll = distrib(generator);

    int critThreshold = 1;
    if (highCrit) {
        critThreshold = 4;
    }

    return critRoll < critThreshold;
}

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
) {

    double BURN = 1;
    if (statusAttack == Status::Burned && category == Category::Physical) {
        BURN = 0.5;
    }

    int totalStatsAttack;
    int totalStatsDefence;

    if (category == Category::Special) {
        totalStatsAttack  = calculatedStatsAttack.spAttack    * stageToMultiplier(battleStagesAttack.spAttack);
        totalStatsDefence = calculatedStatsDefence.spDefence  * stageToMultiplier(battleStagesDefence.spDefence);
        if (isCrit && battleStagesAttack.spAttack < 0)   { totalStatsAttack  = calculatedStatsAttack.spAttack; }
        if (isCrit && battleStagesDefence.spDefence > 0) { totalStatsDefence = calculatedStatsDefence.spDefence; }
    } else if (category == Category::Physical) {
        totalStatsAttack  = calculatedStatsAttack.attack    * stageToMultiplier(battleStagesAttack.attack);
        totalStatsDefence = calculatedStatsDefence.defence  * stageToMultiplier(battleStagesDefence.defence);
        if (isCrit && battleStagesAttack.attack < 0)   { totalStatsAttack  = calculatedStatsAttack.attack; }
        if (isCrit && battleStagesDefence.defence > 0) { totalStatsDefence = calculatedStatsDefence.defence; }
    } else {
        return 0;
    }

    double STAB = 1.0;
    if (moveType == pokemonAttackType1 || moveType == pokemonAttackType2) {
        STAB = 1.5;
    }

    double critMultiplier = 1.0;
    if (isCrit) {
        critMultiplier = 2.0;
    }

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> randomDistrib(85, 100);
    double randomFactor = randomDistrib(generator) / 100.0;

    double damage = (((2.0 * level / 5 + 2) * power * totalStatsAttack / totalStatsDefence) / 50 + 2)
             * BURN * critMultiplier * STAB * typeEffectiveness * randomFactor;

    return static_cast<int>(damage);
}
