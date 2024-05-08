/**
 * @file mouse.h
 * @brief Lib that defines the structure and functions for obtaining mouse input.
 */
#ifndef MOUSE_H
#define MOUSE_H

#include <stdint.h>

/**
 * @brief Input mouse data.
 */
typedef struct
{
  int32_t x;    /**< Horizontal mouse movement value. */
  int32_t y;    /**< Vertical mouse movement value. */
  int8_t click; /**< Stores right mouse button click value. */
} input_mouse;

/**
 * @brief Function to open mice input file, enabling data reading.
 */
void openMouse();

/**
 * @brief Function to read mouse input data.
 *
 * @return input_mouse
 */
input_mouse readMouse();

/**
 * @brief Function to close mice input file.
 */
void closeMouse();

#endif /*MOUSE_H*/
