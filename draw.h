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
 * @brief Function to draw X in a specific position
 *
 * @param posX Horizontal position, from 0 to 2
 * @param posY Vertical position, from 0 to 2
 */
void drawX(int posX, int posY);

/**
 * @brief Function to draw O in a specific position
 *
 * @param posX Horizontal position, from 0 to 2
 * @param posY Vertical position, from 0 to 2
 */
void drawO(int posX, int posY);

/**
 * @brief Function to draw a dark block in a specific position
 *
 * @param posX Horizontal position, from 0 to 2
 * @param posY Vertical position, from 0 to 2
 */
void drawBlock(int posX, int posY);

/**
 * @brief Function to clean block in a specific position, removing all non-empty characters from the block
 *
 * @param posX Horizontal position, from 0 to 2
 * @param posY Vertical position, from 0 to 2
 */
void cleanBlock(int posX, int posY);

#endif /*DRAW_H*/
