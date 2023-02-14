#pragma once

#include "game_logic/Board.hpp"

class Player {
private:
    PlayerColor type;

public:
    explicit Player(PlayerColor type);

    [[nodiscard]] PlayerColor get_type() const;

    virtual int get_move(const Board &board);

    virtual ~Player() = default;
};
