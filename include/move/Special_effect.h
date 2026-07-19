#pragma once

enum class SpecialEffect {
    None,
    Protect
};

class Pokemon;

bool protectConsecutiveChance (Pokemon& pokemon);
