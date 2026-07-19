#include "move/Move.h"

//startverdier
Move::Move(std::string name,
            Type type,
            Category category,
            int power,
            int accuracy,
            int PP,
            int priority,
            // status
            Status status,
            int status_chance,
            bool status_target,
            // stat slot 1
            std::vector<StatChange> stat_change_1,
            int stat_change_magnitude_1,
            int stat_change_chance_1,
            bool stat_target_1,
            // stat slot 2
            std::vector<StatChange> stat_change_2,
            int stat_change_magnitude_2,
            int stat_change_chance_2,
            bool stat_target_2,
            // misc
            int recoil,
            int healing,
            int drain,
            bool alwaysHits,
            bool highCrit,
            int flinchChance,
            SpecialEffect specialEffect,
            bool confusion,
            int confusionChance) :

    m_name{name},
    m_type{type},
    m_category{category},
    m_power{power},
    m_accuracy{accuracy},
    m_curr_PP{PP},
    m_max_PP{PP},
    m_priority{priority},
    m_status{status},
    m_status_chance{status_chance},
    m_status_target{status_target},
    m_stat_change_1{stat_change_1},
    m_stat_change_magnitude_1{stat_change_magnitude_1},
    m_stat_change_chance_1{stat_change_chance_1},
    m_stat_target_1{stat_target_1},
    m_stat_change_2{stat_change_2},
    m_stat_change_magnitude_2{stat_change_magnitude_2},
    m_stat_change_chance_2{stat_change_chance_2},
    m_stat_target_2{stat_target_2},
    m_recoil{recoil},
    m_healing{healing},
    m_drain{drain},
    m_alwayshits{alwaysHits},
    m_highCrit{highCrit},
    m_flinchChance{flinchChance},
    m_specialEffect{specialEffect},
    m_confusion{confusion},
    m_confusionChance{confusionChance} {
}

//trekke fra PP etter en "use"
void Move::use() {
    m_curr_PP -= 1;
}

//legge til PP etter en failed use
void Move::unUse() {
    m_curr_PP += 1;
}


//get-funksjoner
// basis
std::string Move::getName() const { return m_name; }
Type Move::getType() const { return m_type; }
Category Move::getCategory() const { return m_category; }
int Move::getPower() const { return m_power; }
int Move::getAccuracy() const { return m_accuracy; }
int Move::getMaxPP() const { return m_max_PP; }
int Move::getCurrPP() const { return m_curr_PP; }

int Move::getPriority() const { return m_priority; }

// status
Status Move::getStatus() const { return m_status; }
int Move::getStatusChance() const { return m_status_chance; }
bool Move::getStatusTarget() const { return m_status_target; }

// stat slot 1
std::vector<StatChange> Move::getStatChange1() const { return m_stat_change_1; }
int Move::getStatChangeMagnitude1() const { return m_stat_change_magnitude_1; }
int Move::getStatChangeChance1() const { return m_stat_change_chance_1; }
bool Move::getStatTarget1() const { return m_stat_target_1; }

// stat slot 2
std::vector<StatChange> Move::getStatChange2() const { return m_stat_change_2; }
int Move::getStatChangeMagnitude2() const { return m_stat_change_magnitude_2; }
int Move::getStatChangeChance2() const { return m_stat_change_chance_2; }
bool Move::getStatTarget2() const { return m_stat_target_2; }

// misc
int Move::getRecoil() const { return m_recoil; }
int Move::getHealing() const { return m_healing; }
int Move::getDrain() const { return m_drain; }
bool Move::getAlwaysHits() const { return m_alwayshits; }
bool Move::getHighCrit() const { return m_highCrit; }
int Move::getFlinchChance() const { return m_flinchChance; }
SpecialEffect Move::getSpecialEffect() const { return m_specialEffect; }
bool Move::getConfusion() const { return m_confusion; }
int Move::getConfusionChance() const { return m_confusionChance; }
