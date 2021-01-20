#ifndef OTHELLO_DIRECTION_H
#define OTHELLO_DIRECTION_H


#include <array>
#include <string>
#include <iostream>

#include "./utility.h"
#include "./box_square.h"


enum class Direction { up, up_left, up_right, down, down_right, down_left, left, right };

inline std::ostream &operator<<(std::ostream &o_stream, const Direction &dir) {
    static std::array<std::string, 8> direction_strings{
            "UP", "UPLEFT", "UPRIGHT",
            "DOWN", "DOWNRIGHT", "DOWNLEFT",
            "LEFT", "RIGHT"
    };
    return o_stream << direction_strings[as_integer(dir)];
}

inline Direction determine(const BoxSquare start, const BoxSquare end) {
    int dx = start.x - end.x;
    int dy = start.y - end.y;

    if (dx == 0) {
        return dy < 0 ? Direction::up : Direction::down;
    } else if (dy == 0) {
        return dx < 0 ? Direction::right : Direction::left;
    } else if (dx < 0) {
        return dy < 0 ? Direction::up_right : Direction::down_right;
    } else {
        return dy < 0 ? Direction::up_left : Direction::down_left;
    }
}


#endif  // OTHELLO_DIRECTION_H
