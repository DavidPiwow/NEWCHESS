#ifndef BITBOARDH
#define BITBOARDH

#include "helper_functions.h"

typedef uint64_t BITBOARD;


struct _board_state {
    BITBOARD white;
    BITBOARD black;
};


void print_num(BITBOARD* board);

typedef struct _board_state BoardState;

static void shift_mask(BITBOARD* original_mask, int x, int y);


int piece_swap(BoardState* game_state, struct _move* move, int white_team);
int attempt_move(BoardState* game_state, struct _move* move, int white_team);



#endif