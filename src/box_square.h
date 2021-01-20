#ifndef OTHELLO_BOX_SQUARE_H
#define OTHELLO_BOX_SQUARE_H


// typedef std::pair<int, int> Square;

typedef struct BoxSquare {
    unsigned int x, y;
} BoxSquare;

inline bool operator==(const BoxSquare &lhs, const BoxSquare &rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline bool operator!=(const BoxSquare &lhs, const BoxSquare &rhs) {
    return !(lhs == rhs);
}


#endif  // OTHELLO_BOX_SQUARE_H
