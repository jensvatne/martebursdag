#pragma once
#include <string>
#include <vector>
#include "misc/Type.h"
#include "move/Category_moves.h"
#include "misc/Status.h"
#include "move/Stat_change.h"
#include "move/Special_effect.h"

class Move {

    public:
        Move(std::string name,
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
            int confusionChance);

        void use(); //fjerner en PP fra move

        void unUse(); //legger til en PP til move

        //get-funksjoner:
        // basis
        std::string getName() const;
        Type getType() const;
        Category getCategory() const;
        int getPower() const;
        int getAccuracy() const;
        int getMaxPP() const;
        int getCurrPP() const;

        int getPriority() const;

        // status
        Status getStatus() const;
        int getStatusChance() const;
        bool getStatusTarget() const;

        // stat slot 1
        std::vector<StatChange> getStatChange1() const;
        int getStatChangeMagnitude1() const;
        int getStatChangeChance1() const;
        bool getStatTarget1() const;

        // stat slot 2
        std::vector<StatChange> getStatChange2() const;
        int getStatChangeMagnitude2() const;
        int getStatChangeChance2() const;
        bool getStatTarget2() const;

        // misc
        int getRecoil() const;
        int getHealing() const;
        int getDrain() const;
        bool getAlwaysHits() const;
        bool getHighCrit() const;
        int getFlinchChance() const;
        SpecialEffect getSpecialEffect() const;
        bool getConfusion() const;
        int getConfusionChance() const;

    private:
        std::string m_name;
        Type m_type;
        int m_power;
        int m_accuracy;
        int m_max_PP;
        int m_curr_PP;

        int m_priority;

        Category m_category; // physical, special eller status move

        //status effekter
        Status m_status; //ulike statuseffekter
        int m_status_chance; //sjanse for at status effekt treffer

        //stat(istikk) endringer nummer 1
        std::vector<StatChange> m_stat_change_1; //hva som endres
        int m_stat_change_magnitude_1; //finner hvor mye en stat skal endres med
        int m_stat_change_chance_1; //sjanse for at det endres
        bool m_stat_target_1; //stat(istikk) target, selv->true, motstander->false

        //stat(istikk) endringer nummer 2
        std::vector<StatChange> m_stat_change_2; //hva som endres
        int m_stat_change_magnitude_2; //finner hvor mye en stat skal endres med
        int m_stat_change_chance_2; //sjanse for at det endres
        bool m_stat_target_2; //stat(istikk) target, selv->true, motstander->false

        //misc
        int m_recoil; //sier seg selv
        int m_healing; //sier seg selv
        int m_drain; //hvor mye man healer på drain-moves
        bool m_alwayshits; //arial-ace f.eks
        int m_flinchChance; //sjanse for flinch
        SpecialEffect m_specialEffect; //egentlig bare protect
        bool m_highCrit; //høyere crit sjanse for noen trekk, om true->høyere sjanse
        bool m_status_target; //status target, selv->true, motstander->false
        bool m_confusion;
        int m_confusionChance;

};
