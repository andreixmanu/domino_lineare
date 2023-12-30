//
// Created by andreixmanu on 25/10/23.
//

#ifndef DOMINO_LINEARE_VIEW_MENU_H
#define DOMINO_LINEARE_VIEW_MENU_H

#include "main.h"

/**
 * @brief Displays the main menu of the Domino Lineare game and handles user input.
 *
 * This function presents options to the user, such as playing the game, viewing rules,
 * or exiting the program. It includes a loop that continues until a valid option is selected.
 * Depending on the user's choice, it may initiate the game, display rules, or exit the program.
 */
void view_menu();

/**
 * @brief Flushes the input buffer by discarding any remaining characters until a newline or EOF is encountered.
 *
 * This function is useful for clearing the input buffer, ensuring there are no leftover characters
 * that might interfere with subsequent input operations. It reads characters from the standard input
 * until a newline character or end-of-file (EOF) is encountered.
 */
void flush_input_buffer();


#endif //DOMINO_LINEARE_VIEW_MENU_H
