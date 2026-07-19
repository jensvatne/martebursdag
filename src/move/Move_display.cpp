#include <string>
#include <vector>
#include "misc/Type.h"
#include "move/Category_moves.h"
#include "move/Special_effect.h"
#include "move/Stat_change.h"
#include "misc/Status.h"

std::string typeToString (const Type& t) {
    switch (t) {
        case Type::None:     return "None";
        case Type::Normal:   return "Normal";
        case Type::Fire:     return "Fire";
        case Type::Water:    return "Water";
        case Type::Electric: return "Electric";
        case Type::Grass:    return "Grass";
        case Type::Ice:      return "Ice";
        case Type::Fighting: return "Fighting";
        case Type::Poison:   return "Poison";
        case Type::Ground:   return "Ground";
        case Type::Flying:   return "Flying";
        case Type::Psychic:  return "Psychic";
        case Type::Bug:      return "Bug";
        case Type::Rock:     return "Rock";
        case Type::Ghost:    return "Ghost";
        case Type::Dragon:   return "Dragon";
        case Type::Dark:     return "Dark";
        case Type::Steel:    return "Steel";
        case Type::Struggle: return "???";
    }
    throw std::invalid_argument("Ukjent Type");
}

std::string categoryToString (const Category& t) {
    switch (t) {
        case Category::Physical: return "Physical";
        case Category::Special:  return "Special";
        case Category::Status:   return "Status";
    }
    throw std::invalid_argument("Ukjent Category");
}

std::string specialEffectToString (const SpecialEffect& t) {
    switch (t) {
        case SpecialEffect::None:    return "None";
        case SpecialEffect::Protect: return "Protect";
    }
    throw std::invalid_argument("Ukjent SpecialEffect");
}

std::string statChangeToString (const StatChange& t) {
    switch (t) {
        case StatChange::None:      return "None";
        case StatChange::Attack:    return "Attack";
        case StatChange::Defense:   return "Defense";
        case StatChange::SpAttack:  return "SpAttack";
        case StatChange::SpDefence: return "SpDefence";
        case StatChange::Speed:     return "Speed";
        case StatChange::Accuracy:  return "Accuracy";
        case StatChange::Evasion:   return "Evasion";
        case StatChange::AllStats:  return "AllStats";
    }
    throw std::invalid_argument("Ukjent StatChange");
}

std::string statusToString (const Status& t) {
    switch (t) {
        case Status::None:      return "None";
        case Status::Burned:    return "Burned";
        case Status::Paralyzed: return "Paralyzed";
        case Status::Frozen:    return "Frozen";
        case Status::Poisoned:  return "Poisoned";
        case Status::Asleep:    return "Asleep";
        case Status::Toxic:     return "Toxic";
    }
    throw std::invalid_argument("Ukjent Status");
}

std::string boolToString (const bool& t) {
    switch (t) {
        case true:  return "True";
        case false: return "False";
    }
    throw std::invalid_argument("Ukjent bool(?)");
}

std::string statChangesToString (const std::vector<StatChange>& t) {
    if (t.empty()) return "None";

    std::string result;

    for (int i = 0; i < t.size(); i++) {
        result += statChangeToString(t[i]);
    }

    return result;
}
