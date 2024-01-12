//
// Created by andre on 11/01/2024.
//

#ifndef DOMINO_LINEARE_CHALLENGE_H
#define DOMINO_LINEARE_CHALLENGE_H


void end_challenge(int challenge);

/**
 * @brief Manages the Challenge mode, allowing the player to select a specific challenge.
 *
 * The function provides options for the available challenges and calls the selected challenge.
 *
 * @note The function is also responsible for handling user choices and invoking the corresponding challenge function.
 */
void challenge_main();
/**
 * @brief Implementation of Challenge 1.
 *
 * In this challenge, the player must reach exactly the maximum score specified by the constant CHALLENGE_1_MAX_SCORE.
 * The challenge provides the player with a predefined set of cards and an initial table configuration.
 * The challenge is completed when the player reaches the maximum score or surrenders.
 */
void challenge_1();
/**
 * @brief Implementation of Challenge 2.
 *
 * In this challenge, the player must reach exactly the maximum score specified by the constant CHALLENGE_2_MAX_SCORE.
 * The challenge modifies the number of rows in the table to 2 and presents a specific table configuration and a predefined set of cards for the player.
 * The challenge is completed when the player reaches the maximum score or surrenders.
 */
void challenge_2();
/**
 * @brief Implementation of Challenge 3.
 *
 * In this challenge, the player must reach exactly the specified maximum score, CHALLENGE_3_MAX_SCORE.
 * The player is provided with a predefined set of cards and an initial table configuration.
 * The challenge is completed when the player reaches the maximum score or surrenders.
 */
void challenge_3();
/**
 * @brief Implementation of Challenge 4.
 *
 * In this challenge, the player must reach exactly the specified maximum score, CHALLENGE_4_MAX_SCORE.
 * Note: In this challenge, the player can only place pieces vertically.
 * The challenge is completed when the player reaches the maximum score or surrenders.
 */
void challenge_4();

#endif //DOMINO_LINEARE_CHALLENGE_H
