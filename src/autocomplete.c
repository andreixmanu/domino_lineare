//
// Created by manua on 30/10/2023.
//

#include "../include/main.h"
#include "../include/print.h"
#include "../include/game.h"
#include "../include/autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1


void autocomplete(Player *bot, Player *enemy_bot, Domino_piece *table) {
    //TODO implementare AI
}

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


Id_piece decide_piece(Domino_piece* table, Player* bot) {
    Id_piece returning_piece = {0, LEFT_SIDE}; // Default values

    // Calcola il punteggio attuale del tavolo
    int score = 0;
    Domino_piece* current_node = table;
    while (current_node != NULL) {
        score += current_node->left_side + current_node->right_side;
        current_node = current_node->next;
    }

    // Esamina tutte le combinazioni di pezzi nella mano del giocatore e posizioni a sinistra o a destra del tavolo
    Domino_piece* current_piece = bot->first_piece;
    int piece_index = 0;
    while (current_piece != NULL) {
        // Prova a piazzare il pezzo a sinistra
        int left_score = score + current_piece->left_side;
        if (table->left_side == current_piece->right_side) {
            left_score += table->left_side;
        }

        // Prova a piazzare il pezzo a destra solo se esiste un pezzo nel tavolo
        int right_score = score + current_piece->right_side;
        if (get_last_table_piece(table) != NULL && get_last_table_piece(table)->right_side == current_piece->left_side) {
            right_score += current_piece->left_side;
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

    // Incrementa l'indice del pezzo come hai fatto prima
    returning_piece.npiece++;

    return returning_piece;
}

Id_piece stupid_move(Domino_piece* table, Player* bot) {
    printf("DEBUG: Inside stupid_move\n");
    Id_piece returning_piece = {0, rand() % 2 == 0 ? LEFT_SIDE : RIGHT_SIDE}; // Decide casualmente tra LEFT_SIDE e RIGHT_SIDE
    Domino_piece* temp = bot->first_piece;
    short index = 1;

    if (temp == NULL) {
        // Gestisci il caso in cui la lista dei pezzi del bot sia vuota
        printf("Bot has no pieces, you won the game!");
        exit(0);
    }
    printf("First check\n");
    if (returning_piece.side == LEFT_SIDE) {
        Domino_piece* first_piece = get_first_table_piece(table);
        while (first_piece != NULL) {
            if (first_piece->left_side == temp->right_side) {
                returning_piece.npiece = index;
                return returning_piece;
            }
            index++;
            temp = temp->next;
        }
        printf("Vado nel primo else if\n");
    } else if (returning_piece.side == RIGHT_SIDE) {
        Domino_piece* last_piece = get_last_table_piece(table);
        while (last_piece != NULL) {
            if (last_piece->right_side == temp->left_side) {
                returning_piece.npiece = index;
                return returning_piece;
            }
            index++;
            temp = temp->next;
        }
    }

    // Se nessuna combinazione è stata trovata sul lato iniziale,
    // resetta l'indice e cerca nell'altro lato senza liberare la memoria di temp
    index = 0;
    Domino_piece* temp2 = bot->first_piece;
    if (temp2 == NULL) {
        // Gestisci il caso in cui la lista dei pezzi del bot sia vuota
        printf("Bot has no pieces, you won the game!");
        exit(0);
    }
    printf("Second check\n");
    if (returning_piece.side == LEFT_SIDE) {
        Domino_piece* other_piece = get_last_table_piece(table);
        while (other_piece != NULL) {
            if (other_piece->right_side == temp2->left_side) {
                returning_piece.npiece = index;
                return returning_piece;
            }
            temp2 = temp2->next;
            index++;
        }
        printf("Entro nel secondo else if\n");
    } else if (returning_piece.side == RIGHT_SIDE) {
        Domino_piece* other_first_piece = get_first_table_piece(table);
        while (other_first_piece != NULL) {
            if (other_first_piece->left_side == temp2->right_side) {
                returning_piece.npiece = index;
                return returning_piece;
            }
            temp2 = temp2->next;
            index++;
        }
    }

    // Se nessuna combinazione è stata trovata su entrambi i lati,
    // il giocatore ha vinto la partita
    printf("Bot has no options, you won the game!");
    exit(0);
}


void cpu_move(Player *bot, Domino_piece *table) {
    printf("Bot's pieces:\n");
    print_player(*bot);

    //printf("DEBUG: Now deciding piece\n");
    Id_piece piece = stupid_move(table, bot);
    if(piece.side == LEFT_SIDE) printf("DEBUG: Bot has decided to use piece %d on LEFT side\n", piece.npiece);
    if(piece.side == RIGHT_SIDE) printf("DEBUG: Bot has decided to use piece %d on RIGHT side\n", piece.npiece);

    use_piece(bot, table, piece.npiece, piece.side);

    printf("Printing new table\n");
    print_table(table);
}
