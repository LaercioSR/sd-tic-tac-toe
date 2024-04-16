#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>
#include "draw.h"

#define SIZE_BOARD 3

#define EV_KEY 0x01
#define EV_REL 0x02

#define REL_X 0x00
#define REL_Y 0x01

struct input_event
{
    struct timeval time;
    uint16_t type;
    uint16_t code;
    int32_t value;
};

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

void changePosition(char board[SIZE_BOARD][SIZE_BOARD], int row, int col, int lastRow, int lastCol)
{
    printf("\033[1APosição atual: %d %d\n", row, col);
    cleanBlock(lastRow, lastCol);
    if (board[lastRow][lastCol] == 'X')
    {
        drawX(lastRow, lastCol);
    }
    else if (board[lastRow][lastCol] == 'O')
    {
        drawO(lastRow, lastCol);
    }
    drawBlock(row, col);
    if (board[row][col] == 'X')
    {
        drawX(row, col);
    }
    else if (board[row][col] == 'O')
    {
        drawO(row, col);
    }
}

int main(void)
{
    int fileInput;
    struct input_event event;
    char board[SIZE_BOARD][SIZE_BOARD] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    char playerValue;
    int numPlays = 0, row = 0, col = 0, qttClick = 0;
    int isWinner = 0;
    int x = 1;
    int y = 1;

    fileInput = open("/dev/input/event7", O_RDONLY);
    if (fileInput == -1)
    {
        perror("Erro ao abrir o dispositivo de entrada");
        return 1;
    }

    drawBoard();
    drawBlock(row, col);
    while ((numPlays < 9) && !isWinner)
    {
        int player = numPlays % 2 + 1;

        ssize_t bytes = read(fileInput, &event, sizeof(event));
        if (bytes == -1)
        {
            perror("Erro ao ler o evento");
            close(fileInput);
            return 1;
        }
        if (event.type == EV_REL && event.code == REL_X)
        {
            if (event.value > 0 && x < 1499)
            {
                x++;
            }
            else if (event.value < 0 && x > 0)
            {
                x--;
            }
            if (col != (x / 500))
            {
                changePosition(board, row, (x / 500), row, col);
                col = (x / 500);
                qttClick = 0;
            }
        }
        if (event.type == EV_REL && event.code == REL_Y)
        {
            if (event.value > 0 && y < 1499)
            {
                y++;
            }
            else if (event.value < 0 && y > 0)
            {
                y--;
            }
            if (row != (y / 500))
            {
                changePosition(board, (y / 500), col, row, col);
                row = (y / 500);
                qttClick = 0;
            }
        }
        if (event.type == EV_KEY && event.value == 1)
        {
            qttClick++;
            if (qttClick == 2)
            {
                if (board[row][col] == ' ')
                {
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
                qttClick = 0;
            }
        }
    }

    return 0;
}
