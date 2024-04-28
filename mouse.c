#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "mouse.h"

#define EVENT_FILE "/dev/input/mice"

int fd;

void openMouse()
{
    fd = open(EVENT_FILE, O_RDWR);
    if (fd == -1)
    {
        printf("ERROR Opening %s\n", EVENT_FILE);
    }
}

input_mouse readMouse()
{
    int bytes;
    int8_t data[3];
    input_mouse mouse;

    bytes = read(fd, data, sizeof(data));

    if (bytes > 0)
    {
        mouse.click = data[0] & 0x1;
        mouse.x = data[1];
        mouse.y = data[2];
    }

    return mouse;
}

void closeMouse()
{
    close(fd);
}