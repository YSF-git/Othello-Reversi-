#ifndef REVERSI_INTERFACE_REVERSI_PLAYER_H
#define REVERSI_INTERFACE_REVERSI_PLAYER_H


#include "./square.h"
#include "./OthelloGame.h"

class IReversiPlayer {
 public:
    virtual Square think(const OthelloGame& game) = 0;
    virtual ~IReversiPlayer() {}
};

#endif  // REVERSI_INTERFACE_REVERSI_PLAYER_H
