#pragma once
#include <string>
#include <vector>
#include "misc/Type.h"
#include "move/Category_moves.h"
#include "move/Special_effect.h"
#include "move/Stat_change.h"
#include "misc/Status.h"

std::string typeToString (const Type& t);

std::string categoryToString (const Category& t);

std::string specialEffectToString (const SpecialEffect& t);

std::string statChangeToString (const StatChange& t);

std::string statusToString (const Status& t);

std::string boolToString (const bool& t);

std::string statChangesToString (const std::vector<StatChange>& t);
