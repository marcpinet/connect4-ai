#include "game_logic/Coord.hpp"

Coord::Coord(int x, int y) {
    this->x = x;
    this->y = y;
}

int Coord::get_x() const {
    return this->x;
}

int Coord::get_y() const {
    return this->y;
}