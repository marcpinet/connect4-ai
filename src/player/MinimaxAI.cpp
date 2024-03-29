#include "player/MinimaxAI.hpp"

int MinimaxAI::evaluate(const Board &board) {
    PlayerColor opponent = this->get_type() == PlayerColor::RED ? PlayerColor::YELLOW : PlayerColor::RED;
    int score = 0;
    int opponent_score = 0;

    if(board.get_winner() == this->get_type())
        return 100000000;
    else if(board.get_winner() == opponent)
        return -100000000;

    score = 1 * board.count_adjacent_discs(2, this->get_type());
    opponent_score = 3 * board.count_adjacent_discs(2, opponent);

    score += 3 * board.count_adjacent_discs(3, this->get_type());
    opponent_score += 10 * board.count_adjacent_discs(3, opponent);

    score += 10 * board.count_adjacent_discs(4, this->get_type());
    opponent_score += 1000 * board.count_adjacent_discs(4, opponent);

    return score - opponent_score;
}

std::pair<int, int>
MinimaxAI::compute(const Board &board, unsigned int depth, int player, int alpha, int beta) {
    // Checking inside the Transposition Table
    std::unique_ptr<std::pair<int, int>> cached_value = transposition_table.get(board);
    if(cached_value != nullptr)
        return *cached_value;

    std::pair<int, int> best;
    if(player == static_cast<int>(this->get_type()))
        best = std::make_pair(-1, std::numeric_limits<int>::min());
    else
        best = std::make_pair(-1, std::numeric_limits<int>::max());

    if(depth == 0 || board.is_terminal())
        return std::make_pair(-1, this->evaluate(board));

    std::vector<int> possible_moves = board.get_possible_moves();

    for(auto &move: possible_moves) {
        Board new_board = board;

        // Simulate the move (I say simulate because it's not actually played, it will be undone later...)
        new_board.place(move, static_cast<PlayerColor>(player));

        if(new_board.get_winner() == this->get_type()) {
            best = std::make_pair(move, std::numeric_limits<int>::max());
            return best;
        }

        // Recursively compute the best move
        std::pair<int, int> result = this->compute(new_board, depth - 1, -player, alpha, beta);

        // Undo the move
        new_board.remove(move);

        // Update the result
        result = std::make_pair(move, result.second);

        if(player == static_cast<int>(this->get_type())) {
            if(result.second > best.second)
                best = result;
            alpha = std::max(alpha, best.second);
            if(beta <= alpha)
                break;
        } else {
            if(result.second < best.second)
                best = result;
            beta = std::min(beta, best.second);
            if(beta <= alpha)
                break;
        }
    }
    transposition_table.set(board, best.first, best.second);

    return best;
}

int MinimaxAI::get_move(const Board &board) {
    if(board.is_terminal())
        return -1;

    return this->compute(board, MinimaxAI::DEFAULT_DEPTH, static_cast<int>(this->get_type())).first;
}
