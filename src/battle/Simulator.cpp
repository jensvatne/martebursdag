#include "battle/Simulator.h"
#include "move/Move.h"
#include "move/Special_effect.h"
#include "battle/DamageCalc.h"
#include "battle/StatusDamage.h"
#include "pokemon/Stats.h"
#include "typechart/TypeChart.h"
#include <iostream>
#include <random>

Simulator::Simulator(Pokemon& pokemon1, Pokemon& pokemon2) : m_pokemon1{pokemon1}, m_pokemon2{pokemon2} {}

void Simulator::runBattle() {

    while (!m_pokemon1.hasFainted() && !m_pokemon2.hasFainted()) {

        m_pokemon1.setIsProtected(false);
        m_pokemon2.setIsProtected(false);

        int moveIndex_p1, moveIndex_p2;

        std::cout << "\n========================================\n";
        std::cout << m_pokemon1.getName() << " HP: " << m_pokemon1.getCurrHP() << "  |  " << m_pokemon2.getName() << " HP: " << m_pokemon2.getCurrHP() << "\n";
        std::cout << "----------------------------------------\n";

        std::cout << "Moveindex for " << m_pokemon1.getName() << " : ";
        std::cin >> moveIndex_p1;

        while (!isValidMoveCheck(m_pokemon1, moveIndex_p1)) {

            bool struggle = false;

            for (int i = 1; i < static_cast<int>(m_pokemon1.getMoves().size()); i++) {
                if (m_pokemon1.getMoves()[i].getCurrPP() > 0) {
                    struggle = true;
                }
            }

            if (struggle == false) {
                moveIndex_p1 = 0;
                std::cout << m_pokemon1.getName() << " used struggle! \n";
            } else {
                std::cout << "Moveindex for " << m_pokemon1.getName() << " : ";
                std::cin >> moveIndex_p1;
            }

        }

        std::cout << "Moveindex for " << m_pokemon2.getName() << " : ";
        std::cin >> moveIndex_p2;
        while (!isValidMoveCheck(m_pokemon2, moveIndex_p2)) {

            bool struggle = false;

            for (int i = 1; i < static_cast<int>(m_pokemon2.getMoves().size()); i++) {
                if (m_pokemon2.getMoves()[i].getCurrPP() > 0) {
                    struggle = true;
                }
            }

            if (struggle == false) {
                moveIndex_p2 = 0;
                std::cout << m_pokemon2.getName() << " used struggle! \n";
            } else {
                std::cout << "Moveindex for " << m_pokemon2.getName() << " : ";
                std::cin >> moveIndex_p2;
            }

        }

        runTurn(moveIndex_p1, moveIndex_p2);
    }

    std::cout << "\n========================================\n";
    if (m_pokemon1.hasFainted()) {
        std::cout << m_pokemon1.getName() << " has fainted!\n";
    } else if (m_pokemon2.hasFainted()) {
        std::cout << m_pokemon2.getName() << " has fainted!\n";
    } else {
        std::cout << "what her skjedde det noe feil, sjekk simulator.cpp linje 27";
    }

}

void Simulator::runTurn(int moveIndex_p1, int moveIndex_p2) {
    int speed_p1 = m_pokemon1.getCalculatedStats().speed;
    int speed_p2 = m_pokemon2.getCalculatedStats().speed;

    m_pokemon1.setIsProtected(false);
    m_pokemon2.setIsProtected(false);

    if (m_pokemon1.getStatus() == Status::Paralyzed) {
        speed_p1 = speed_p1 / 2;
    }

    if (m_pokemon2.getStatus() == Status::Paralyzed) {
        speed_p2 = speed_p2 / 2;
    }

    Move& move_p1 = m_pokemon1.getMove(moveIndex_p1);
    Move& move_p2 = m_pokemon2.getMove(moveIndex_p2);

    if (move_p1.getPriority() == move_p2.getPriority()) {

        if (speed_p1 > speed_p2) {

            bool flinched = executeTurn(move_p1, m_pokemon1, m_pokemon2);

            if (!flinched && !m_pokemon2.hasFainted() && !m_pokemon1.hasFainted()) {
                executeTurn(move_p2, m_pokemon2, m_pokemon1);
            }

        } else if (speed_p1 < speed_p2) {

            bool flinched = executeTurn(move_p2, m_pokemon2, m_pokemon1);

            if (!flinched && !m_pokemon1.hasFainted() && !m_pokemon2.hasFainted()) {
                executeTurn(move_p1, m_pokemon1, m_pokemon2);
            }

        } else {

        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<int> distrib(0, 99);

        int roll = distrib(generator);
        if (roll < 50) {

            bool flinched = executeTurn(move_p1, m_pokemon1, m_pokemon2);

            if (!flinched && !m_pokemon2.hasFainted() && !m_pokemon1.hasFainted()) {
                executeTurn(move_p2, m_pokemon2, m_pokemon1);
            }

        } else {

            bool flinched = executeTurn(move_p2, m_pokemon2, m_pokemon1);

            if (!flinched && !m_pokemon1.hasFainted() && !m_pokemon2.hasFainted()) {
                executeTurn(move_p1, m_pokemon1, m_pokemon2);
            }
        }
    }

    } else if (move_p1.getPriority() > move_p2.getPriority()) {

        bool flinched = executeTurn(move_p1, m_pokemon1, m_pokemon2);

        if (!flinched && !m_pokemon2.hasFainted() && !m_pokemon1.hasFainted()) {
            executeTurn(move_p2, m_pokemon2, m_pokemon1);
        }

    } else if (move_p1.getPriority() < move_p2.getPriority()) {

        bool flinched = executeTurn(move_p2, m_pokemon2, m_pokemon1);

        if (!flinched && !m_pokemon1.hasFainted() && !m_pokemon2.hasFainted()) {
            executeTurn(move_p1, m_pokemon1, m_pokemon2);
        }

    }

    applyStatusDamage(m_pokemon1);
    applyStatusDamage(m_pokemon2);

}

MoveResult Simulator::applyMove(Move& move, Pokemon& pokemon1, Pokemon& pokemon2){

    std::string moveName = move.getName();

    Type moveType = move.getType();

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distrib(0, 99);

    bool crit = isCrit(move.getHighCrit());

    double type_multiplier = getTypeEffectiveness(pokemon2.getType1(), pokemon2.getType2(), move.getType());

    int damage = damageCalculator
(
    move.getPower(),
    move.getCategory(),
    pokemon1.getCalculatedStats(),
    pokemon2.getCalculatedStats(),
    pokemon1.getBattleStages(),
    pokemon2.getBattleStages(),
    pokemon1.getStatus(),
    move.getType(),
    pokemon1.getType1(),
    pokemon1.getType2(),
    pokemon2.getType1(),
    pokemon2.getType2(),
    type_multiplier,
    crit,
    pokemon1.getLevel()
);

    int roll1 = distrib(generator);

    double effectiveAccuracy = move.getAccuracy()
        * stageToMultiplier(pokemon1.getBattleStages().accuracy)
        / stageToMultiplier(pokemon2.getBattleStages().evasion);
    bool hit = roll1 < static_cast<int>(effectiveAccuracy);

    if (move.getAccuracy() == -1 || move.getAlwaysHits()) {
        hit = true;
    }

    Status status_applied = move.getStatus();

    int roll3 = distrib(generator);
    bool flinched = roll3 < move.getFlinchChance();

    bool protect = false;
    if (move.getSpecialEffect() == SpecialEffect::Protect) {
        protect = protectConsecutiveChance(pokemon1);
    }

    int recoil = move.getRecoil();
    int drain = move.getDrain();
    int healing = move.getHealing();

    bool status;
    if (move.getCategory() == Category::Status) {
        status = true;
    } else { status = false;}

    return MoveResult(moveName, damage, hit, crit, type_multiplier, status_applied, flinched, protect, recoil, drain, healing, status, moveType);
}

bool Simulator::executeTurn(Move& move, Pokemon& attacker, Pokemon& defender) {

    if (!checkStatus(attacker)) {
        return false;
    }

    if (attacker.getIsConfused()) {

        std::cout << attacker.getName() << " is confused! \n";

        attacker.deIncrementConfusionCounter();

        if (attacker.getConfusionCounter() == 0) {

            attacker.setIsConfused(false);
            std::cout << attacker.getName() << " snapped out of confusion! \n";

        } else {

            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_int_distribution<int> distrib(0, 1);

            int roll = distrib(generator);

            if (roll == 0) {

                std::cout << attacker.getName() << " hit themselves in confusion! \n";

                int level = attacker.getLevel();
                double attack = attacker.getCalculatedStats().attack * stageToMultiplier(attacker.getBattleStages().attack);
                double defence = attacker.getCalculatedStats().defence * stageToMultiplier(attacker.getBattleStages().defence);

                int confusionDamage = static_cast<int>(((2.0 * level / 5 + 2) * 40 * attack / defence) / 50 + 2);

                attacker.tookDamage(confusionDamage);

                return false;

            }

        }
    }

    MoveResult moveResult = applyMove(move, attacker, defender);

    if (move.getSpecialEffect() == SpecialEffect::Protect && !moveResult.protect) {

        std::cout << attacker.getName() << " used Protect! \n";
        std::cout << "But it failed! \n";

        move.use();
        return false;
    }

    if (moveResult.protect && move.getSpecialEffect() == SpecialEffect::Protect) {
        attacker.setIsProtected(moveResult.protect);

        std::cout << attacker.getName() << " used Protect! \n";

        move.use();

        attacker.incrementConsecutiveProtect();
        return false;
    }

    move.use();
    attacker.resetConsecutiveProtect();

    if (applyDamage(moveResult, attacker, defender)) {
        if (!defender.getIsProtected()) {
            applyEndOfTurn(move, attacker, defender);
        }
        return moveResult.flinched;
    }

    return false;
}

void Simulator::applyEndOfTurn(Move& move, Pokemon& pokemon1, Pokemon& pokemon2) {

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distrib(0, 99);

    if (move.getStatus() != Status::None) {

        int roll1 = distrib(generator);

        if (roll1 < move.getStatusChance()) {

            if (move.getStatusTarget() == true && pokemon1.getStatus() == Status::None
                && !isImmuneToStatus(pokemon1, move.getStatus())) {
                pokemon1.setStatus(move.getStatus());

                if (pokemon1.getStatus() == Status::Asleep) {
                    std::uniform_int_distribution<int> distrib2(1,4);
                    pokemon1.setSleepCounter(distrib2(generator));
                }

            } else if (move.getStatusTarget() == false && pokemon2.getStatus() == Status::None
                        && !isImmuneToStatus(pokemon2, move.getStatus())) {
                pokemon2.setStatus(move.getStatus());

                if (pokemon2.getStatus() == Status::Asleep) {
                    std::uniform_int_distribution<int> distrib2(1,4);
                    pokemon2.setSleepCounter(distrib2(generator));
                }
            }
        }
    }

    if (!move.getStatChange1().empty()){
        int roll2 = distrib(generator);
        if (roll2 < move.getStatChangeChance1()) {

            std::vector<StatChange> stats = move.getStatChange1();
            int magnitude = move.getStatChangeMagnitude1();
            bool targetSelf = move.getStatTarget1();

            for (const StatChange& stat : stats) {
                if (targetSelf) {
                    pokemon1.applyStatChange(stat, magnitude);
                } else {
                    pokemon2.applyStatChange(stat, magnitude);
                }
            }
        }
    }

    if (!move.getStatChange2().empty()){
        int roll3 = distrib(generator);
        if (roll3 < move.getStatChangeChance2()) {

            std::vector<StatChange> stats = move.getStatChange2();
            int magnitude = move.getStatChangeMagnitude2();
            bool targetSelf = move.getStatTarget2();

            for (const StatChange& stat : stats) {
                if (targetSelf) {
                    pokemon1.applyStatChange(stat, magnitude);
                } else {
                    pokemon2.applyStatChange(stat, magnitude);
                }
            }
        }
    }

    if (move.getConfusion()) {
        pokemon2.setIsConfused(true);
        pokemon2.setConfuisionCounter(2 + rand() % 4);
        std::cout << pokemon2.getName() << " became confused! \n";
    }

}

void Simulator::applyStatusDamage(Pokemon& pokemon) {
    if (pokemon.getStatus() == Status::Burned) {
        if (!pokemon.hasFainted()) {
            std::cout << pokemon.getName() << " was hurt by its burn!\n";
            pokemon.tookDamage(burnDamage(pokemon.getBaseStats().hp));
        }
    } else if (pokemon.getStatus() == Status::Poisoned) {
        if (!pokemon.hasFainted()) {
            std::cout << pokemon.getName() << " was hurt by poison!\n";
            pokemon.tookDamage(poisonDamage(pokemon.getBaseStats().hp));
        }
    } else if (pokemon.getStatus() == Status::Toxic) {
        if (!pokemon.hasFainted()) {
            std::cout << pokemon.getName() << " was badly hurt by poison!\n";
            pokemon.tookDamage(toxicDamage(pokemon.getBaseStats().hp, pokemon.getToxicCounter()));
            pokemon.incrementToxicCounter();
        }
    }
}


bool Simulator::isValidMoveCheck(Pokemon& pokemon, int moveIndex) {
    if (moveIndex >= 0 && moveIndex < static_cast<int>(pokemon.getMoves().size())) {
        if (pokemon.getMove(moveIndex).getCurrPP() > 0) {
            return true;
        } else {
            std::cout << pokemon.getMove(moveIndex).getName() << " is out of PP!" << "\n";
            return false;
        }
    } else {
        std::cout << moveIndex << " is out of movelist!" << "\n";
        return false;
    }
}

bool Simulator::checkStatus(Pokemon& attacker) {

    if (attacker.getStatus() == Status::Asleep) {

        attacker.deIncrementSleepCounter();

        if (attacker.getSleepCounter() == 0) {

            attacker.setStatus(Status::None);
            std::cout << attacker.getName() << " woke up! \n";
            return true;

        } else {

            std::cout << attacker.getName() << " is fast asleep! \n";
            return false;
        }

    } else if (attacker.getStatus() == Status::Frozen) {

        std::random_device rd_freeze;
        std::default_random_engine generator(rd_freeze());
        std::uniform_int_distribution<int> distrib(0, 4);
        int roll1 = distrib(generator);

        if (roll1 == 0) {

            attacker.setStatus(Status::None);
            std::cout << attacker.getName() << " thawed out! \n";
            return true;

        } else {

            std::cout << attacker.getName() << " is frozen! \n";
            return false;

        }

    } else if (attacker.getStatus() == Status::Paralyzed) {

        std::random_device rd_para;
        std::default_random_engine generator(rd_para());
        std::uniform_int_distribution<int> distrib(0, 3);
        int roll2 = distrib(generator);

        std::cout << attacker.getName() << " is paralyzed!\n";

        if (roll2 == 0) {
            std::cout << attacker.getName() << " couldn't move due to it's paralysis\n";
            return false;
        } else {
            return true;
        }

    } else {

        return true;

    }
}

bool Simulator::applyDamage(MoveResult& moveResult, Pokemon& attacker, Pokemon& defender) {

    if (!moveResult.hit) {
        std::cout << attacker.getName() << " used " << moveResult.moveName << " but it missed! \n";
        return false;
    }

    std::cout << attacker.getName() << " used " << moveResult.moveName << "\n";

    if (moveResult.crit && !moveResult.status) {
        std::cout << "A critical hit! \n";
    }

    if (moveResult.type_multiplier >= 2.0 && !defender.getIsProtected() && !moveResult.status) {
        std::cout << "It's super effective! \n";
    } else if (moveResult.type_multiplier > 0.0 && moveResult.type_multiplier < 1.0 && !defender.getIsProtected() && !moveResult.status) {
        std::cout << "It's not very effective... \n";
    } else if (moveResult.type_multiplier == 0.0 && !moveResult.status && !defender.getIsProtected()) {
        std::cout << "It doesn't affect " << defender.getName() << "! \n";
        return false;
    }

    if (!defender.getIsProtected()) {

        int hpBeforeDamage = defender.getCurrHP();
        defender.tookDamage(moveResult.damage);

        if (defender.getStatus() == Status::Frozen && moveResult.moveType == Type::Fire) {
            defender.setStatus(Status::None);
            std::cout << defender.getName() << " thawed out! \n";
        }

        if (moveResult.recoil > 0) {
            if (moveResult.damage > hpBeforeDamage) {
                int recoilDamage = hpBeforeDamage * moveResult.recoil / 100;
                attacker.tookDamage(recoilDamage);
            } else {
                int recoilDamage = moveResult.damage * moveResult.recoil / 100;
                attacker.tookDamage(recoilDamage);
            }
            std::cout << attacker.getName() << " took recoil damage! \n";
        }

        if (moveResult.drain > 0) {
            if (moveResult.damage > hpBeforeDamage) {
                int drainAmount = hpBeforeDamage * moveResult.drain / 100;
                attacker.healDamage(drainAmount);
            } else {
                int drainAmount = moveResult.damage * moveResult.drain / 100;
                attacker.healDamage(drainAmount);
            }
            std::cout << attacker.getName() << " drained HP! \n";
        }

        if (moveResult.healing > 0) {
            int healAmount = attacker.getBaseStats().hp * moveResult.healing / 100;
            attacker.healDamage(healAmount);
            std::cout << attacker.getName() << " restored HP! \n";
        }

        if (defender.hasFainted()) {
            std::cout << defender.getName() << " fainted! \n";
        }

    } else {

        std::cout << defender.getName() << " defended themselves! \n";
    }

    return true;
}

bool Simulator::isImmuneToStatus(Pokemon& pokemon, Status status) {
    if (status == Status::Burned) {
        if (pokemon.getType1() == Type::Fire || pokemon.getType2() == Type::Fire) {
            std::cout << pokemon.getName() << " cannot be burned! \n";
            return true;
        }
    }
    if (status == Status::Paralyzed) {
        if (pokemon.getType1() == Type::Electric || pokemon.getType2() == Type::Electric) {
            std::cout << pokemon.getName() << " is immune to paralysis! \n";
            return true;
        }
    }
    if (status == Status::Poisoned || status == Status::Toxic) {
        if (pokemon.getType1() == Type::Poison || pokemon.getType2() == Type::Poison) {
            std::cout << pokemon.getName() << " is immune to toxic! \n";
            return true;
        }
        if (pokemon.getType1() == Type::Steel || pokemon.getType2() == Type::Steel) {
            std::cout << pokemon.getName() << " is immune to poison! \n";
            return true;
        }
    }
    return false;
}
