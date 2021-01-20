#ifndef OTHELLO_STONE_H
#define OTHELLO_STONE_H


#include <array>
#include <string>
#include <iostream>

#include "./utility.h"


/**
 *  The enum Stone represents a field on the OthelloGame board, which can be black, white or empty.
 */
enum class Stone {
    empty, ///< stone empty
    black, ///< stone black
    white ///< stone white
};

/**
 *  Writes a textual representation of the given stone to the given stream.
 * \param o_stream   the output stream.
 * \param s     the stone to be written.
 * \return a reference to the used stream.
 */
inline std::ostream &operator<<(std::ostream &o_stream, const Stone &p) {
    static std::array<std::string, 3> piece_strings{{"_", "X", "O"}};
    return o_stream << piece_strings[as_integer(p)];
}

/**
 * Inverts the given Stone (only if it's not empty).
 * @param s the stone.
 * @return the inverted stone.
 */
inline Stone invert(const Stone s) {
    if (s == Stone::black)
        return Stone::white;
    if (s == Stone::white)
        return Stone::black;
    return Stone::empty;
}

/**
 * Inverts the given stone with the ! operator (only if it's not empty).
 * @param s the stone.
 * @return the inverted stone.
 */
inline Stone operator!(Stone s) {
    return invert(s);
}

#endif  // OTHELLO_STONE_H
