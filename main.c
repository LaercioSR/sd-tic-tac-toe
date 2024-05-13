/**
 * @file tictactoe.c
 * @brief Main file
 */
#include <stdio.h>
#include <stdlib.h>
#include <intelfpgaup/KEY.h>
#include <intelfpgaup/HEX.h>
#include "draw.h"
#include "mouse.h"

#define SIZE_BOARD 3
#define SIZE_BLOCK 150

/**
 * @brief Function to highlight winning positions.
 *
 * @param positions Winning positions.
 * @param player Winner player character.
 */
void drawWinLine(int positions[3][2], char player)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        drawBlock(positions[i][0], positions[i][1]);
        if (player == 'X')
        {
            drawX(positions[i][0], positions[i][1]);
        }
        else
        {
            drawO(positions[i][0], positions[i][1]);
        }
    }
}

/**
 * @brief Function to check condition of winning.
 *
 * @param board Board game.
 * @param player Character of current player.
 * @return int
 */
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
        if (isWinnerRow)
        {
            int line[3][2] = {{i, 0}, {i, 1}, {i, 2}};
            drawWinLine(line, player);
            return 1;
        }
        else if (isWinnerCol)
        {
            int line[3][2] = {{0, i}, {1, i}, {2, i}};
            drawWinLine(line, player);
            return 1;
        }
    }

    if (isWinnerDiag1)
    {
        int line[3][2] = {{0, 0}, {1, 1}, {2, 2}};
        drawWinLine(line, player);
        return 1;
    }
    else if (isWinnerDiag2)
    {
        int line[3][2] = {{0, 2}, {1, 1}, {2, 0}};
        drawWinLine(line, player);
        return 1;
    }

    return 0;
}

/**
 * @brief Function to handle position change
 *
 * @param board Board game.
 * @param row New row position.
 * @param col New column position.
 * @param lastRow Last row position.
 * @param lastCol Last column position.
 */
void changePosition(char board[SIZE_BOARD][SIZE_BOARD], int row, int col, int lastRow, int lastCol)
{
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

/**
 * @brief Function to show winner in display.
 *
 * @param player Character of current player.
 */
void showWinner(int player)
{
    /*              6543210 6543210*/
    int data_h = 0b0111001100111000;
    /*                            6543210 6543210 6543210 6543210*/
    int data_l = player == 1 ? 0b01110111011011100000000000000110
                             : 0b01110111011001100000000001011011;

    HEX_raw(data_h, data_l);
}

/**
 * @brief Function to handle game finish.
 */
void finishGame(void)
{
    closeMouse();
    KEY_close();
    HEX_close();
}

/**
 * @brief Main function
 *
 * @return int
 */
int main(void)
{
    char board[SIZE_BOARD][SIZE_BOARD] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    char playerValue;
    int buttonState = 0;
    int maxBoardSize = SIZE_BLOCK * 3 - 1;
    int numPlays = 0, row = 0, col = 0, qttClick = 0;
    int isWinner = 0;
    int startGame = 0;
    int flagFinish = 0;
    int x = 1;
    int y = 1;

    /* Open devices */
    openMouse();
    KEY_open();
    HEX_open();

    system("clear");
    while (!flagFinish)
    {
        printf("Press button 1 to start the game\n");
        printf("Press button 2 to end the game\n");
        while (!buttonState)
        {
            if (!KEY_read(&buttonState))
            {
                printf("ERROR to read push button state.\n");
            }

            if (buttonState == 1)
            {
                startGame = buttonState;
            }
            else if (buttonState == 2)
            {
                flagFinish = 1;
            }
        }
        printf("\033[3A");

        buttonState = 0;
        system("clear");
        if (startGame)
        {
            startGame = 0;
            HEX_raw(0, 0);
            drawBoard();
            drawBlock(row, col);

            while ((numPlays < 9) && !isWinner)
            {
                int player = numPlays % 2 + 1;
                int playerSegments = player == 1 ? 0b00000000000000000000000000000110
                                                 : 0b00000000000000000000000001011011;
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
                                    printf("Player %d is winner!!!\n\n", player);
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
                printf("GAME DRAW!!!\n\n");
            }

            /* Reset Game */
            numPlays = 0, row = 0, col = 0;
            isWinner = 0;
            x = 1;
            y = 1;

            int i, j;
            for (i = 0; i < SIZE_BOARD; i++)
            {
                for (j = 0; j < SIZE_BOARD; j++)
                {
                    board[i][j] = ' ';
                }
            }
        }
        else
        {
            HEX_raw(0b0, 0b0);
            finishGame();
        }
    }

    return 0;
}
