#pragma once

#include "player/PlayerColor.hpp"
#include "Coord.hpp"
#include <array>
#include <vector>

class Board {
private:
    static const unsigned int width = 7;
    static const unsigned int height = 6;
    std::array<std::array<PlayerColor, width>, height> repr{};

public:
    Board();

    friend std::ostream &operator<<(std::ostream &, const Board &);

    void print() const;

    [[nodiscard]] const std::array<std::array<PlayerColor, 7>, 6> &get_repr() const;

    [[nodiscard]] PlayerColor get(Coord) const;

    void place(int column, PlayerColor value);

    void remove(int column);

    [[nodiscard]] std::vector<int> get_possible_moves() const;

    [[nodiscard]] static int get_height();

    [[nodiscard]] static int get_width();

    [[nodiscard]] PlayerColor get_winner() const;

    [[nodiscard]] bool is_terminal() const;
};