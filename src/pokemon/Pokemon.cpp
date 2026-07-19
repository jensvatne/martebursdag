#include "pokemon/Pokemon.h"
#include <stdexcept>
#include <iostream>

//startverdier
Pokemon::Pokemon(std::string name,
            Type type_1,
            Type type_2,
            int level,
            BaseStats baseStats,
            BattleStages battlestages) :

    m_name{name},
    m_type_1{type_1},
    m_type_2{type_2},
    m_level{level},
    m_baseStats{baseStats},
    m_calculatedStats{},
    m_battleStages{0,0,0,0,0,0,0},
    m_status{Status::None},
    m_toxicCounter{0},
    m_sleepCounter{0},
    m_isFlinched{false},
    m_isProtected{false},
    m_consecutiveProtect{0},
    m_confusionCounter{0},
    m_isConfused{false}
{
    //formler for hvordan stats til pokemon regens ut
    m_calculatedStats.hp = (2 * m_baseStats.hp * m_level) / 100 + m_level + 10;
    m_calculatedStats.attack = (2 * m_baseStats.attack * m_level) / 100 + 5;
    m_calculatedStats.defence = (2 * m_baseStats.defence * m_level) / 100 + 5;
    m_calculatedStats.spAttack = (2 * m_baseStats.spAttack * m_level) / 100 + 5;
    m_calculatedStats.spDefence = (2 * m_baseStats.spDefence * m_level) / 100 + 5;
    m_calculatedStats.speed = (2 * m_baseStats.speed * m_level) / 100 + 5;

    m_curr_HP = m_calculatedStats.hp;
}

//moveset
void Pokemon::addMove (Move move) {if (m_moves.size() < 5){m_moves.push_back(move);};} //legger til trekk i m_moves-vector
Move& Pokemon::getMove(int index) {
    if (index < 0 || index >= (int)m_moves.size()) {
        throw std::out_of_range(m_name + " har ikke trekk på index " + std::to_string(index));
    }
    return m_moves[index];
}

//battle
void Pokemon::tookDamage(int damage) { //trekker fra damage (en variabel som regnes ut i simulatordel) fra HP
    m_curr_HP -= damage;
    if (m_curr_HP < 0) {
        m_curr_HP = 0;
    }
}

void Pokemon::healDamage(int healing) {
    m_curr_HP += healing;
    if (m_curr_HP > m_calculatedStats.hp) {
        m_curr_HP = m_calculatedStats.hp;
    }
}


bool Pokemon::hasFainted() {return m_curr_HP < 1;} //sjekker om pokemon har faintet

//status
void Pokemon::setStatus(Status status) {m_status = status;} //sette status til noe spesifikt (kan være none)
void Pokemon::setToxicCounter(int toxicCounter) {m_toxicCounter = toxicCounter;} //sette toxicCounter til noe spesifikt
void Pokemon::setSleepCounter(int sleepCounter) {m_sleepCounter = sleepCounter;} //sette sleepCounter til noe spesifikt
void Pokemon::incrementToxicCounter() {m_toxicCounter += 1;}//øke toxiccounter med 1
void Pokemon::deIncrementSleepCounter() {m_sleepCounter -= 1;};//senke sleepCounter med 1
void Pokemon::deIncrementConfusionCounter() {m_confusionCounter -= 1;}

//battlestate
void Pokemon::setIsFlinched(bool isFlinched) {m_isFlinched = isFlinched;}
void Pokemon::setIsProtected(bool isProtected) {m_isProtected = isProtected;}
void Pokemon::setIsConfused(bool isConfused) {m_isConfused = isConfused;}
void Pokemon::incrementConsecutiveProtect() {m_consecutiveProtect += 1;}
void Pokemon::resetConsecutiveProtect() {m_consecutiveProtect = 0;}
void Pokemon::setConfuisionCounter(int confusionCounter) { m_confusionCounter = confusionCounter; };

//battlestages
int Pokemon::clamp(int value) {
    if (value > 6) return 6;
    if (value < -6) return -6;
    return value;
}

void Pokemon::applyAndClamp(int& stage, int magnitude, const std::string& statName) {
    int before = stage;
    stage += magnitude;
    stage = clamp(stage);
    if (stage == before) {
        if (magnitude > 0) {
            std::cout << m_name << "'s " << statName << " won't go any higher!\n";
        } else {
            std::cout << m_name << "'s " << statName << " won't go any lower!\n";
        }
    }
}

void Pokemon::applyStatChange(StatChange stat, int magnitude) {
    switch (stat) {
        case StatChange::Attack:    applyAndClamp(m_battleStages.attack,    magnitude, "Attack");   break;
        case StatChange::Defense:   applyAndClamp(m_battleStages.defence,   magnitude, "Defense");  break;
        case StatChange::SpAttack:  applyAndClamp(m_battleStages.spAttack,  magnitude, "Sp. Atk"); break;
        case StatChange::SpDefence: applyAndClamp(m_battleStages.spDefence, magnitude, "Sp. Def"); break;
        case StatChange::Speed:     applyAndClamp(m_battleStages.speed,     magnitude, "Speed");    break;
        case StatChange::Accuracy:  applyAndClamp(m_battleStages.accuracy,  magnitude, "Accuracy"); break;
        case StatChange::Evasion:   applyAndClamp(m_battleStages.evasion,   magnitude, "Evasion");  break;
        case StatChange::AllStats:
            applyAndClamp(m_battleStages.attack,    magnitude, "Attack");
            applyAndClamp(m_battleStages.defence,   magnitude, "Defense");
            applyAndClamp(m_battleStages.spAttack,  magnitude, "Sp. Atk");
            applyAndClamp(m_battleStages.spDefence, magnitude, "Sp. Def");
            applyAndClamp(m_battleStages.speed,     magnitude, "Speed");
            break;
            case StatChange::None: break;
        }
}
void Pokemon::resetBattleStage() {m_battleStages={0,0,0,0,0,0,0};}

//get-funksjoner
// basis
std::string Pokemon::getName() const { return m_name; }
Type Pokemon::getType1() const { return m_type_1; }
Type Pokemon::getType2() const { return m_type_2; }
int Pokemon::getCurrHP() const { return m_curr_HP; }
int Pokemon::getLevel() const { return m_level; }

// moveset
std::vector<Move> Pokemon::getMoves() const { return m_moves; }

// status
Status Pokemon::getStatus() const { return m_status; }
int Pokemon::getToxicCounter() const { return m_toxicCounter; }
int Pokemon::getSleepCounter() const { return m_sleepCounter; }
bool Pokemon::getIsFlinched() const { return m_isFlinched; }
bool Pokemon::getIsConfused() const { return m_isConfused; }
int Pokemon::getConfusionCounter() const { return m_confusionCounter; }
bool Pokemon::getIsProtected() const { return m_isProtected; }
int Pokemon::getConsecutiveProtect() const { return m_consecutiveProtect; }

// stats
BaseStats Pokemon::getBaseStats() const { return m_baseStats; }
CalculatedStats Pokemon::getCalculatedStats() const { return m_calculatedStats; }
BattleStages Pokemon::getBattleStages() const { return m_battleStages; }
