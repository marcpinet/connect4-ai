#pragma once

#include <limits>
#include "AIPlayer.hpp"

class MinimaxAI : public AIPlayer {
private:
    static const unsigned int DEFAULT_DEPTH = 10;

    int evaluate(const Board &board);

    std::pair<int, int>
    compute(const Board &board, unsigned int depth, int player, int alpha = std::numeric_limits<int>::min(),
            int beta = std::numeric_limits<int>::max());


public:
    explicit MinimaxAI(PlayerColor type) : AIPlayer(type) {};

    int get_move(const Board &board) override;
};