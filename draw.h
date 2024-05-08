/**
 * @file draw.h
 * @brief Lib of functions to design the game in the terminal
 */
#ifndef DRAW_H
#define DRAW_H

/**
 * @brief Function to draw a board 3X3
 */
void drawBoard(void);

/**
 * @brief
 *
 * @param posX
 * @param posY
 */
void drawX(int posX, int posY);
void drawO(int posX, int posY);
void drawBlock(int posX, int posY);
void cleanBlock(int posX, int posY);

#endif /*DRAW_H*/
