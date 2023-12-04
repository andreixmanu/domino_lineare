//
// Created by manua on 30/10/2023.
//

#include "../include/main.h"
#include "../include/print.h"
#include "../include/game.h"
#include "../include/autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1

Domino_piece *get_first_table_piece(Domino_piece *table) {
    Domino_piece *current_node = (Domino_piece *) malloc(sizeof(Domino_piece));
    current_node->left_side = table->left_side;
    current_node->right_side = table->right_side;
    current_node->next = NULL;
    current_node->previous = NULL;
    return current_node;
}

Domino_piece *get_last_table_piece(Domino_piece *table) {
    Domino_piece *current_node = table;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }
    return current_node;
}

Id_piece decide_piece(Domino_piece *table, Player *bot) {
    Id_piece returning_piece = {0, LEFT_SIDE}; // Default values

    // Indica se ci sono mosse possibili
    bool moveExists = false;

    // Calcola il punteggio attuale del tavolo
    int score = 0;
    Domino_piece *current_node = table;
    while (current_node != NULL) {
        score += current_node->left_side + current_node->right_side;
        current_node = current_node->next;
    }

    // Esamina tutte le combinazioni di pezzi nella mano del giocatore e posizioni a sinistra o a destra del tavolo
    Domino_piece *current_piece = bot->first_piece;
    int piece_index = 0;
    while (current_piece != NULL) {
        // Prova a piazzare il pezzo a sinistra
        int left_score = score + current_piece->left_side;
        if (table->left_side == current_piece->right_side) {
            left_score += table->left_side;
            moveExists = true;
        }

        // Prova a piazzare il pezzo a destra solo se esiste un pezzo nel tavolo
        int right_score = score + current_piece->right_side;
        if (get_last_table_piece(table) != NULL &&
            get_last_table_piece(table)->right_side == current_piece->left_side) {
            right_score += current_piece->left_side;
            moveExists = true;
        }

        // Confronta i punteggi e aggiorna la scelta se necessario
        if (left_score > score || (left_score == score && returning_piece.side == RIGHT_SIDE)) {
            score = left_score;
            returning_piece.npiece = piece_index;
            returning_piece.side = LEFT_SIDE;
        }

        if (right_score > score) {
            score = right_score;
            returning_piece.npiece = piece_index;
            returning_piece.side = RIGHT_SIDE;
        }

        // Passa al prossimo pezzo nella mano del giocatore
        current_piece = current_piece->next;
        piece_index++;
    }

    // Se non ci sono mosse possibili, setta i valori di returning_piece a -1
    if (!moveExists) {
        returning_piece.npiece = -1;
        returning_piece.side = -1;
    } else {
        returning_piece.npiece++;
    }

    return returning_piece;
}

Id_piece stupid_move(Domino_piece *table, Player *bot) {

    Id_piece returning_piece = {0, rand() % 2 == 0 ? LEFT_SIDE
                                                   : RIGHT_SIDE}; // Decide casualmente tra LEFT_SIDE e RIGHT_SIDE
    Domino_piece *temp = bot->first_piece;
    short index = 1;

    // Indica se ci sono mosse possibili
    bool moveExists = false;

    if (temp == NULL) {
        returning_piece.npiece = -1;
        returning_piece.side = -1;
        return returning_piece;
    }

    if (returning_piece.side == LEFT_SIDE) {
        Domino_piece *first_piece = get_first_table_piece(table);
        while (temp != NULL) {
            if (first_piece->left_side == temp->right_side) {
                returning_piece.npiece = index++;
                moveExists = true;
                break;
            }
            index++;
            temp = temp->next;
        }
    } else if (returning_piece.side == RIGHT_SIDE) {
        Domino_piece *last_piece = get_last_table_piece(table);
        while (temp != NULL) {
            if (last_piece->right_side == temp->left_side) {
                returning_piece.npiece = index++;
                moveExists = true;
                break;
            }
            index++;
            temp = temp->next;
        }
    }

    // Se non si trova nessuna combinazione sul lato iniziale, si resetta l'indice e si cerca sulla parte opposta
    if (!moveExists) {
        index = 0;
        Domino_piece *temp2 = bot->first_piece;

        if (temp2 == NULL) {
            returning_piece.npiece = -1;
            returning_piece.side = -1;
            return returning_piece;
        }

        if (returning_piece.side == LEFT_SIDE) {
            Domino_piece *other_piece = get_last_table_piece(table);
            while (temp2 != NULL) {
                if (other_piece->right_side == temp2->left_side) {
                    returning_piece.npiece = index++;
                    moveExists = true;
                    break;
                }
                temp2 = temp2->next;
                index++;
            }
        } else if (returning_piece.side == RIGHT_SIDE) {
            Domino_piece *other_first_piece = get_first_table_piece(table);
            while (temp2 != NULL) {
                if (other_first_piece->left_side == temp2->right_side) {
                    returning_piece.npiece = index++;
                    moveExists = true;
                    break;
                }
                temp2 = temp2->next;
                index++;
            }
        }
    }

    // Se non esiste una mossa valida, restituisci -1 per npiece e side
    if (!moveExists) {
        returning_piece.npiece = -1;
        returning_piece.side = -1;
    }

    return returning_piece;
}

void autocomplete_stupid(Player *bot, Domino_piece *table, int pieces) {
    printf("Bot's pieces:\n");
    print_player(bot);
    int random_piece = rand() % pieces;
    Domino_piece *first_piece = get_player_piece(bot, random_piece);
    append_piece(&table, first_piece);
    Id_piece piece = stupid_move(table, bot);

    for(int i = 0; i<pieces && piece.npiece != -1 && piece.side != -1;i++){
        use_piece(get_player_piece(bot, piece.npiece), &table, piece.side);
        piece = stupid_move(table, bot);
    }
    printf("Remaining bot pieces:\n");
    print_player(bot);
    printf("Printing final table\n");
    print_table(table);
    printf("Final score: %d\n", calculate_score(table));
    exit(EXIT_SUCCESS);
}

void autocomplete_smart(Player *bot, Domino_piece *table) {
    printf("Bot's pieces:\n");
    print_player(bot);

    //printf("DEBUG: Now deciding piece\n");
    Id_piece piece = stupid_move(table, bot);
    if (piece.side == LEFT_SIDE) printf("DEBUG: Bot has decided to use piece %d on LEFT side\n", piece.npiece);
    if (piece.side == RIGHT_SIDE) printf("DEBUG: Bot has decided to use piece %d on RIGHT side\n", piece.npiece);

    use_piece(get_player_piece(bot, piece.npiece), &table, piece.side);

    printf("Printing new table\n");
    print_table(table);
}
