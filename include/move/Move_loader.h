#pragma once
#include <string>
#include "misc/Type.h"
#include "move/Category_moves.h"
#include "move/Special_effect.h"
#include "move/Stat_change.h"
#include "misc/Status.h"
#include "move/Move.h"

Type stringToType(const std::string& s);

Category stringToCategory(const std::string& s);

SpecialEffect stringToSpecialEffect(const std::string& s);

StatChange stringToStatChange(const std::string& s);

Status stringToStatus(const std::string& s);

bool stringToBool(const std::string& s);

std::vector<StatChange> stringToStatChanges(const std::string& s);

std::vector<Move> loadMoves();
