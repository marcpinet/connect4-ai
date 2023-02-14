#pragma once

#include "AIPlayer.hpp"

class MinimaxAI : public AIPlayer {
private:
    static const unsigned int DEFAULT_DEPTH = 42;

    int evaluate(const Board &board);

    std::pair<int, int>
    compute(const Board &board, unsigned int depth, int player, int alpha = INT_MIN, int beta = INT_MAX);


public:
    explicit MinimaxAI(PlayerColor type) : AIPlayer(type) {};

    int get_move(const Board &board) override;
};