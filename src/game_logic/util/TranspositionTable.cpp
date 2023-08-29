#include "game_logic/util/TranspositionTable.hpp"

std::unique_ptr<std::pair<int, int>> TranspositionTable::get(const Board &board) {
    auto it = table.find(board.hash());
    if(it != table.end()) {
        return std::make_unique<std::pair<int, int>>(it->second);
    }
    return nullptr;
}

void TranspositionTable::set(const Board &board, int move, int value) {
    table[board.hash()] = std::make_pair(move, value);
}

[[nodiscard]] std::string TranspositionTable::to_string() const {
    return "TranspositionTable(size=" + std::to_string(table.size()) + ")";
}