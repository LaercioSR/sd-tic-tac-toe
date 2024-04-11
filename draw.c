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

void changePosition(int up, int right)
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

void drawX(int posX, int posY)
{
    char drawing[7][500] = {
        "           ",
        "  ██   ██  ",
        "   ██ ██   ",
        "    ███    ",
        "   ██ ██   ",
        "  ██   ██  ",
        "           ",
    };
    int row = getRowPosition(posX);
    int col = getColPosition(posY);
    int i;

    changePosition(row, col);
    for (i = 0; i < 7; i++)
    {
        printf("%s", drawing[i]);
        breakRowInBlock();
    }
    fixPosition(row);
}

void drawO(int posX, int posY)
{
    char drawing[7][500] = {
        "           ",
        "   █████   ",
        "  ██   ██  ",
        "  ██   ██  ",
        "  ██   ██  ",
        "   █████   ",
        "           ",
    };
    int row = getRowPosition(posX);
    int col = getColPosition(posY);
    int i;

    changePosition(row, col);
    for (i = 0; i < 7; i++)
    {
        printf("%s", drawing[i]);
        breakRowInBlock();
    }
    fixPosition(row);
}
