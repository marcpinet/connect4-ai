#include "player/MinimaxAI.hpp"

int MinimaxAI::evaluate(const Board &board) {
    int player = static_cast<int>(this->get_type());
    int winner = static_cast<int>(board.get_winner());

    return winner == player ? 1 : winner == -player ? -1 : 0;
}

std::pair<int, int>
MinimaxAI::compute(const Board &board, unsigned int depth, int player, int alpha, int beta) {
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
    return best;
}

int MinimaxAI::get_move(const Board &board) {
    int depth = static_cast<int>(board.get_possible_moves().size());
    if(depth == 0 || board.is_terminal())
        return -1;

    if(depth == MinimaxAI::DEFAULT_DEPTH)
        // Getting random move as a first move
        return board.get_possible_moves()[rand() % board.get_possible_moves().size()];

    else
        return this->compute(board, depth, static_cast<int>(this->get_type()), std::numeric_limits<int>::min(),
                             std::numeric_limits<int>::max()).first;
}
