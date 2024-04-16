#include <stdio.h>

int getRowPosition(int index)
{
    return 24 - (8 * index);
}

int getColPosition(int index)
{
    return 12 * index;
}

void breakRowInBlock(void)
{
    printf("\033[1B");
    printf("\033[11D");
}

void moveCursor(int up, int right)
{
    printf("\033[%dA", up);
    if (right)
        printf("\033[%dC", right);
}

void fixPosition(int row)
{
    int i;

    for (i = 0; i < (row - 7); i++)
    {
        printf("\n");
    }
}

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
    draw(posX, posY, drawing);
}

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
    draw(posX, posY, drawing);
}

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
