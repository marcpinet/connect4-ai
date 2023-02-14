#include "player/Player.hpp"

Player::Player(PlayerColor type) {
    this->type = type;
}

PlayerColor Player::get_type() const {
    return this->type;
}

int Player::get_move(const Board &board) {
    return 0;
}
