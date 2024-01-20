//
// Created by manua on 04/12/2023.
//

#ifndef DOMINO_LINEARE_2D_GAMEMODE_H
#define DOMINO_LINEARE_2D_GAMEMODE_H

/**
 * @brief Structure representing a Domino piece.
 *
 * The `Piece` structure represents a Domino piece with two sides, each identified by an integer value.
 * The left_side and right_side members store the values of the respective sides of the Domino piece.
 *
 * @details The `left_side` and `right_side` members store the integer values of the left and right sides
 * of a Domino piece, respectively. These values represent the markings on each side of the piece.
 *
 * @note This structure is typically used in the context of a Domino game to represent individual pieces.
 * The values stored in `left_side` and `right_side` are integers representing the markings on each side.
 */
typedef struct piece Piece;
struct piece {
    int left_side;
    int right_side;
};

/**
 * @brief Calculates the score for a 2D array of Domino pieces.
 *
 * This function calculates the score for a 2D array of Domino pieces, where each element of the array
 * represents an individual piece with left and right sides. The scoring is based on the sum of the values
 * on each side of the pieces in the array.
 *
 * @param table A pointer to a 2D array of Domino pieces.
 *
 * @return The calculated score based on the values of the left and right sides of the Domino pieces.
 *
 * @details The function iterates through the 2D array of Domino pieces, skipping elements with both sides
 * set to -1. For each piece, it adds the values of the left and right sides to the total score. If one side
 * is -1, only the value of the non-negative side is added to the score. The final calculated score is returned.
 *
 * @note The caller is responsible for ensuring that the provided 2D array of pieces is valid and has appropriate
 * dimensions (20x20 in this case).
 */
int calculate_score_2D(Piece** table);

/**
 * @brief Assigns Domino pieces to a 1D array of pieces for a player.
 *
 * This function assigns Domino pieces to a 1D array of pieces representing a player.
 * The number of pieces assigned is specified by the parameter `n`. The assignment is
 * based on a predefined set of possible Domino pieces.
 *
 * @param player A pointer to a 1D array of pieces representing the player.
 * @param n The number of Domino pieces to assign to the player.
 *
 * @details The function uses a predefined set of possible Domino pieces, and for each
 * piece to be assigned, it selects a random number to determine which piece from the
 * set to assign to the player. The assigned pieces' values are stored in the `left_side`
 * and `right_side` members of the player's pieces array.
 *
 * @note The caller is responsible for ensuring that the provided player array has sufficient
 * space to store `n` Domino pieces, and the random selection of pieces may result in duplicates.
 */
void assign_pieces_2D(Piece* player, int n);

/**
 * @brief Finds the index of the first non-empty Domino piece in a 1D array.
 *
 * This function searches a 1D array of Domino pieces, representing a row or column,
 * to find the index of the first non-empty piece. The function considers a piece as
 * empty if both its left and right sides are set to -1.
 *
 * @param row A pointer to a 1D array of Domino pieces representing a row or column.
 * @param cols The number of columns in the array.
 *
 * @return The index of the first non-empty Domino piece, or -1 if all pieces are empty.
 *
 * @details The function iterates through the array and checks each piece. If a non-empty
 * piece is found, its index is returned. If no non-empty piece is found, the function returns -1.
 */
int first_piece_2D(Piece* row, int cols);

/**
 * @brief Finds the index of the last non-empty Domino piece in a 1D array.
 *
 * This function searches a 1D array of Domino pieces, representing a row or column,
 * to find the index of the last non-empty piece. The function considers a piece as
 * empty if both its left and right sides are set to -1.
 *
 * @param row A pointer to a 1D array of Domino pieces representing a row or column.
 * @param cols The number of columns in the array.
 *
 * @return The index of the last non-empty Domino piece, or -1 if all pieces are empty.
 *
 * @details The function iterates through the array in reverse order and checks each piece.
 * If a non-empty piece is found, its index is returned. If no non-empty piece is found,
 * the function returns -1.
 */
int last_piece_2d(Piece* row, int cols);

/**
 * @brief Creates a 1D array representing a player in a 2D Domino game.
 *
 * This function allocates memory for a 1D array of Domino pieces, each representing
 * a player's row or column in a 2D Domino game.
 *
 * @param n The number of pieces to allocate for the player.
 *
 * @return A pointer to the allocated array of Domino pieces.
 *
 * @details The function allocates memory for the specified number of Domino pieces
 * and returns a pointer to the first element of the array. If memory allocation fails,
 * the function prints a debug message and exits the program.
 */
Piece* create_player_2D(size_t n);

/**
 * @brief Checks if a player's 1D array of Domino pieces is empty.
 *
 * This function checks if all Domino pieces in a player's 1D array are empty.
 * A piece is considered empty if both its left and right sides are set to -1.
 *
 * @param player A pointer to a 1D array of Domino pieces representing a player.
 * @param n The number of pieces in the player's array.
 *
 * @return 1 if all pieces are empty, 0 if at least one piece is non-empty.
 *
 * @details The function iterates through the player's array and checks each piece.
 * If it finds at least one non-empty piece, it returns 0. If all pieces are empty, it
 * returns 1.
 */
int check_empty_player(Piece* player, int n);

/**
 * @brief Checks if a move is allowed in a 2D Domino game.
 *
 * This function checks whether a Domino piece can be legally placed on the table
 * in a 2D Domino game, considering the specified side (left or right).
 *
 * @param table_piece A pointer to the Domino piece on the table.
 * @param using_piece A pointer to the Domino piece to be placed on the table.
 * @param side The side on which the piece is to be placed (LEFT_SIDE or RIGHT_SIDE).
 *
 * @return MOVE_ALLOWED if the move is allowed, MOVE_NOT_ALLOWED otherwise.
 *
 * @details The function considers the orientation of the table piece (vertical or
 * horizontal) and checks if the using piece can be legally placed on the specified
 * side of the table piece. If the move is allowed, it returns MOVE_ALLOWED; otherwise,
 * it returns MOVE_NOT_ALLOWED.
 */
int check_move_2D(Piece* table_piece, Piece* piece, int side);

/**
 * @brief Picks a piece index from a player's collection of pieces.
 *
 * This function selects a specific index from a player's collection of Domino pieces
 * based on the provided index. The selected index represents the player's chosen piece
 * for a move.
 *
 * @param player A pointer to the array of Domino pieces representing the player's collection.
 * @param player_size The number of pieces in the player's collection.
 * @param pickedIndex The index representing the selected piece for the move.
 *
 * @return The index of the chosen piece in the player's collection, or -1 if not found.
 *
 * @details The function iterates through the player's pieces, excluding empty spaces,
 * and returns the index corresponding to the selected piece for the move. If the
 * selected index is not found, it returns -1.
 */
int pick_piece_index(Piece* player, int n, int pickedIndex);

/**
 * @brief Uses a Domino piece from the player to make a move on the 2D table.
 *
 * This function places a selected Domino piece from the player onto the 2D table
 * based on the specified orientation (horizontal or vertical) and side (left or right).
 *
 * @param table A pointer to the 2D array representing the Domino pieces on the table.
 * @param player A pointer to the array of Domino pieces representing the player's collection.
 * @param piece The index of the selected piece in the player's collection.
 * @param side The side on which to place the piece (LEFT_SIDE or RIGHT_SIDE).
 * @param player_size A pointer to the variable storing the size of the player's collection.
 * @param orientation The orientation of the piece placement (HORIZONTAL or VERTICAL).
 * @param row The row in which the piece is placed on the 2D table.
 *
 * @details The function checks the validity of the move based on the specified orientation,
 * side, and the adjacent pieces on the table. If the move is valid, it updates the table,
 * removes the used piece from the player's collection, and increments the row count if needed.
 * If the move is invalid, an error message is printed.
 */
void use_piece_2D(Piece** table, Piece* player, int piece, int side, int* player_size, int orientation, int row);

/**
 * @brief Removes a Domino piece from the player's collection.
 *
 * This function removes a Domino piece from the player's collection at the specified index.
 *
 * @param player A pointer to the array of Domino pieces representing the player's collection.
 * @param size A pointer to the variable storing the size of the player's collection.
 * @param index The index of the piece to be removed.
 *
 * @details The function shifts the elements in the player's collection to fill the gap
 * left by the removed piece, and decrements the size of the collection.
 * If the specified index is out of range, an error message is printed.
 */
void remove_piece_2D(Piece* player, int* size, int index);

/**
 * @brief Switches the values of a Domino piece in the player's collection.
 *
 * This function prompts the user to select a Domino piece from their collection
 * and switches the values of its left and right sides.
 *
 * @param player A pointer to the array of Domino pieces representing the player's collection.
 * @param player_size The size of the player's collection.
 *
 * @details The function prompts the user to enter the index of the piece they want to switch.
 * It then validates the input and switches the values of the selected piece.
 * If the input is invalid, an error message is printed.
 */
void switch_values_2D(Piece* player, int player_size);

/**
 * @brief Plays a single-player game of Dominoes on a 2D table.
 *
 * This function initiates a single-player game of Dominoes on a 2D table.
 * It prompts the player to make moves by placing pieces on the table horizontally or vertically.
 * The game continues until the player decides to quit or can't make any more moves.
 *
 * @param table A pointer to the 2D array representing the Domino table.
 * @param pieces A pointer to the variable storing the number of pieces in the player's collection.
 *
 * @details The function creates a player, assigns pieces, and starts the game loop.
 * In each iteration, it prints the player's pieces, prompts the player to choose a piece,
 * and allows them to make a move. The game continues until the player quits or can't make any more moves.
 * The table is printed after each move.
 */
void singleplayer_2D(Piece** matrix, int* player_size);

/**
 * @brief Creates a 2D matrix for representing a Domino table.
 *
 * This function dynamically allocates memory for a 2D array of Piece structures
 * to represent a Domino table. It initializes each element of the matrix to the
 * EMPTY_PIECE value.
 *
 * @return A pointer to the created 2D matrix.
 *
 * @details The function allocates memory for the rows and columns of the matrix
 * and initializes each element to the EMPTY_PIECE value, indicating an empty slot
 * on the Domino table.
 */
Piece** create_matrix();

/**
 * @brief Starts a game of (not) Linear Domino.
 *
 * This function initializes the game, allowing the player to choose the number
 * of pieces and the game mode (Singleplayer or CPU mode). It then starts the
 * selected game mode.
 *
 * @details The function creates a 2D matrix to represent the Domino table and
 * prompts the player to enter the number of pieces and the game mode. It handles
 * invalid inputs, such as non-numeric entries, by displaying an error message
 * and prompting the user again. After obtaining valid inputs, it starts the
 * selected game mode (Singleplayer or CPU mode).
 */
void not_linear_domino();

#endif //DOMINO_LINEARE_2D_GAMEMODE_H
