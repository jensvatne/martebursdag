#include "pokemon/Pokemon_loader.h"
#include "move/Move_loader.h"
#include "battle/Simulator.h"
#include <iostream>
#include <limits>
#include <random>
#include <string>

namespace {

int promptInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number between " << min << " and " << max << ".\n";
    }
}

void printMoveset(const Pokemon& pokemon) {
    const std::vector<Move>& moves = pokemon.getMoves();
    for (int i = 0; i < static_cast<int>(moves.size()); i++) {
        std::cout << "  [" << i << "] " << moves[i].getName()
                   << " (PP " << moves[i].getCurrPP() << "/" << moves[i].getMaxPP() << ")\n";
    }
}

int pickMoveIndex(Simulator& sim, Pokemon& pokemon) {
    while (true) {
        std::cout << pokemon.getName() << "'s moves:\n";
        printMoveset(pokemon);
        int index = promptInt("Choose a move index: ", 0, static_cast<int>(pokemon.getMoves().size()) - 1);
        if (sim.isValidMoveCheck(pokemon, index)) {
            return index;
        }
    }
}

} // namespace

int main() {
    std::vector<Pokemon> dex = loadPokemon();
    std::vector<Move> movepool = loadMoves();

    std::cout << "=== Choose your Pokemon ===\n";
    for (int i = 0; i < static_cast<int>(dex.size()); i++) {
        std::cout << "[" << i << "] " << dex[i].getName() << "\n";
    }

    int playerChoice = promptInt("\n> ", 0, static_cast<int>(dex.size()) - 1);

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<int> dexDistrib(0, static_cast<int>(dex.size()) - 1);
    int opponentChoice;
    do {
        opponentChoice = dexDistrib(rng);
    } while (opponentChoice == playerChoice);

    Pokemon player = dex[playerChoice];
    Pokemon opponent = dex[opponentChoice];

    // Both sides get the same fixed movepool (in addition to Struggle, added by loadPokemon)
    // so damage/type interactions are visible without building a full move-select UI.
    const std::vector<std::string> presetMoves = {"Tackle", "Flamethrower", "Thunderbolt", "Shadow Ball"};
    for (const Move& move : movepool) {
        for (const std::string& name : presetMoves) {
            if (move.getName() == name) {
                player.addMove(move);
                opponent.addMove(move);
            }
        }
    }

    std::cout << "\nA wild " << opponent.getName() << " appears! Go, " << player.getName() << "!\n";

    Simulator sim(player, opponent);
    std::uniform_int_distribution<int> opponentMoveDistrib(0, static_cast<int>(opponent.getMoves().size()) - 1);

    while (!player.hasFainted() && !opponent.hasFainted()) {
        std::cout << "\n----------------------------------------\n";
        std::cout << player.getName() << " HP: " << player.getCurrHP()
                   << "  |  " << opponent.getName() << " HP: " << opponent.getCurrHP() << "\n";

        int playerMove = pickMoveIndex(sim, player);

        int opponentMove;
        do {
            opponentMove = opponentMoveDistrib(rng);
        } while (!sim.isValidMoveCheck(opponent, opponentMove));

        sim.runTurn(playerMove, opponentMove);
    }

    std::cout << "\n========================================\n";
    std::cout << (player.hasFainted() ? opponent.getName() : player.getName()) << " wins!\n";

    return 0;
}
