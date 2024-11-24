#include "helper_functions.h"
#include <Windows.h>

int main(void)
{
    // initialize random and game board
    srand((unsigned int)time(NULL)); 
    Board* game_board = create_board();
    if (!game_board) return 0;
    BITBOARD white_state = game_board->state ->white;


    for (int i = 0; i <= 10; i++) {
        Move mv = get_random_move(game_board, i % 2 == 1);

        if (verify_move(game_board, &mv))
            move_piece(game_board, &mv);
       // system("cls");
        print_board(game_board);
        BITBOARD num = game_board->state->black | game_board->state->white;
        print_num(&num);
     //   Sleep(1000);
    }

    free_board(game_board);
    return 0;
}
