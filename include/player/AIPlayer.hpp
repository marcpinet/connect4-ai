#pragma once

#include "Player.hpp"

class AIPlayer : public Player {
public:
    explicit AIPlayer(PlayerColor type) : Player(type) {};

    int get_move(const Board &) override = 0;
};