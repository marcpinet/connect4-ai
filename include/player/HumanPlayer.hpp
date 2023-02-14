#pragma once

#include "Player.hpp"

class HumanPlayer : public Player {
public:
    explicit HumanPlayer(PlayerColor type) : Player(type) {};
};