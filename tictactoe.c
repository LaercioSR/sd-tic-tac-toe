#include <stdio.h>
#include <stdlib.h>
#include <intelfpgaup/KEY.h>
#include <intelfpgaup/HEX.h>
#include "draw.h"
#include "mouse.h"

#define SIZE_BOARD 3
#define SIZE_BLOCK 150

int checkWin(char board[SIZE_BOARD][SIZE_BOARD], char player)
{
    int i, j;
    int isWinnerDiag1 = 1;
    int isWinnerDiag2 = 1;
    int maxPosBoard = SIZE_BOARD - 1;
    for (i = 0; i < SIZE_BOARD; i++)
    {
        int isWinnerRow = 1;
        int isWinnerCol = 1;

        isWinnerDiag1 = isWinnerDiag1 && (board[i][i] == player);
        isWinnerDiag2 = isWinnerDiag2 && (board[i][maxPosBoard - i] == player);
        for (j = 0; j < SIZE_BOARD; j++)
        {
            isWinnerRow = isWinnerRow && (board[i][j] == player);
            isWinnerCol = isWinnerCol && (board[j][i] == player);
        }
        if (isWinnerRow || isWinnerCol)
            return 1;
    }

    if (isWinnerDiag1 || isWinnerDiag2)
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

void showWinner(int player)
{
    /*              6543210 6543210*/
    int data_h = 0b0111001100111000;
    /*                            6543210 6543210 6543210 6543210*/
    int data_l = player == 1 ? 0b01110111011001100000000000000110
                             : 0b01110111011001100000000000111111;

    HEX_raw(data_h, data_l);
}

int main(void)
{
    char board[SIZE_BOARD][SIZE_BOARD] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    char playerValue;
    int button_state = 0;
    int maxBoardSize = SIZE_BLOCK * 3 - 1;
    int numPlays = 0, row = 0, col = 0, qttClick = 0;
    int isWinner = 0;
    int startGame = 0;
    int x = 1;
    int y = 1;

    openMouse();
    KEY_open();
    HEX_open();

    printf("Aperte botão para iniciar o jogo...\n");
    while (!startGame)
    {
        if (!KEY_read(&button_state))
        {
            printf("Erro ao ler o estado do push button.\n");
        }

        if (button_state == 1)
        {
            startGame = button_state;
        }
    }
    printf("\033[1A");

    HEX_raw(0, 0);
    drawBoard();
    drawBlock(row, col);

    while ((numPlays < 9) && !isWinner)
    {
        int player = numPlays % 2 + 1;
        int playerSegments = player == 1 ? 0b00000000000000000000000000000110
                                         : 0b00000000000000000000000000111111;
        HEX_raw(0, playerSegments);

        input_mouse event = readMouse();
        if (event.x != 0)
        {
            if (event.x > 0 && x < maxBoardSize)
            {
                x++;
            }
            else if (event.x < 0 && x > 0)
            {
                x--;
            }
            if (col != (x / SIZE_BLOCK))
            {
                changePosition(board, row, (x / SIZE_BLOCK), row, col);
                col = (x / SIZE_BLOCK);
                qttClick = 0;
            }
        }
        if (event.y != 0)
        {
            if (event.y < 0 && y < maxBoardSize)
            {
                y++;
            }
            else if (event.y > 0 && y > 0)
            {
                y--;
            }
            if (row != (y / SIZE_BLOCK))
            {
                changePosition(board, (y / SIZE_BLOCK), col, row, col);
                row = (y / SIZE_BLOCK);
                qttClick = 0;
            }
        }
        if (event.click == 1)
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

                    if ((SIZE_BOARD * 2) - 1)
                    {
                        isWinner = checkWin(board, playerValue);
                        if (isWinner)
                        {
                            showWinner(player);
                            printf("Player %d is winner!!!\n", player);
                        }
                    }

                    numPlays += 1;
                }
                qttClick = 0;
            }
        }
    }
    if (!isWinner)
    {
        printf("Empate!!!\n");
    }
    closeMouse();
    KEY_close();
    HEX_close();

    return 0;
}
