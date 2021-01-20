#ifndef OTHELLO_OTHELLO_GAME_H
#define OTHELLO_OTHELLO_GAME_H


#include <vector>
#include <utility>
#include <iostream>
#include <string>

#include "./stone.h"
#include "./box_square.h"

/**
 * OthelloGame class represents a fraction with a numerator and denominator.
 * It provides functionality to calculate with fractions, to compare fractions
 * and some additional helper functions.
 */
class OthelloGame {
 private:
    /** The board size. */
    const unsigned int uint_board_size;

    /** The number of moves. */
    unsigned int uint_nbr_of_moves;

    /** The board. */
    std::vector<Stone> board_vect_;

    /** All possible moves. */
    std::vector<std::pair<BoxSquare, std::vector<BoxSquare>>> all_possible_moves_;

    /** The active player. */
    Stone piece_active_player;

 public:
    /**
      * Initializes this OthelloGame instance with board size of 8.
      */
    OthelloGame() : OthelloGame(8) { }

    /**
      * Initializes this ReversiGame instance with the given board size
      * and white as starting player.
      * and has to be even.
      * \param size    the board size.
      * \throw out_of_range if the size is incorrect.
      */
    explicit OthelloGame(unsigned int size) : OthelloGame(size, Stone::white) { }

    /**
      * Initializes this ReversiGame instance
      * and the given starting player.
      * \param starting_player    the starting player.
      */
    explicit OthelloGame(Stone starting_player) : OthelloGame(8, starting_player) { }

    /**
      * Initializes this ReversiGame instance with the given board size
      * and the given starting player.
      * and has to be even.
      * \param size               the board size.
      * \param starting_player    the starting player.
      * \throw out_of_range if the size is incorrect.
      */
    OthelloGame(unsigned int size, Stone starting_player);

    /**
      * Initializes this ReversiGame instance with a given coded board,
      * the active player and the number of moves.
      * \param board            the string coded board.
      * \param active_player    the active player.
      * \param moves            the number of played moves.
      * \throw out_of_range if the size is incorrect.
      */
    OthelloGame(std::string board, Stone active_player, unsigned int MovesPlayed);


    OthelloGame(const OthelloGame& rg);

    /**
     * Displayes the board in the commandline mostly for debuging purposes.
     */
    void display_board() const;

    /**
     * Returns the board size of this ReversiGame instance.
     * \return  the board size.
     */
    unsigned int BoardSize() const {
        return uint_board_size;
    }

    /**
     * Returns a string representing the board of this ReversiGame instance.
     * \return  the string representation.
     */
    std::string BoardToString() const;

    /**
     * Returns the current score of this ReversiGame instance as a pair.
     * The stone count for black is first in the pair, white second.
     * \return  the score.
     */
    std::pair<unsigned int, unsigned int> GetCurrentScore() const;

    /**
     * Returns the Piece (black, white, empty) for a given Square.
     * \return  the piece.
     */
    Stone GetSquarePiece(BoxSquare s) const;

    /**
     * Returns all possible moves as a vector.
     * \return  all possible moves.
     */
    auto GetPossibleMoves() const { return all_possible_moves_; }

    /**
     * Checks whether a move on the given Square is possible.
     * \return  true, if it would be a valid move; otherwise false.
     */
    bool CheckValidMove(BoxSquare s) const;

    /**
     * Makes a move for the current player on the given Square. Also calls functions
     * to flip all stones and to update the possible moves.
     */
    void MakePlayerMove(BoxSquare s);

    /**
     * Checks if there still are possible moves to be played.
     * \return  true, if there are still moves; otherwise false.
     */
    bool CheckForPossibleMoves() const { return !all_possible_moves_.empty(); }

    /**
     * Returns the Piece of the active player (white or black).
     * \return  the active player.
     */
    Stone ReturnActivePlayerPiece() const { return piece_active_player; }

    /**
     * Returns the number of moves that have already been played.
     * \return  the number of moves.
     */
    unsigned int MovesPlayed() const { return uint_nbr_of_moves; }

 private:
    /**
      * Returns the Piece for the given x and y coordinate.
      * \return the Pice.
      * \throw out_of_range if the coordinates are incorrect.
      */
    Stone GetSquarePiece(unsigned int x, unsigned int y) const;

    /**
      * Sets the given Piece on the board for the given x and y coordinate.
      * \throw out_of_range if the coordinates are incorrect.
      */
    void SetBoardPiece(unsigned int x, unsigned int y, Stone p);

    /**
      * Sets the given Piece on the board for the given Square.
      * \throw out_of_range if the coordinates are incorrect.
      */
    void SetBoardPiece(BoxSquare s, Stone p);

    /**
     * Updates the list of all possible moves.
     */
    void UpdatePossibleMoves();

    /**
     * Checks all eight directions for possible flips for the given Square.
     * \param s     the square.
     */
    void CheckPossibleFlipDirections(BoxSquare s);

    /**
     * Flips all pieces between the given start and end Square.
     * \param start  the starting point.
     * \param end    the end point.
     */
    void FlipPieces(BoxSquare start, BoxSquare end);
};


#endif  // OTHELLO_HIGH_SCORE_WINDOW_H
