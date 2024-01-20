//
// Created by andreixmanu on 28/10/23.
//


#ifndef DOMINO_LINEARE_GAME_H
#define DOMINO_LINEARE_GAME_H


#include "main.h"

/**
 * @brief Creates a new Domino table.
 *
 * @return A pointer to NULL
 */
Domino_piece *create_table();

/**
 * @brief Calculates the total score of a Domino game table.
 *
 * This function computes the total score of a Domino game table by summing up the values of
 * each Domino piece present on the table. The score is the sum of the left and right sides
 * of each Domino piece.
 *
 * @param table A pointer to the head of the Domino game table.
 * @return The total score of the Domino game table.
 *
 * @details The function iterates through the Domino pieces on the table, adding the values of
 * both sides (left and right) for each piece. The calculated score is then returned.
 * If the input table pointer is NULL, the function prints a debug message and exits with failure.
 */
int calculate_score(Domino_piece* table);

/**
 * @brief Retrieves the n-th Domino piece from a player's set of pieces.
 *
 * This function returns a pointer to the n-th Domino piece in a player's set of pieces.
 * It allows accessing a specific piece in the player's collection, given the position (n).
 *
 * @param player A pointer to the Player structure representing the player.
 * @param n The position of the desired Domino piece in the player's set (1-based index).
 * @param max The maximum number of pieces in the player's set.
 * @return A pointer to the n-th Domino piece, or NULL if an error occurs.
 *
 * @details The function checks if the specified position (n) is within the valid range (1 to max),
 * and if the player and the first piece in the player's set are not NULL. If any of these conditions
 * are not met, the function prints a debug message and returns NULL. Otherwise, it traverses the player's
 * set of pieces to locate the n-th piece and returns a pointer to that Domino piece.
 */
Domino_piece *get_player_piece(Player *player, int n, int max_pieces);

/**
 * @brief Appends a Domino piece to the end of the given Domino game table.
 *
 * This function adds a new Domino piece to the end of the specified Domino game table.
 * It creates a clone of the given piece and appends it to the table, adjusting pointers
 * accordingly.
 *
 * @param table A pointer to a pointer to the head of the Domino game table.
 * @param piece A pointer to the Domino piece to be appended to the table.
 *
 * @details The function allocates memory for a new Domino piece clone, copies the values
 * from the provided piece, and appends the clone to the end of the table. If the table is
 * initially empty, the clone becomes the head of the table. The function updates the next
 * and previous pointers of the relevant pieces to maintain the linked structure.
 */
void append_piece(Domino_piece **table, Domino_piece* piece);

/**
 * @brief Prepends a Domino piece to the beginning of the given Domino game table.
 *
 * This function adds a new Domino piece to the beginning of the specified Domino game table.
 * It creates a clone of the given piece and prepends it to the table, adjusting pointers
 * accordingly.
 *
 * @param table A pointer to a pointer to the head of the Domino game table.
 * @param piece A pointer to the Domino piece to be prepended to the table.
 *
 * @details The function allocates memory for a new Domino piece clone, copies the values
 * from the provided piece, and prepends the clone to the beginning of the table. If the table is
 * initially empty, the clone becomes the head of the table. The function updates the next
 * and previous pointers of the relevant pieces to maintain the linked structure.
 */
void prepend_piece(Domino_piece **table, Domino_piece* piece);

/**
 * @brief Assigns a specified number of random Domino pieces to a player's set.
 *
 * This function randomly selects Domino pieces from a predefined set and assigns them
 * to the specified player's set. The number of pieces assigned is determined by the 'n' parameter.
 *
 * @param player A pointer to the Player structure representing the player.
 * @param n The number of Domino pieces to assign to the player.
 *
 * @details The function uses a predefined set of 21 possible Domino pieces, each represented
 * by a pair of integers. It randomly selects pieces from this set and allocates memory for new
 * Domino_piece nodes. The assigned pieces are added to the end of the player's set, updating
 * pointers accordingly. If memory allocation fails, the function prints an error message and exits.
 *
 * @note The caller should ensure that the provided player pointer is valid.
 *
 * @warning This function uses the rand() function, which might not be suitable for cryptographic
 * or high-quality random number generation. Consider using a more robust random number generator
 * for security-critical applications.
 */
void assign_pieces(Player *player, int n);

/**
 * @brief Creates a new player with an empty set of Domino pieces.
 *
 * This function initializes a new player with an empty set of Domino pieces
 * and returns the created player structure.
 *
 * @return A Player structure representing the newly created player.
 *
 * @details The function sets the 'first_piece' and 'last_piece' pointers of the player
 * structure to NULL, indicating an empty set of Domino pieces.
 */
Player create_player();

/**
 * @brief Checks if a Domino piece can be legally moved to a specified side of the game table.
 *
 * This function examines whether a given Domino piece can be legally moved to the specified side
 * (LEFT_SIDE or RIGHT_SIDE) of the game table. It evaluates the compatibility of the piece with
 * the current state of the table and returns a status indicating whether the move is allowed or not.
 *
 * @param piece A pointer to the Domino piece to be checked for a legal move.
 * @param table A pointer to the head of the Domino game table.
 * @param side An integer representing the side of the table to which the move is to be checked
 *             (LEFT_SIDE or RIGHT_SIDE).
 * @return An integer representing the status of the move (MOVE_ALLOWED or MOVE_NOT_ALLOWED).
 *
 * @details The function checks the compatibility of the given piece with the specified side of the
 * table. If the move is allowed, it returns MOVE_ALLOWED; otherwise, it returns MOVE_NOT_ALLOWED.
 * The function also handles special cases, such as an empty table, and exits the program if an invalid
 * state is detected.
 */
int check_move(Domino_piece* piece, Domino_piece *table, int side);

/**
 * @brief Places a Domino piece on the game table, updating the table and player accordingly.
 *
 * This function places a Domino piece on the specified side (LEFT_SIDE or RIGHT_SIDE) of the game table.
 * It checks if the move is allowed and updates both the table and the player's set of pieces accordingly.
 *
 * @param piece A pointer to the Domino piece to be placed on the table.
 * @param table A pointer to a pointer to the head of the Domino game table.
 * @param side An integer representing the side of the table where the piece is to be placed
 *             (LEFT_SIDE or RIGHT_SIDE).
 * @param player A pointer to the Player structure representing the player who used the piece.
 *
 * @details The function checks if the table is empty and places the piece accordingly.
 * If the move is allowed, the piece is added to the specified side of the table, and the
 * corresponding adjustments are made to the player's set. If the move is not allowed,
 * the function returns without making any changes.
 *
 * @note The caller is responsible for managing the memory of the game table and ensuring that
 * the provided piece and player pointers are valid.
 */
void use_piece(Domino_piece* piece, Domino_piece** table, int side, Player *player);

/**
 * @brief Switches the values of a specified Domino piece in a player's set.
 *
 * This function switches the values of the specified Domino piece in the set of pieces
 * belonging to the provided player. The piece is identified by its position (n) in the set.
 *
 * @param player A pointer to the Player structure representing the player.
 * @param n The position of the Domino piece in the player's set to have its values switched.
 *
 * @details The function retrieves the specified Domino piece using its position (n) in the player's set,
 * and then swaps its left and right side values. If the specified position is invalid or the retrieved
 * piece is NULL, the function prints an error message and returns without making any changes.
 *
 * @note The caller should ensure that the provided player pointer is valid, and the specified position (n)
 * is within the valid range of the player's set of pieces.
 */
void switch_values(Player *player, int n);

/**
 * @brief Executes a single-player Domino game with the specified number of pieces and initial table configuration.
 *
 * This function simulates a single-player Domino game where the player is prompted to place Domino pieces
 * on the game table based on specific rules. The game continues until the player runs out of pieces or chooses to quit.
 *
 * @param pieces The number of Domino pieces to assign to the player initially.
 * @param table A pointer to the head of the Domino game table.
 *
 * @details The function initializes a player, assigns the specified number of Domino pieces to the player, and
 * prompts the player to place pieces on the table. The player can choose to quit, switch values of a piece, or
 * place a piece on the left or right side of the table. The game continues until the player runs out of pieces or quits.
 *
 * @note The caller is responsible for managing the memory of the game table and ensuring that the specified number of
 * pieces is valid. The game ends with an exit code of EXIT_SUCCESS when the player runs out of pieces or chooses to quit.
 */
void singleplayer(int pieces, Domino_piece* table);

/**
 * @brief Initializes and starts a game of Domino.
 *
 * This function initializes a Domino game by creating an empty game table and prompting the user
 * to specify the number of pieces and game mode. It then starts the selected game mode, either singleplayer
 * or CPU mode, and manages the flow of the game until completion.
 *
 * @details The function prompts the user to enter the number of pieces to play with and the desired game mode.
 * It handles invalid inputs and provides options for singleplayer mode or CPU mode. In singleplayer mode, the user
 * interacts with the game, while in CPU mode, the computer autonomously plays using a simplified strategy.
 * The game continues until completion, and memory allocated for the game table is freed at the end.
 *
 * @note The caller is responsible for managing the memory of the game table.
 */
void init_game();

#endif //DOMINO_LINEARE_GAME_H
