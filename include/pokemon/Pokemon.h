#pragma once
#include <string>
#include <vector>
#include "misc/Type.h"
#include "misc/Status.h"
#include "pokemon/Stats.h"
#include "move/Move.h"

class Pokemon {

    public:
        Pokemon(std::string name,
            Type type_1,
            Type type_2,
            int level,
            BaseStats baseStats,
            BattleStages battleStages);

        // moveset
        void addMove(Move move);
        Move& getMove(int index);

        // battle
        void tookDamage(int damage);
        void healDamage(int healing);
        bool hasFainted();

        // status
        void setStatus(Status status);
        void setToxicCounter(int toxicCounter);
        void setSleepCounter(int sleepCounter);
        void setIsConfused(bool isConfused);
        void incrementToxicCounter();
        void deIncrementSleepCounter();
        void deIncrementConfusionCounter();

        // battle state
        void setIsFlinched(bool isFlinched);
        void setIsProtected(bool isProtected);
        void incrementConsecutiveProtect();
        void resetConsecutiveProtect();
        void setConfuisionCounter(int confusionCounter);

        //battlestages
        int clamp(int value);
        void applyAndClamp(int& stage, int magnitude, const std::string& statName);
        void applyStatChange(StatChange stat, int magnitude);
        void resetBattleStage();

        // get-funksjoner:
        // basis
        std::string getName() const;
        Type getType1() const;
        Type getType2() const;
        int getCurrHP() const;
        int getLevel() const;

        // moveset
        std::vector<Move> getMoves() const;

        // status
        Status getStatus() const;
        int getToxicCounter() const;
        int getSleepCounter() const;
        bool getIsFlinched() const;
        bool getIsConfused() const;
        int getConfusionCounter() const;
        bool getIsProtected() const;
        int getConsecutiveProtect() const;

        //stats
        BaseStats getBaseStats() const;
        CalculatedStats getCalculatedStats() const;
        BattleStages getBattleStages() const;

    private:
        std::string m_name;
        Type m_type_1;
        Type m_type_2;
        int m_curr_HP;

        //moveset
        std::vector<Move> m_moves;

        //statuseffekter
        Status m_status;
        int m_toxicCounter;
        int m_sleepCounter;
        bool m_isFlinched;
        bool m_isConfused;
        int m_confusionCounter;
        bool m_isProtected;
        int m_consecutiveProtect;

        //stats (statistikk)
        int m_level;
        BaseStats m_baseStats;
        CalculatedStats m_calculatedStats;
        BattleStages m_battleStages;
};
