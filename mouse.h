#ifndef MOUSE_H
#define MOUSE_H

#include <sys/time.h>
#include <stdint.h>

struct input_event
{
    struct timeval time;
    uint16_t type;
    uint16_t code;
    int32_t value;
};

#define EV_KEY 0x01
#define EV_REL 0x02

#define REL_X 0x00
#define REL_Y 0x01

input_event readData(void);

#endif /*MOUSE_H*/
