#include "helper_functions.h"

static inline int bad_coords(int x, int y) {
    return (x < 0) || (y < 0) ||
        (x >= BOARD_SIZE) || (y >= BOARD_SIZE) ||
        (x == EMPTY || y == EMPTY);
}

char get_piece_at(Board* board, int x, int y) {
    if (bad_coords(x, y)) return EMPTY;
    return *(board->grid + x + (y * BOARD_SIZE));
}

int can_move_vertical(char piece) {
    return (toupper(piece) == 'C' || toupper(piece) == 'P' || toupper(piece) == 'K' || toupper(piece) == 'Q');
}

int can_move_horizontal(char piece) {
    return (toupper(piece) == 'C' || toupper(piece) == 'K' || toupper(piece) == 'Q');
}

int can_move_diagonal(char piece) {
    return (toupper(piece) == 'B' || toupper(piece) == 'K' || toupper(piece) == 'Q');
}


int correct_direction(Move* move, char piece) {
    if (!move || (move->dx == 0 && move->dy == 0)) return 0;

    // make sure the piece is allowed to move in the way the move says
    if ((move->dx == 0 && move->dy != 0) && can_move_vertical(piece)) {
        return 1;
    }
    else if ((move->dx != 0 && move->dy == 0) && can_move_horizontal(piece)) {
        return 1;
    }
    else if ((move->dx == move->dy) && can_move_diagonal(piece)) {
        return 1;
    }

    return 0;
}

// u better be on the board >:(( and REALLLLL
int out_of_bounds(Move* move) {
        return bad_coords(move->x1, move->y1) ||(bad_coords(move->x2, move->y2)) 
            || (move->dx == 0 && move->dy == 0);
}


int is_same_team(char piece, char piece2) {
    if (isupper(piece))
        return isupper(piece2);
    
    if (islower(piece))
        return islower(piece2);

    return 0;
}

int piece_score(char piece) {
    switch (piece)
    {
    case 'P':
        return 1;
        break;
    case 'N':
        return 2;
        break;
    case 'B':
    case 'C':
        return 3;
        break;
    case 'Q':
        return 4;
        break;
    default:
        break;
    }
    return 0;
}


void move_piece(Board* board, Move* move) {
    char* old_pos = board->grid + move->x1 + (move->y1*BOARD_SIZE);
    char* new_pos = board->grid + move->x2 + (move->y2*BOARD_SIZE);
    char piece = get_piece_at(board, move->x1, move->y1);

    *new_pos = piece;
    *old_pos = EMPTY;
    MoveHistory* hist = push_history(move, board->history);
    piece_swap(board->state, move, islower(piece));
    if (board->history) {
        hist->last = board->history; 
    }
    board->history = hist;
}

MoveHistory* push_history(Move* move, MoveHistory* last) {
    MoveHistory* mv = (MoveHistory*)malloc(sizeof(MoveHistory));
    if (!mv) {
        return NULL;
    }
    mv->where = (Coordinates){move->x2, move->y2};
    mv->last = last;
    return mv;
}

MoveHistory* pop_history(MoveHistory* last) {
    MoveHistory* to_return = last->last;
    free(last);

    return to_return;
}

void free_history(MoveHistory* history) {
    while (history) {
        MoveHistory* temp = history;
        history = history->last;
        free(temp);
    }
}

void print_coords(Coordinates* c) {
    printf("(%c, %c) ", c->x + 'A', BOARD_SIZE - (c->y) + '0');
}

int num_from_char(char c) {
    if (c >= 'A' && c <= 'H') {
        return c- 'A';
    }
    if (c >= '0' && c <= '8') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'h') {
        return c- 'a';
    }
    return EMPTY;
}