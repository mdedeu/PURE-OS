// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "time.h"
#include "libc.h"
#include "shell.h"
#include "system.h"

int getSeconds() { return sys_time(SECONDS); }

int getMinutes() { return sys_time(MINUTES); }

int getHours() { return sys_time(HOURS); }

int getDay() { return sys_time(DAY); }

int getMonth() { return sys_time(MONTH); }

int getYear() { return sys_time(YEAR); }

void printTime(int number) {
  char buffer[3] = {0};
  buffer[0] = number / 10 + '0';
  buffer[1] = number % 10 + '0';
  buffer[2] = '\0';
  addText(buffer);
}

void time() {
  printTime(getDay());
  addText("/");
  printTime(getMonth());
  addText("/");
  printTime(getYear());
  addText(" ");
  printTime(getHours());
  addText(":");
  printTime(getMinutes());
  addText(":");
  printTime(getSeconds());
  printWindow();
  substractLine();
}