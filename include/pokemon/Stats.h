#pragma once

struct BaseStats {
    int hp;
    int attack;
    int defence;
    int spAttack;
    int spDefence;
    int speed;
};


struct CalculatedStats {
    int hp;
    int attack;
    int defence;
    int spAttack;
    int spDefence;
    int speed;
};


struct BattleStages {
    int attack;
    int defence;
    int spAttack;
    int spDefence;
    int speed;
    int accuracy;
    int evasion;
};


double stageToMultiplier (int stage);
