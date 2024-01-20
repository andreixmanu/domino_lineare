//
// Created by manua on 22/12/2023.
//

#ifndef DOMINO_LINEARE_2D_AUTOCOMPLETE_H
#define DOMINO_LINEARE_2D_AUTOCOMPLETE_H

/**
 * @brief Picks the index of a non-empty piece in the player's collection.
 *
 * This function iterates through the player's collection and returns the index
 * of the non-empty piece at the specified position (pickedIndex). It skips
 * over empty pieces until it reaches the specified position.
 *
 * @param player The player's collection of pieces.
 * @param player_size The size of the player's collection.
 * @param pickedIndex The position of the desired non-empty piece (0-based).
 * @return The index of the non-empty piece at the specified position,
 *         or -1 if no such piece is found.
 */
int pick_piece_index_autocomplete(Piece *player, int player_size, int pickedIndex);

/**
 * @brief Automatically switches the values of a piece in the player's collection.
 *
 * This function automatically switches the left and right values of a piece
 * in the player's collection. The piece to be switched is determined by the
 * specified position (n), assuming a 1-based index. If no non-empty piece is
 * found at the specified position, the function does nothing.
 *
 * @param player The player's collection of pieces.
 * @param player_size The size of the player's collection.
 * @param n The position (1-based) of the piece to switch values.
 */
void auto_switch_values_2D(Piece* player, int player_size, int n);

/**
 * @brief Removes a piece from the player's collection at the specified index.
 *
 * This function removes a piece from the player's collection at the specified
 * index. If the index is out of bounds, the function adjusts it to the nearest
 * valid index. If the specified index is negative or greater than or equal to
 * the size of the player's collection, the function does nothing.
 *
 * @param player The player's collection of pieces.
 * @param size The size of the player's collection (modified by the function).
 * @param index The index of the piece to remove (0-based).
 * @return 1 if successful, 0 if the index is out of bounds.
 */
int remove_piece_autocomplete(Piece *player, int *size, int index);

/**
 * @brief Places a piece on the table in the specified orientation and side.
 *
 * This function attempts to place a piece on the table in the specified
 * orientation (horizontal) and side (left or right). It checks the validity of
 * the move based on the adjacent piece on the table. If the move is valid, the
 * piece is placed on the table, and the function returns PIECE_PLACED. If the
 * move is not valid or there is no adjacent piece on the specified side, the
 * function returns PIECE_NOT_PLACED.
 *
 * @param table The 2D array representing the game table.
 * @param piece The piece to be placed on the table.
 * @param side The side on which to place the piece (LEFT_SIDE or RIGHT_SIDE).
 * @return PIECE_PLACED if the piece is successfully placed, PIECE_NOT_PLACED
 * otherwise.
 */
int use_piece_autocomplete(Piece **table, Piece piece, int side);

/**
 * @brief AI player strategy to play pieces on the table using the first-fit strategy.
 *
 * This function implements an AI player strategy to play pieces on the table
 * using the first-fit strategy. The AI player iterates through its pieces and
 * attempts to place them on the table. It randomly chooses between LEFT_SIDE
 * and RIGHT_SIDE, then searches for the first available position on the table
 * in the chosen direction. If a position is found, it places the piece on the
 * table and removes it from the player's pieces.
 *
 * After attempting to place pieces in both directions, the function switches
 * the values of each piece and repeats the process. This continues until all
 * pieces are placed on the table or no valid moves are left.
 *
 * @param table The 2D array representing the game table.
 * @param player The array of pieces belonging to the AI player.
 * @param player_size The size of the AI player's pieces array.
 */
void ai_first_fit(Piece** table, Piece* player, int* player_size);

/**
 * @brief Attempt to place player's pieces on the table using a special strategy.
 *
 * This function attempts to place the player's pieces on the table using a special
 * strategy. It checks if any of the player's pieces have a side matching the right
 * side of the last piece on the table. If a match is found, it places the piece on
 * the table to the right of the last piece. Similarly, it checks if any piece has a
 * side matching the left side of the first piece on the table. If a match is found,
 * it places the piece on the table to the left of the first piece.
 *
 * This function aims to optimize the placement of pieces based on their sides to
 * fill gaps on the table.
 *
 * @param table The 2D array representing the game table.
 * @param player The array of pieces belonging to the player.
 * @param pieces The size of the player's pieces array.
 */
void ultimate_try(Piece** table, Piece* player, int* pieces);

/**
 * @brief Automatically completes the game table with player's pieces using AI strategies.
 *
 * This function automatically completes the game table with pieces from the player using
 * AI strategies. It creates a player, assigns pieces, randomly selects the first piece
 * to place on the table, and then uses AI strategies to iteratively place pieces on the
 * table. The main AI strategy is the 'ai_first_fit' function. After the AI placement,
 * the function checks if the player's pieces can still be placed optimally using the
 * 'ultimate_try' function.
 *
 * @param table The 2D array representing the game table.
 * @param pieces The number of pieces to play with.
 */
void autocomplete_2D(Piece** table, int* pieces);

#endif //DOMINO_LINEARE_2D_AUTOCOMPLETE_H
