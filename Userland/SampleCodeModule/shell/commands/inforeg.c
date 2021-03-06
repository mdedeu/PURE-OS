// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "inforeg.h"
#include "libc.h"
#include "shell.h"
#include <stdint.h>

uint64_t _getRegs();

static char *regsNames[] = {
    "RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RDI: ",
    "RSI: ", "R8: ",  "R9: ",  "R10: ", "R11: ", "R12: ",
    "R13: ", "R14: ", "R15: ", "RSP: ", "RIP: "};

void inforeg() {
  uint64_t *regs = (uint64_t *)_getRegs();

  char bufferAux[20];

  for (int i = 0; i < 17; i++) {
    if (i % 3 == 0 && i != 0)
      substractLine();
    addText(regsNames[i]);
    addText("0x");
    addText(gtoa(regs[i], bufferAux, 16, 20));
    if (i != 14 && i % 3 != 2)
      addText(" - ");
  }
  printWindow();
  substractLine();
}