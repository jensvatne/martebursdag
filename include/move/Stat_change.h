#pragma once

enum class StatChange {
    None,

    // Enkeltstat-endringer
    Attack,         // Swords Dance (+2), Growl (-1)
    Defense,        // Iron Defense (+2), Tail Whip (-1)
    SpAttack,       // Growth (+1)
    SpDefence,
    Speed,          // Agility (+2), Cotton Spore (-2)
    Accuracy,       // Kinesis (-1)
    Evasion,        // Double Team (+1), Minimize (+1)

    AllStats,
};
