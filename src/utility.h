#ifndef OTHELLO_UTILITY_H
#define OTHELLO_UTILITY_H


#include <algorithm>
#include <type_traits>


template<typename Enum>
auto as_integer(Enum const value) {
    return static_cast<typename std::underlying_type<Enum>::type>(value);
}


#endif  // OTHELLO_UTILITY_H
