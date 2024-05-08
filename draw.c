/**
 * @file draw.c
 * @brief Implementation of library for draw tic-tac-toe game in terminal.
 */
#include <stdio.h>

/**
 * @brief Get row starting position by index.
 *
 * @param index
 * @return int - Row starting position.
 */
int getRowPosition(int index)
{
    return 24 - (8 * index);
}

/**
 * @brief Get column starting position by index.
 *
 * @param index
 * @return int - Column starting position.
 */
int getColPosition(int index)
{
    return 12 * index;
}

/**
 * @brief Auxiliary function to move cursor to start position in bass line.
 */
void breakRowInBlock(void)
{
    printf("\033[1B");
    printf("\033[11D");
}

/**
 * @brief Auxiliary function to move cursor to desired position.
 *
 * @param up How many lines should the cursor go up.
 * @param right How many characters should the cursor shift to the right.
 */
void moveCursor(int up, int right)
{
    printf("\033[%dA", up);
    if (right)
        printf("\033[%dC", right);
}

/**
 * @brief Auxiliary function to return the cursor to the final position of the board in the terminal.
 *
 * @param row Initial position the drawing was made.
 */
void fixPosition(int row)
{
    int i, currentPosition = row - 7;

    for (i = 0; i < currentPosition; i++)
    {
        printf("\n");
    }
}

/**
 * @brief Function to draw a board 3X3.
 */
void drawBoard(void)
{
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("███████████████████████████████████\n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("███████████████████████████████████\n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("           █           █           \n");
    printf("\n");
}

/**
 * @brief Auxiliary function with logic to draw in a block.
 *
 * @param posX Horizontal position, from 0 to 2.
 * @param posY Vertical position, from 0 to 2.
 * @param drawing Drawing that will be made in the defined block.
 */
void draw(int posX, int posY, char drawing[7][500])
{
    int row = getRowPosition(posX);
    int col = getColPosition(posY);
    int i;

    moveCursor(row, col);
    for (i = 0; i < 7; i++)
    {
        printf("%s", drawing[i]);
        breakRowInBlock();
    }
    fixPosition(row);
}

/**
 * @brief Function to draw X in a specific position.
 *
 * @param posX Horizontal position, from 0 to 2.
 * @param posY Vertical position, from 0 to 2.
 */
void drawX(int posX, int posY)
{
    char drawing[7][500] = {
        "\033[11C",
        "\033[2C██\033[3C██\033[2C",
        "\033[3C██\033[1C██\033[3C",
        "\033[4C███\033[4C",
        "\033[3C██\033[1C██\033[3C",
        "\033[2C██\033[3C██\033[2C",
        "\033[11C",
    };
    printf("\033[31m");
    draw(posX, posY, drawing);
    printf("\033[0m");
}

/**
 * @brief Function to draw O in a specific position.
 *
 * @param posX Horizontal position, from 0 to 2.
 * @param posY Vertical position, from 0 to 2.
 */
void drawO(int posX, int posY)
{
    char drawing[7][500] = {
        "\033[11C",
        "\033[3C█████\033[3C",
        "\033[2C██\033[3C██\033[2C",
        "\033[2C██\033[3C██\033[2C",
        "\033[2C██\033[3C██\033[2C",
        "\033[3C█████\033[3C",
        "\033[11C",
    };
    printf("\033[34m");
    draw(posX, posY, drawing);
    printf("\033[0m");
}

/**
 * @brief Function to draw a dark block in a specific position.
 *
 * @param posX Horizontal position, from 0 to 2.
 * @param posY Vertical position, from 0 to 2.
 */
void drawBlock(int posX, int posY)
{
    char drawing[7][500] = {
        "░░░░░░░░░░░",
        "░░░░░░░░░░░",
        "░░░░░░░░░░░",
        "░░░░░░░░░░░",
        "░░░░░░░░░░░",
        "░░░░░░░░░░░",
        "░░░░░░░░░░░"};
    draw(posX, posY, drawing);
}

/**
 * @brief Function to clean block in a specific position, removing all non-empty characters from the block.
 *
 * @param posX Horizontal position, from 0 to 2.
 * @param posY Vertical position, from 0 to 2.
 */
void cleanBlock(int posX, int posY)
{
    char drawing[7][500] = {
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           "};
    draw(posX, posY, drawing);
}
