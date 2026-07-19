#include "pokemon/Stats.h"

double stageToMultiplier (int stage) {
    int positiveStage = 0;
    int negativeStage = 0;

    if (stage > 0) positiveStage = stage;
    if (stage < 0) negativeStage = stage;

    double numerator = 2.0 + static_cast<double>(positiveStage);
    double denominator = 2.0 - static_cast<double>(negativeStage);

    return numerator/denominator;
}
