#include <iostream>
#include <memory>
#include "render/Engine.hpp"
#include "player/HumanPlayer.hpp"
#include "player/MinimaxAI.hpp"
#include <time.h>

int main() {
    srand(time(nullptr));
    std::unique_ptr<Player> player1 = std::make_unique<HumanPlayer>(PlayerColor::RED);
    std::unique_ptr<Player> player2 = std::make_unique<MinimaxAI>(PlayerColor::YELLOW);
    Engine engine(std::move(player1), std::move(player2));
    engine.run();

    return EXIT_SUCCESS;
}
