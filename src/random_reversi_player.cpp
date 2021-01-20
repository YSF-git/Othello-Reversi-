#include "./random_reversi_player.h"

#include <random>
#include <algorithm>
#include <iterator>


Square RandomReversiPlayer::think(const ReversiGame& game) {
    static std::random_device rd;
    static std::mt19937 g(rd());

    auto p_moves = game.GetPossibleMoves();
    std::shuffle(p_moves.begin(), p_moves.end(), g);
    return p_moves.front().first;
}
