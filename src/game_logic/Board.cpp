#include "game_logic/Board.hpp"
#include <iostream>
#include <algorithm>

Board::Board() {
    this->repr = std::array<std::array<PlayerColor, 7>, 6>();
    for(int x = 0; x < Board::height; x++) {
        for(int y = 0; y < Board::width; y++)
            this->repr[x][y] = PlayerColor::NONE;
    }
}

const std::array<std::array<PlayerColor, 7>, 6> &Board::get_repr() const {
    return this->repr;
}

PlayerColor Board::get(Coord coord) const {
    return this->repr.at(coord.get_x()).at(coord.get_y());
}

void Board::place(int column, PlayerColor value) {
    if(column >= 0 && column < Board::width) {
        for(int x = Board::height - 1; x >= 0; x--) {
            if(this->repr.at(x).at(column) == PlayerColor::NONE) {
                this->repr.at(x).at(column) = value;
                break;
            }
        }
    }
}

int Board::get_height() {
    return Board::height;
}

int Board::get_width() {
    return Board::width;
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    for(int x = 0; x < Board::height; x++) {
        for(int y = 0; y < Board::width; y++) {
            switch(board.repr.at(x).at(y)) {
                case PlayerColor::NONE:
                    os << " - ";
                    break;
                case PlayerColor::RED:
                    os << " X ";
                    break;
                case PlayerColor::YELLOW:
                    os << " O ";
                    break;
            }
        }
        os << std::endl;
    }
    return os;
}

void Board::print() const {
    std::cout << *this << std::endl;
}

PlayerColor Board::get_winner() const {
    // Checking rows
    for(int x = 0; x < Board::height; x++) {
        for(int y = 0; y < Board::width - 3; y++) {
            if(this->repr.at(x).at(y) != PlayerColor::NONE &&
               this->repr.at(x).at(y) == this->repr.at(x).at(y + 1) &&
               this->repr.at(x).at(y) == this->repr.at(x).at(y + 2) &&
               this->repr.at(x).at(y) == this->repr.at(x).at(y + 3))
                return this->repr.at(x).at(y);
        }
    }

    // Checking columns
    for(int x = 0; x < Board::height - 3; x++) {
        for(int y = 0; y < Board::width; y++) {
            if(this->repr.at(x).at(y) != PlayerColor::NONE &&
               this->repr.at(x).at(y) == this->repr.at(x + 1).at(y) &&
               this->repr.at(x).at(y) == this->repr.at(x + 2).at(y) &&
               this->repr.at(x).at(y) == this->repr.at(x + 3).at(y))
                return this->repr.at(x).at(y);
        }
    }

    // Checking diagonal 1
    for(int x = 0; x < Board::height - 3; x++) {
        for(int y = 0; y < Board::width - 3; y++) {
            if(this->repr.at(x).at(y) != PlayerColor::NONE &&
               this->repr.at(x).at(y) == this->repr.at(x + 1).at(y + 1) &&
               this->repr.at(x).at(y) == this->repr.at(x + 2).at(y + 2) &&
               this->repr.at(x).at(y) == this->repr.at(x + 3).at(y + 3))
                return this->repr.at(x).at(y);
        }
    }

    // Checking diagonal 2
    for(int x = 0; x < Board::height - 3; x++) {
        for(int y = 3; y < Board::width; y++) {
            if(this->repr.at(x).at(y) != PlayerColor::NONE &&
               this->repr.at(x).at(y) == this->repr.at(x + 1).at(y - 1) &&
               this->repr.at(x).at(y) == this->repr.at(x + 2).at(y - 2) &&
               this->repr.at(x).at(y) == this->repr.at(x + 3).at(y - 3))
                return this->repr.at(x).at(y);
        }
    }

    return PlayerColor::NONE;
}

bool Board::is_terminal() const {
    return this->get_winner() != PlayerColor::NONE || this->get_possible_moves().empty();
}

std::vector<int> Board::get_possible_moves() const {
    //std::vector<int> moves;
    //for(int i = 0; i < Board::width; i++) {
    //    if(this->repr.at(0).at(i) == PlayerColor::NONE)
    //        moves.push_back(i);
    //}
    //return moves;

    // Order by CAN WIN for each player
    std::vector<int> moves;
    for(int i = 0; i < Board::width; i++) {
        if(this->repr.at(0).at(i) == PlayerColor::NONE) {
            Board copy = *this;
            copy.place(i, PlayerColor::RED);
            if(copy.get_winner() == PlayerColor::RED) {
                moves.insert(moves.begin(), i);
            } else {
                copy = *this;
                copy.place(i, PlayerColor::YELLOW);
                if(copy.get_winner() == PlayerColor::YELLOW) {
                    moves.insert(moves.begin(), i);
                } else {
                    moves.push_back(i);
                }
            }
            copy.remove(i);
        }
    }
    return moves;
}

void Board::remove(int column) {
    if(column >= 0 && column < Board::width) {
        for(int x = 0; x < Board::height; x++) {
            if(this->repr.at(x).at(column) != PlayerColor::NONE) {
                this->repr.at(x).at(column) = PlayerColor::NONE;
                break;
            }
        }
    }
}

int Board::count_adjacent_discs(int nb_adjacent_pieces, PlayerColor color) const {
    int count = 0;
    // Checking rows
    for(int x = 0; x < Board::height; x++) {
        for(int y = 0; y < Board::width - nb_adjacent_pieces + 1; y++) {
            bool found = true;
            for(int i = 0; i < nb_adjacent_pieces; i++) {
                if(this->repr.at(x).at(y + i) != color) {
                    found = false;
                    break;
                }
            }
            if(found)
                count++;
        }
    }

    // Checking columns
    for(int x = 0; x < Board::height - nb_adjacent_pieces + 1; x++) {
        for(int y = 0; y < Board::width; y++) {
            bool found = true;
            for(int i = 0; i < nb_adjacent_pieces; i++) {
                if(this->repr.at(x + i).at(y) != color) {
                    found = false;
                    break;
                }
            }
            if(found)
                count++;
        }
    }

    // Checking diagonal 1
    for(int x = 0; x < Board::height - nb_adjacent_pieces + 1; x++) {
        for(int y = 0; y < Board::width - nb_adjacent_pieces + 1; y++) {
            bool found = true;
            for(int i = 0; i < nb_adjacent_pieces; i++) {
                if(this->repr.at(x + i).at(y + i) != color) {
                    found = false;
                    break;
                }
            }
            if(found)
                count++;
        }
    }

    // Checking diagonal 2
    for(int x = 0; x < Board::height - nb_adjacent_pieces + 1; x++) {
        for(int y = nb_adjacent_pieces - 1; y < Board::width; y++) {
            bool found = true;
            for(int i = 0; i < nb_adjacent_pieces; i++) {
                if(this->repr.at(x + i).at(y - i) != color) {
                    found = false;
                    break;
                }
            }
            if(found)
                count++;
        }
    }

    return count;
}

std::unique_ptr<Board> Board::clone() const {
    auto newBoard = std::make_unique<Board>();
    for(unsigned int i = 0; i < height; ++i) {
        for(unsigned int j = 0; j < width; ++j) {
            newBoard->repr[i][j] = repr[i][j];
        }
    }
    return newBoard;
}

bool Board::can_place(int column) const {
    return column >= 0 && column < Board::width && this->repr.at(0).at(column) == PlayerColor::NONE;
}
