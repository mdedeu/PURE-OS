// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include "video.h"
#include "keyboard.h"
#include "time.h"
#include "pcb.h"

#define STDOUT 1
#define STDERR 2

#define STDOUT_COLOR 0x0f
#define STDERR_COLOR 0x04 

uint64_t write(uint64_t fd, uint64_t buffer, uint64_t length) {
    char * bufferAux = (char *) buffer;
    int color;

    if (fd == STDOUT)
        color = STDOUT_COLOR;
    else if (fd == STDERR)
        color = STDERR_COLOR;

    return printStringLen(color, bufferAux, (int) length);
}

uint64_t read(uint64_t fd, uint64_t buffer, uint64_t length) {
    char * bufferAux = (char *) buffer;
    int readBytes = 0;

    while (length-- > 0) {
        *bufferAux = getKeyFromBuffer();
        if (*bufferAux == 0)
            break;
        readBytes++;
        bufferAux++;
    }

	return readBytes;
}

int createProcess(void (*entryPoint)(int, char **), int argc, char **argv, int fg, int fd[2]) {
    return addProcess(entryPoint, argc, argv, fg, fd, argv[0]);
}
