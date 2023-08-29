#pragma once

#include <utility>
#include "game_logic/Board.hpp"
#include <unordered_map>
#include <memory>

class TranspositionTable {
private:
    std::unordered_map<std::size_t, std::pair<int, int>> table;

public:
    std::unique_ptr<std::pair<int, int>> get(const Board &board);

    void set(const Board &board, int move, int value);

    [[nodiscard]] std::string to_string() const;
};