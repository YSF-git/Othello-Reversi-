#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <string>

#include "./OthelloGame.h"
#include "./utility.h"


OthelloGame::OthelloGame(const OthelloGame &rg) :
        board_vect_(rg.board_vect_),
        all_possible_moves_(rg.all_possible_moves_),
        uint_board_size(rg.uint_board_size),
        uint_nbr_of_moves(rg.uint_nbr_of_moves),
        piece_active_player(rg.piece_active_player) {}


OthelloGame::OthelloGame(unsigned int size, Stone starting_player)
        : uint_board_size(size), board_vect_(size * size), uint_nbr_of_moves(0) {
    if (size < 4 || size > 16 || size % 2 == 1)
        throw std::out_of_range{"ReversiGame(int)"};

    SetBoardPiece(uint_board_size / 2, uint_board_size / 2, Stone::black);
    SetBoardPiece(uint_board_size / 2 - 1, uint_board_size / 2 - 1, Stone::black);
    SetBoardPiece(uint_board_size / 2 - 1, uint_board_size / 2, Stone::white);
    SetBoardPiece(uint_board_size / 2, uint_board_size / 2 - 1, Stone::white);

    piece_active_player = starting_player;
    UpdatePossibleMoves();
}

OthelloGame::OthelloGame(std::string board, Stone active_player, unsigned int moves)
        : OthelloGame(static_cast<unsigned int>(sqrt(board.size())), active_player) {
    uint_nbr_of_moves = moves;

    for (unsigned int i = 0; i < board.size(); ++i) {
        if (board[i] == '1') {
            SetBoardPiece({i % uint_board_size, i / uint_board_size}, Stone::black);
        } else if (board[i] == '2') {
            SetBoardPiece({i % uint_board_size, i / uint_board_size}, Stone::white);
        }
    }
    UpdatePossibleMoves();
}


void OthelloGame::display_board() const {
    for (unsigned int y = uint_board_size; y-- > 0; ) {
        std::cout << y;
        for (unsigned int x = 0; x < uint_board_size; ++x) {
            std::cout << " " << GetSquarePiece(x, y);
        }
        std::cout << std::endl;
    }
    std::cout << " ";
    for (int x = 0; x < uint_board_size; ++x) {
        std::cout << " " << x;
    }
    std::cout << std::endl;
}

Stone OthelloGame::GetSquarePiece(unsigned int x, unsigned int y) const {
    if (x >= uint_board_size || y >= uint_board_size)
        throw std::out_of_range{"get_piece(int, int)"};
    return board_vect_.at(x + y * uint_board_size);
}

Stone OthelloGame::GetSquarePiece(BoxSquare s) const {
    return GetSquarePiece(s.x, s.y);
}

void OthelloGame::SetBoardPiece(BoxSquare s, Stone p) {
    SetBoardPiece(s.x, s.y, p);
}

void OthelloGame::SetBoardPiece(unsigned int x, unsigned int y, Stone p) {
    if (x >= uint_board_size || y >= uint_board_size)
        throw std::out_of_range{"set_piece(int, int, Piece)"};
    board_vect_[x + y * uint_board_size] = p;
}

void OthelloGame::UpdatePossibleMoves() {
    all_possible_moves_.clear();

    for (unsigned int x = 0; x < uint_board_size; ++x) {
        for (unsigned int y = 0; y < uint_board_size; ++y) {
            if (GetSquarePiece(x, y) != Stone::empty) continue;
            CheckPossibleFlipDirections({x, y});
        }
    }
}

void OthelloGame::CheckPossibleFlipDirections(BoxSquare s) {
    std::vector<BoxSquare> destinations;

    // up check
    if ((s.y < (uint_board_size - 2)) && GetSquarePiece(s.x, s.y + 1) == invert(piece_active_player)) {
        for (unsigned int i = s.y + 2; i < uint_board_size; ++i) {
            if (GetSquarePiece(s.x, i) == Stone::empty) break;
            if (GetSquarePiece(s.x, i) == piece_active_player) {
                destinations.push_back({s.x, i});
                break;
            }
        }
    }

    // down check
    if ((s.y > 1) && GetSquarePiece(s.x, s.y - 1) == invert(piece_active_player)) {
        for (unsigned int i = s.y - 1; i-- > 0; ) {
            if (GetSquarePiece(s.x, i) == Stone::empty) break;
            if (GetSquarePiece(s.x, i) == piece_active_player) {
                destinations.push_back({s.x, i});
                break;
            }
        }
    }

    // right check
    if ((s.x < (uint_board_size - 2)) && GetSquarePiece(s.x + 1, s.y) == invert(piece_active_player)) {
        for (unsigned int i = s.x + 2; i < uint_board_size; ++i) {
            if (GetSquarePiece(i, s.y) == Stone::empty) break;
            if (GetSquarePiece(i, s.y) == piece_active_player) {
                destinations.push_back({i, s.y});
                break;
            }
        }
    }

    // left check
    if ((s.x > 1) && GetSquarePiece(s.x - 1, s.y) == invert(piece_active_player)) {
        for (unsigned int i = s.x - 1; i-- > 0; ) {
            if (GetSquarePiece(i, s.y) == Stone::empty) break;
            if (GetSquarePiece(i, s.y) == piece_active_player) {
                destinations.push_back({i, s.y});
                break;
            }
        }
    }

    // up-right check
    if ((s.y < (uint_board_size - 2)) && (s.x < (uint_board_size - 2))
        && GetSquarePiece(s.x + 1, s.y + 1) == invert(piece_active_player)) {
        for (unsigned int i = 2; ((s.x + i) < uint_board_size) && ((s.y + i) < uint_board_size); i++) {
            if (GetSquarePiece(s.x + i, s.y + i) == Stone::empty) break;
            if (GetSquarePiece(s.x + i, s.y + i) == piece_active_player) {
                destinations.push_back({s.x + i, s.y + i});
                break;
            }
        }
    }

    // down-right check
    if ((s.y > 1) && (s.x < (uint_board_size - 2)) && GetSquarePiece(s.x + 1, s.y - 1) == invert(piece_active_player)) {
        for (unsigned int i = 2; (s.x + i < uint_board_size) && ((s.y - i + 1) > 0); i++) {
            if (GetSquarePiece(s.x + i, s.y - i) == Stone::empty) break;
            if (GetSquarePiece(s.x + i, s.y - i) == piece_active_player) {
                destinations.push_back({s.x + i, s.y - i});
                break;
            }
        }
    }

    // down-left check
    if ((s.y > 1) && (s.x > 1) && GetSquarePiece(s.x - 1, s.y - 1) == invert(piece_active_player)) {
        for (unsigned int i = 2; ((s.x - i + 1) > 0) && ((s.y - i + 1) > 0); i++) {
            if (GetSquarePiece(s.x - i, s.y - i) == Stone::empty) break;
            if (GetSquarePiece(s.x - i, s.y - i) == piece_active_player) {
                destinations.push_back({s.x - i, s.y - i});
                break;
            }
        }
    }

    // up-left check
    if ((s.y < (uint_board_size - 2)) && (s.x > 1) && GetSquarePiece(s.x - 1, s.y + 1) == invert(piece_active_player)) {
        for (unsigned int i = 2; ((s.x - i + 1) > 0) && ((s.y + i) < uint_board_size); i++) {
            if (GetSquarePiece(s.x - i, s.y + i) == Stone::empty) break;
            if (GetSquarePiece(s.x - i, s.y + i) == piece_active_player) {
                destinations.push_back({s.x - i, s.y + i});
                break;
            }
        }
    }

    if (!destinations.empty())
        all_possible_moves_.push_back({s, destinations});
}

void OthelloGame::MakePlayerMove(BoxSquare s) {
    auto moves = std::find_if(std::begin(all_possible_moves_), std::end(all_possible_moves_),
                               [&s](const auto &item) { return item.first == s; });
    if (moves != std::end(all_possible_moves_)) {
        SetBoardPiece(s, piece_active_player);
        for (auto end : (*moves).second) {
            FlipPieces((*moves).first, end);
        }
        piece_active_player = invert(piece_active_player);
        ++uint_nbr_of_moves;
        UpdatePossibleMoves();
    }
}

bool OthelloGame::CheckValidMove(BoxSquare s) const {
    return std::find_if(
            std::begin(all_possible_moves_),
            std::end(all_possible_moves_),
            [&s](const auto &item) { return item.first == s; }) != std::end(all_possible_moves_);
}

void OthelloGame::FlipPieces(BoxSquare start, BoxSquare end) {
    while (start != end) {
        if (start.x > end.x) start.x--;
        else if (start.x < end.x) start.x++;
        if (start.y > end.y) start.y--;
        else if (start.y < end.y) start.y++;
        SetBoardPiece(start, piece_active_player);
    }
}

std::pair<unsigned int, unsigned int> OthelloGame::GetCurrentScore() const {
    std::pair<unsigned int, unsigned int> score{0, 0};
    for (Stone p : board_vect_) {
        if (p == Stone::white)
            ++score.first;
        else if (p == Stone::black)
            ++score.second;
    }
    return score;
}

std::string OthelloGame::BoardToString() const {
    std::string board(uint_board_size * uint_board_size, '0');
    for (int i = 0; i < board_vect_.size(); ++i) {
        if (board_vect_[i] == Stone::white)
            board[i] = '2';
        else if (board_vect_[i] == Stone::black)
            board[i] = '1';
    }
    return board;
}
