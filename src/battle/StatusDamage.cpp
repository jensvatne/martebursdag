#include "battle/StatusDamage.h"
#include "pokemon/Pokemon.h"

int poisonDamage(int maxHP) {
    return maxHP * 0.125;
}

int burnDamage(int maxHP) {
    return maxHP * 0.125;
}

int toxicDamage(int maxHP, int toxicCounter) {
    return maxHP * (1 + toxicCounter) / 16;
}
