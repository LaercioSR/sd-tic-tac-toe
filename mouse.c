#include "mouse.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

input_event readData(void)
{
    input_event event;
    int fileInput = open("/dev/input/event14", O_RDONLY);

    ssize_t bytes = read(fileInput, &event, sizeof(event));
    if (bytes == -1)
    {
        perror("Erro ao ler o evento");
        close(fileInput);
        return 1;
    }
    else if (bytes != sizeof(event))
    {
        fprintf(stderr, "Ler tamanho incorreto do evento\n");
        close(fileInput);
        return 1;
    }

    return event;
}