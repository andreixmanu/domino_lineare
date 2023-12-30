//
// Created by andreixmanu on 28/10/23.
//

#include "main.h"

#ifndef DOMINO_LINEARE_PRINT_H
#define DOMINO_LINEARE_PRINT_H

/**
 * @brief Prints the current state of the Domino game table.
 *
 * This function prints the values of each Domino piece on the specified game table, representing
 * the current state of the game table.
 *
 * @param table A pointer to the head of the Domino game table.
 *
 * @details The function iterates through the linked list of Domino pieces on the table and prints
 * the left and right side values of each piece enclosed in square brackets. If the table is empty (NULL),
 * it prints a message indicating that the table is empty.
 *
 * @note The caller is responsible for ensuring that the provided game table is valid.
 */
void print_table(Domino_piece* table);

/**
 * @brief Prints the current state of a player's Domino pieces.
 *
 * This function prints the left and right side values of each Domino piece belonging to the specified player,
 * representing the current state of the player's pieces.
 *
 * @param player A pointer to the Player structure representing the player.
 *
 * @details The function checks if the player or the player's pieces are null. If the player is null, it prints
 * a debugging message indicating that the player is null. If the player's pieces are null, it prints a message
 * indicating that the player has no pieces and assigns a default set of pieces. It then prints the index, left
 * and right side values of each piece belonging to the player.
 *
 * @note The caller is responsible for ensuring that the provided player structure is valid.
 */

/**
 * @brief Prints the current state of a player's Domino pieces.
 *
 * This function prints the left and right side values of each Domino piece belonging to the specified player,
 * representing the current state of the player's pieces.
 *
 * @param player A pointer to the Player structure representing the player.
 *
 * @details The function checks if the player or the player's pieces are null. If the player is null, it prints
 * a debugging message indicating that the player is null. If the player's pieces are null, it prints a message
 * indicating that the player has no pieces and assigns a default set of pieces. It then prints the index, left
 * and right side values of each piece belonging to the player.
 *
 * @note The caller is responsible for ensuring that the provided player structure is valid.
 */
void print_player(Player* player);

/**
 * @brief Prints the rules and instructions for playing the Domino Lineare game.
 *
 * This function displays detailed rules and instructions for playing the Domino Lineare game.
 * It covers the player's options, the structure of Domino pieces, placement rules, and scoring.
 * Additionally, it provides information about playing against the CPU and the option to play in
 * non-linear mode, allowing vertical placement of pieces.
 *
 * @details The function prints the rules to the standard output and then calls the `view_menu` function,
 * redirecting the user to the main menu to start or configure a game.
 */
void print_rules();

/**
 * @brief Prints the end game screen, including the score and an ASCII art display.
 *
 * This function displays an ASCII art representation of the end game screen, including the final
 * score calculated from the Domino game table. It prompts the user with an option to play the game
 * again and responds accordingly.
 *
 * @param table A pointer to the head of the Domino game table.
 *
 * @details The function prints an ASCII art representation of the end game screen, which includes
 * a decorative title and the calculated score. It then prompts the user with a question about whether
 * they want to play the game again. If the user enters 'y' for yes, it restarts the game by calling
 * the `main` function. Otherwise, it exits the program.
 *
 * @note The caller is responsible for ensuring that the provided game table is valid.
 */
void print_end_game(Domino_piece ** table);

#endif //DOMINO_LINEARE_PRINT_H
