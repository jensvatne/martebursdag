#pragma once
#include "pokemon/Pokemon.h"
#include "misc/Status.h"

struct MoveResult {
    std::string moveName;
    int damage;
    bool hit;
    bool crit;
    double type_multiplier;
    Status status_applied;
    bool flinched;
    bool protect;
    int recoil;
    int drain;
    int healing;
    bool status;
    Type moveType;
};

class Simulator {
    public:
        Simulator(Pokemon& pokemon1, Pokemon& pokemon2);
        void runBattle();
        void runTurn(int moveIndex_p1, int moveIndex_p2);
        MoveResult applyMove(Move& move, Pokemon& pokemon1, Pokemon& pokemon2);
        void applyEndOfTurn(Move& move, Pokemon& pokemon1, Pokemon& pokemon2);
        bool executeTurn(Move& move, Pokemon& attacker, Pokemon& defender);
        bool isValidMoveCheck(Pokemon& pokemon, int moveIndex);
        bool applyDamage(MoveResult& moveResult, Pokemon& attacker, Pokemon& defender);
        bool checkStatus(Pokemon& attacker);
        bool isImmuneToStatus(Pokemon& pokemon, Status status);
        void applyStatusDamage(Pokemon& pokemon);

    private:
        Pokemon& m_pokemon1;
        Pokemon& m_pokemon2;
};
