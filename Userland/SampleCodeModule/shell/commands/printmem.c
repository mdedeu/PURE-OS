// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "inforeg.h"
#include "libc.h"
#include "shell.h"
#include <stdint.h>

int _getMem(int);

void getMem(int *buffer, int initialAddress) {
  int *bufferAux = (int *)buffer;

  for (int i = 0; i < 8; i++) {
    bufferAux[i] = (int)_getMem(initialAddress + (i * 4));
  }
}

void printmem(long dir) {
  int buffer[8];

  getMem(buffer, dir);

  for (int i = 0; i < 8; i++) {
    char bufferAux[8];
    addText("0x");
    addText(itoa(buffer[i], bufferAux, 16));
    substractLine();
  }
  printWindow();
}