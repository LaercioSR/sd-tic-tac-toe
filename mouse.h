#ifndef MOUSE_H
#define MOUSE_H

#include <stdint.h>

typedef struct {
  int32_t x;
  int32_t y;
  int8_t click;
} input_mouse;

void openMouse();
input_mouse readMouse();
void closeMouse();

#endif /*MOUSE_H*/
