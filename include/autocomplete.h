//
// Created by manua on 30/10/2023.
//

#ifndef DOMINO_LINEARE_AUTOCOMPLETE_H
#define DOMINO_LINEARE_AUTOCOMPLETE_H

#include "../include/main.h"

typedef struct{
    int npiece;
    int side;
} Id_piece;

/**
 * @brief Retrieves the first Domino piece from the game table.
 *
 * This function creates and returns a new Domino piece structure with the same values
 * as the first piece on the specified game table.
 *
 * @param table A pointer to the head of the Domino game table.
 * @return A pointer to a new Domino piece structure representing the first piece on the table.
 *
 * @details The function allocates memory for a new Domino piece, copies the values from the first piece
 * on the table, and returns a pointer to the newly created piece.
 *
 * @note The caller is responsible for managing the memory of the returned Domino piece.
 */
Domino_piece *get_first_table_piece(Domino_piece *table);

/**
 * @brief Retrieves the last Domino piece from the game table.
 *
 * This function traverses the specified game table to find and return a pointer to the last
 * Domino piece on the table.
 *
 * @param table A pointer to the head of the Domino game table.
 * @return A pointer to the last Domino piece on the table.
 *
 * @details The function iterates through the linked list of Domino pieces until it reaches the
 * last piece and returns a pointer to that piece.
 *
 * @note The caller is responsible for ensuring that the provided game table is not empty (not NULL).
 */
Domino_piece *get_last_table_piece(Domino_piece *table);

/**
 * @brief Generates a move for a bot player in Domino using a simplistic "stupid" strategy.
 *
 * This function determines a move for a bot player based on a basic strategy. It randomly decides
 * whether to place a piece on the left or right side of the game table and then looks for a matching piece
 * in the bot's set of pieces. If no valid move is found, it resets and looks for a match on the opposite side.
 *
 * @param table A pointer to the head of the Domino game table.
 * @param bot A pointer to the Player structure representing the bot.
 * @return An Id_piece structure representing the chosen move, including the index of the selected piece (npiece)
 * and the side (LEFT_SIDE or RIGHT_SIDE) where it is placed.
 *
 * @details The function first randomly decides whether to place a piece on the left or right side of the table.
 * It then iterates through the bot's set of pieces, looking for a match on the chosen side. If a valid move is found,
 * the function returns an Id_piece structure with information about the selected move. If no valid move is found on
 * the chosen side, the function resets and looks for a match on the opposite side. If still no valid move is found,
 * the function returns an Id_piece structure with npiece and side set to -1.
 *
 * @note The caller is responsible for interpreting the returned Id_piece structure and managing the memory of the
 * specified game table and the bot's set of pieces.
 */
Id_piece stupid_move(Domino_piece *table, Player *bot);

/**
 * @brief Performs an automated, simplistic gameplay for a bot in Domino using a "stupid" strategy.
 *
 * This function simulates a bot's gameplay by selecting random pieces and making moves based on a
 * simplistic strategy. The bot continues making moves until it can no longer play or until the game ends.
 *
 * @param bot A pointer to the Player structure representing the bot.
 * @param table A pointer to the head of the Domino game table.
 * @param pieces The number of Domino pieces in the initial set for the bot.
 *
 * @details The function prints the bot's initial pieces, selects a random piece to start the game,
 * and then uses a "stupid" strategy to make subsequent moves. The strategy continues until the bot can
 * no longer play or until the game ends. The final state of the game table is printed, and the game ends
 * with an exit code of EXIT_SUCCESS.
 */
void autocomplete_stupid(Player *bot, Domino_piece* table, int pieces);

#endif //DOMINO_LINEARE_AUTOCOMPLETE_H
