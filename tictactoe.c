#include <stdio.h>
#include <stdlib.h>
// #include <stdint.h>
// #include <sys/time.h>
#include "draw.h"

#define SIZE_BOARD 3

// #define EV_KEY 0x01
// #define EV_REL 0x02

// #define REL_X 0x00
// #define REL_Y 0x01

// struct input_event
// {
//     struct timeval time;
//     uint16_t type;
//     uint16_t code;
//     int32_t value;
// };

int checkWin(char board[SIZE_BOARD][SIZE_BOARD], char player)
{
    int i, j;
    int isWinnerDiag = 1;
    for (i = 0; i < SIZE_BOARD; i++)
    {
        int isWinnerRow = 1;
        int isWinnerCol = 1;

        isWinnerDiag = isWinnerDiag && (board[i][i] == player);
        for (j = 0; j < SIZE_BOARD; j++)
        {
            isWinnerRow = isWinnerRow && (board[i][j] == player);
            isWinnerCol = isWinnerCol && (board[j][i] == player);
        }
        if (isWinnerRow || isWinnerCol)
            return 1;
    }

    if (isWinnerDiag)
        return 1;

    return 0;
}

void waitPlay(int player, int *row, int *col)
{
    int confirmation = 0;

    do
    {

        printf("Player %d: ", player);
        scanf("%d %d", row, col);
        printf("\033[1A");

        if (*row < 0 || *row > 2 || *col < 0 || *col > 2)
        {
            printf("Invalid position!\n");
        }
        drawBlock(*row, *col);
        printf("Deseja confirmar? ");
        scanf("%d", &confirmation);
        printf("\033[1A");
        if (!confirmation)
            cleanBlock(*row, *col);
        printf("                    \n\033[1A");
    } while (!confirmation);
}

int main(void)
{
    char board[SIZE_BOARD][SIZE_BOARD] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    char playerValue;
    int numPlays = 0, row, col;
    int isWinner = 0;

    drawBoard();
    while ((numPlays < 9) && !isWinner)
    {
        int player = numPlays % 2 + 1;
        waitPlay(player, &row, &col);

        playerValue = player == 1 ? 'X' : 'O';
        board[row][col] = playerValue;

        if (player == 1)
        {
            drawX(row, col);
        }
        else
        {
            drawO(row, col);
        }

        isWinner = checkWin(board, playerValue);
        if (isWinner)
            printf("Player %d is winner!!!\n", player);

        numPlays += 1;
    }

    return 0;
}
