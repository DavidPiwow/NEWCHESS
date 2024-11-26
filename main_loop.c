#include "helper_functions.h"
#include <Windows.h>

int main(void)
{
    // initialize random and game board
    srand((unsigned int)time(NULL)); 
    Board* game_board = create_board();
    if (!game_board) return 0;
    BITBOARD white_state = game_board->state ->white;


    for (int i = 0; i <= 100; i++) {

        if (i % 2 == 0) {
            char x = fgetc(stdin);
            system("cls");

            print_board(game_board);
        }
        Move mv = get_random_move(game_board, i % 2 == 1);

        while (!verify_move(game_board, &mv))
            mv = get_random_move(game_board, i % 2 == 1);

        move_piece(game_board, &mv);
        printf("\n\n");
        
    }

    free_board(game_board);
    return 0;
}
