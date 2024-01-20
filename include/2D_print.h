//
// Created by andreixmanu on 08/12/23.
//
#include "../include/2D_gamemode.h"

#ifndef DOMINO_LINEARE_2D_PRINT_H
#define DOMINO_LINEARE_2D_PRINT_H

/**
 * @brief Prints the pieces of a player in a 2D domino game.
 *
 * This function prints the pieces of a player in a 2D domino game, excluding
 * any empty pieces. Each piece is displayed with its left and right sides.
 *
 * @param player An array of Piece representing the player's pieces.
 * @param n The number of pieces in the player's array.
 */
void print_player_2D(Piece* player, int n);

/**
 * @brief Prints the domino table in a 2D format.
 *
 * This function prints the domino table in a 2D format, showing the arrangement
 * of pieces in rows and columns. Empty spaces are represented by "[   ]", and
 * individual pieces are displayed as "[left|right]". If one side of the piece
 * is -1, only the non -1 side is displayed.
 *
 * @param table A 2D array of Piece representing the domino table.
 * @param rows The number of rows in the table.
 */
void print_table_2D(Piece** table, int rows);

/**
 * @brief Prints the domino pieces of a player for debugging purposes.
 *
 * This function prints the domino pieces of a player in a debug-friendly format.
 * Each piece is displayed as "[%d|%d]", where %d represents the left and right
 * sides of the piece. The pieces are numbered starting from 1.
 *
 * @param player An array of Piece representing the player's domino pieces.
 * @param n The number of pieces in the player's array.
 */
void print_player_2D_DEBUG(Piece* player, int n);

/**
 * @brief Prints the domino table for debugging purposes.
 *
 * This function prints the domino table in a debug-friendly format.
 * Each cell of the table is displayed as "[   ]" for an empty cell,
 * "[ %d ]" for a cell with a non-empty right side, "[ %d ]" for a cell
 * with a non-empty left side, and "[%d|%d]" for a cell with both sides.
 *
 * @param table A 2D array of Piece representing the domino table.
 *              The table is assumed to have dimensions 5x20.
 */
void print_table_2D_DEBUG(Piece** table);

/**
 * @brief Prints the end game screen for a 2D domino game.
 *
 * This function displays a stylized end game screen for a 2D domino game,
 * including the game logo, final score, and prompts the user to play again.
 * If the user chooses to play again, the function calls the main() function,
 * otherwise, it exits the program.
 *
 * @param table A 2D array of Piece representing the domino table.
 *              The table is assumed to have dimensions 5x20.
 */
void print_end_game_2D(Piece** table, int rows);

#endif //DOMINO_LINEARE_2D_PRINT_H
