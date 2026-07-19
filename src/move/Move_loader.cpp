#include "move/Move_loader.h"
#include <fstream>
#include <sstream>
#include <string>

Type stringToType(const std::string& s) {
    if (s == "None")     return Type::None;
    if (s == "Normal")   return Type::Normal;
    if (s == "Fire")     return Type::Fire;
    if (s == "Water")    return Type::Water;
    if (s == "Electric") return Type::Electric;
    if (s == "Grass")    return Type::Grass;
    if (s == "Ice")      return Type::Ice;
    if (s == "Fighting") return Type::Fighting;
    if (s == "Poison")   return Type::Poison;
    if (s == "Ground")   return Type::Ground;
    if (s == "Flying")   return Type::Flying;
    if (s == "Psychic")  return Type::Psychic;
    if (s == "Bug")      return Type::Bug;
    if (s == "Rock")     return Type::Rock;
    if (s == "Ghost")    return Type::Ghost;
    if (s == "Dragon")   return Type::Dragon;
    if (s == "Dark")     return Type::Dark;
    if (s == "Steel")    return Type::Steel;
    if (s == "Struggle") return Type::Struggle;

    throw std::invalid_argument("Ukjent type: " + s);
}

Category stringToCategory(const std::string& s) {
    if (s == "Physical") return Category::Physical;
    if (s == "Special")  return Category::Special;
    if (s == "Status")   return Category::Status;

    throw std::invalid_argument("Ukjent kategori: " + s);
}

SpecialEffect stringToSpecialEffect(const std::string& s) {
    if (s == "None")    return SpecialEffect::None;
    if (s == "Protect") return SpecialEffect::Protect;

    throw std::invalid_argument("Ukjent special effect: " + s);
}

StatChange stringToStatChange(const std::string& s) {
    if (s == "None")      return StatChange::None;
    if (s == "Attack")    return StatChange::Attack;
    if (s == "Defense")   return StatChange::Defense;
    if (s == "SpAttack")  return StatChange::SpAttack;
    if (s == "SpDefence") return StatChange::SpDefence;
    if (s == "Speed")     return StatChange::Speed;
    if (s == "Accuracy")  return StatChange::Accuracy;
    if (s == "Evasion")   return StatChange::Evasion;
    if (s == "AllStats") return StatChange::AllStats;

    throw std::invalid_argument("Ukjent stat change: " + s);
}

Status stringToStatus(const std::string& s) {
    if (s == "None")      return Status::None;
    if (s == "Burned")    return Status::Burned;
    if (s == "Paralyzed") return Status::Paralyzed;
    if (s == "Frozen")    return Status::Frozen;
    if (s == "Poisoned")  return Status::Poisoned;
    if (s == "Asleep")    return Status::Asleep;
    if (s == "Toxic")     return Status::Toxic;

    throw std::invalid_argument("Ukjent status: " + s);
}

bool stringToBool(const std::string& s) {
    return s == "true";
}

std::vector<StatChange> stringToStatChanges(const std::string& s) {
    if (s == "None") return {};  // tom vector

    std::vector<StatChange> result;
    std::stringstream ss(s);

    std::string part;

    while (std::getline(ss, part, '+')) {
        result.push_back(stringToStatChange(part));
    }

    return result;
}

std::vector<Move> loadMoves() {

    std::vector<Move> moves;

    std::ifstream file("data/test_movesv2.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Klarte ikke åpne moves-fil.");
    }

    std::string linje;
    while (std::getline(file, linje)) {
        if (linje.empty() || linje[0] == '#') continue;

        std::stringstream ss(linje);

        //lage variabler for alle strings som skal henter
        // basis
        std::string nameStr, typeStr, categoryStr, powerStr, accuracyStr, ppStr, priorityStr;

        // status
        std::string statusStr, statusChanceStr, statusTargetStr;

        // stat slot 1
        std::string statChange1Str, statMagnitude1Str, statChance1Str, statTarget1Str;

        // stat slot 2
        std::string statChange2Str, statMagnitude2Str, statChance2Str, statTarget2Str;

        // misc
        std::string recoilStr, healingStr, drainStr, alwaysHitsStr, highCritStr, flinchChanceStr, specialEffectStr;

        //faktisk hente ut disse stringsene
        std::getline(ss, nameStr, ',');
        std::getline(ss, typeStr, ',');
        std::getline(ss, categoryStr, ',');
        std::getline(ss, powerStr, ',');
        std::getline(ss, accuracyStr, ',');
        std::getline(ss, ppStr, ',');

        std::getline(ss, statusStr, ',');
        std::getline(ss, statusChanceStr, ',');
        std::getline(ss, statusTargetStr, ',');

        std::getline(ss, statChange1Str, ',');
        std::getline(ss, statMagnitude1Str, ',');
        std::getline(ss, statChance1Str, ',');
        std::getline(ss, statTarget1Str, ',');

        std::getline(ss, statChange2Str, ',');
        std::getline(ss, statMagnitude2Str, ',');
        std::getline(ss, statChance2Str, ',');
        std::getline(ss, statTarget2Str, ',');

        std::getline(ss, recoilStr, ',');
        std::getline(ss, healingStr, ',');
        std::getline(ss, drainStr, ',');
        std::getline(ss, alwaysHitsStr, ',');
        std::getline(ss, highCritStr, ',');
        std::getline(ss, flinchChanceStr, ',');
        std::getline(ss, specialEffectStr, ',');
        std::getline(ss, priorityStr, ',');

        std::string confusionStr, confusionChanceStr;
        std::getline(ss, confusionStr, ',');
        std::getline(ss, confusionChanceStr, ',');

        try { // tilfelle feil i en linje
            //konvertere til riktige typer nå
            // basis
            Type type = stringToType(typeStr);
            Category category = stringToCategory(categoryStr);
            int power = std::stoi(powerStr);
            int accuracy = std::stoi(accuracyStr);
            int pp = std::stoi(ppStr);

            int priority = std::stoi(priorityStr);

            // status
            Status status = stringToStatus(statusStr);
            int statusChance = std::stoi(statusChanceStr);
            bool statusTarget = stringToBool(statusTargetStr);

            // stat slot 1
            std::vector<StatChange> statChange1 = stringToStatChanges(statChange1Str);
            int statMagnitude1 = std::stoi(statMagnitude1Str);
            int statChance1 = std::stoi(statChance1Str);
            bool statTarget1 = stringToBool(statTarget1Str);

            // stat slot 2
            std::vector<StatChange> statChange2 = stringToStatChanges(statChange2Str);
            int statMagnitude2 = std::stoi(statMagnitude2Str);
            int statChance2 = std::stoi(statChance2Str);
            bool statTarget2 = stringToBool(statTarget2Str);

            // misc
            int recoil = std::stoi(recoilStr);
            int healing = std::stoi(healingStr);
            int drain = std::stoi(drainStr);
            bool alwaysHits = stringToBool(alwaysHitsStr);
            bool highCrit = stringToBool(highCritStr);
            int flinchChance = std::stoi(flinchChanceStr);
            SpecialEffect specialEffect = stringToSpecialEffect(specialEffectStr);

            bool confusion = stringToBool(confusionStr);
            int confusionChance = std::stoi(confusionChanceStr);


            // lage et moves,objekt, og putte inn i en move-vektor
            Move new_move(nameStr,
                type,
                category,
                power,
                accuracy,
                pp,
                priority,
                status, statusChance, statusTarget,
                statChange1, statMagnitude1, statChance1, statTarget1,
                statChange2, statMagnitude2, statChance2, statTarget2,
                recoil,
                healing,
                drain,
                alwaysHits,
                highCrit,
                flinchChance,
                specialEffect,
                confusion,
                confusionChance);

                moves.push_back(new_move);

        } catch (const std::exception& e) {
            throw std::invalid_argument ("Feil i linje: " + linje + " -> " + e.what());
        }

    }
    return moves;
}
