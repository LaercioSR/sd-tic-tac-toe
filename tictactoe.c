#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

#define SIZE_BOARD 3

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

int main(void)
{
    char board[SIZE_BOARD][SIZE_BOARD] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    char playerValue;
    int numPlays = 0, col, row;
    int isWinner = 0;

    drawBoard();
    while ((numPlays < 9) && !isWinner)
    {
        int player = numPlays % 2 + 1;
        printf("Player %d: ", player);
        scanf("%d %d", &row, &col);
        printf("\033[1A");

        if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            printf("Invalid position!\n");
            return 1;
        }

        playerValue = player == 1 ? 'X' : 'O';
        board[col][row] = playerValue;

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
