#include <stdio.h>

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

void drawBoard(char board[SIZE_BOARD][SIZE_BOARD])
{
    int i, j;
    for (i = 0; i < SIZE_BOARD; i++)
    {
        for (j = 0; j < SIZE_BOARD; j++)
        {
            printf("%c", board[i][j]);
            if (j != 2)
                printf("|");
        }
        printf("\n");
    }
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

    while ((numPlays < 9) && !isWinner)
    {
        int player = numPlays % 2 + 1;
        printf("Player %d:", player);
        scanf("%d %d", &col, &row);

        if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            printf("Invalid position!\n");
            return 1;
        }

        playerValue = player == 1 ? 'X' : 'O';
        board[col][row] = playerValue;

        drawBoard(board);

        isWinner = checkWin(board, playerValue);
        if (isWinner)
            printf("Player %d is winner!!!\n", player);

        numPlays += 1;
    }

    return 0;
}
