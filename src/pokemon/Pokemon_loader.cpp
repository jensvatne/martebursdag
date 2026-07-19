#include "pokemon/Pokemon_loader.h"
#include "move/Move_loader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>


std::vector<Pokemon> loadPokemon() {

    Move struggle = loadMoves()[0];

    std::vector<Pokemon> pokemonVector;

    std::ifstream fil("data/test_pokemonv1.txt");
    if (!fil.is_open()) {
        throw std::runtime_error("Klarte ikke åpne fil");
    }

    std::string linje;
    while (std::getline(fil, linje)) {
        if (linje.empty() || linje[0] == '#') continue;

        std::stringstream ss(linje);

        //basic
        std::string nameStr, type1Str, type2Str;

        //basestats
        std::string HPStr, attackStr, defenceStr, spAttackStr, spDefenceStr, speedStr;

        //hente ut strings:
        std::getline(ss, nameStr, ',');
        std::getline(ss, type1Str, ',');
        std::getline(ss, type2Str, ',');
        std::getline(ss, HPStr, ',');
        std::getline(ss, attackStr, ',');
        std::getline(ss, defenceStr, ',');
        std::getline(ss, spAttackStr, ',');
        std::getline(ss, spDefenceStr, ',');
        std::getline(ss, speedStr, ',');

        //konvertere til riktige typer, for å senere kunne sette dem inn i pokemon klassen
        try{
            std::string name = nameStr;
            Type type1 = stringToType(type1Str);
            Type type2 = stringToType(type2Str);

            int HP = std::stoi(HPStr);
            int attack = std::stoi(attackStr);
            int spAttack = std::stoi(spAttackStr);
            int defence = std::stoi(defenceStr);
            int spDefence = std::stoi(spDefenceStr);
            int speed = std::stoi(speedStr);
            BaseStats baseStats = {HP, attack, defence, spAttack, spDefence, speed};

            int target = 650;
            int BST = HP + attack + spAttack + defence + spDefence + speed;

            int level = (target - 35) / (2*BST/100 + 1);

            BattleStages defaultStages = {};
            Pokemon newPokemon(name, type1, type2, level, baseStats, defaultStages);
            newPokemon.addMove(struggle);
            pokemonVector.push_back(newPokemon);

        } catch (const std::exception& e) {
            throw std::runtime_error("Feil i Pokemon-linje: " + linje + " -> " + e.what());
        }
    }
    return pokemonVector;
}
