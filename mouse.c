/**
 * @file mouse.c
 * @brief Implementation of mouse input data reading library.
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "mouse.h"

/** File with data from all connected mice */
#define EVENT_FILE "/dev/input/mice"

/** File descriptor */
int fd;

/**
 * @brief Function to open mice input file, enabling data reading.
 */
void openMouse()
{
    fd = open(EVENT_FILE, O_RDWR);
    if (fd == -1)
    {
        printf("ERROR Opening mice input file %s\n", EVENT_FILE);
    }
}

/**
 * @brief Function to read mouse input data.
 *
 * @return input_mouse
 */
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

/**
 * @brief Function to close mice input file.
 */
void closeMouse()
{
    close(fd);
}