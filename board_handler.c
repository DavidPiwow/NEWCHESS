#include "helper_functions.h"


Board* create_board(void) {
    Board* temp = (Board*)malloc(sizeof(Board));
    if (!temp) {
        printf("FAIL");
        return NULL;
    }

    // 64 places after the start - all sequential, get end of board
    char* board_start = &temp->grid[0];
    temp->board_end = &temp->grid[BOARD_SIZE * BOARD_SIZE];

    // set this to a null pointer for start of chain reasons
    temp->history = NULL;

    char pieces_u[16] = { 'C', 'N', 'B', 'Q', 'K', 'B', 'N', 'C',
                         'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' };
    char pieces_l[16] = { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                         'c', 'n', 'b', 'q', 'k', 'b', 'n', 'c' };

    // copy the above arrays into memory and set the rest to chosen EMPTY char
    memset(temp->grid, EMPTY, BOARD_SIZE * BOARD_SIZE);
    memcpy(board_start, pieces_u, sizeof(pieces_u));
    memcpy(temp->board_end - (BOARD_SIZE * 2), pieces_l, sizeof(pieces_l));

    BoardState state = create_board_state();
    temp->state = state;
    

    return temp;
}