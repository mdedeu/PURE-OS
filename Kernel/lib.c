// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "lib.h"
#include <stdint.h>

void *memset(void *destination, int32_t c, uint64_t length) {
  uint8_t chr = (uint8_t)c;
  char *dst = (char *)destination;

  while (length--)
    dst[length] = chr;

  return destination;
}

void *memcpy(void *destination, const void *source, uint64_t length) {
  /*
   * memcpy does not support overlapping buffers, so always do it
   * forwards. (Don't change this without adjusting memmove.)
   *
   * For speedy copying, optimize the common case where both pointers
   * and the length are word-aligned, and copy word-at-a-time instead
   * of byte-at-a-time. Otherwise, copy by bytes.
   *
   * The alignment logic below should be portable. We rely on
   * the compiler to be reasonably intelligent about optimizing
   * the divides and modulos out. Fortunately, it is.
   */
  uint64_t i;

  if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
      (uint64_t)source % sizeof(uint32_t) == 0 &&
      length % sizeof(uint32_t) == 0) {
    uint32_t *d = (uint32_t *)destination;
    const uint32_t *s = (const uint32_t *)source;

    for (i = 0; i < length / sizeof(uint32_t); i++)
      d[i] = s[i];
  } else {
    uint8_t *d = (uint8_t *)destination;
    const uint8_t *s = (const uint8_t *)source;

    for (i = 0; i < length; i++)
      d[i] = s[i];
  }

  return destination;
}

void swap(char *x, char *y) {
  char t = *x;
  *x = *y;
  *y = t;
}

char *reverse(char *buffer, int i, int j) {
  while (i < j) {
    swap(&buffer[i++], &buffer[j--]);
  }

  return buffer;
}

int abs(int value) { return value < 0 ? -value : value; }

char *itoa(int value, char *buffer, int base, int length) {
  if (base < 2 || base > 32) {
    return buffer;
  }

  int n = abs(value);
  int i = 0;
  while (n && i < length) {
    int r = n % base;

    if (r >= 10) {
      buffer[i++] = 65 + (r - 10);
    } else {
      buffer[i++] = 48 + r;
    }

    n = n / base;
  }

  if (i == 0) {
    buffer[i++] = '0';
  }

  if (value < 0 && base == 10) {
    buffer[i++] = '-';
  }

  buffer[i] = '\0';
  return reverse(buffer, 0, i - 1);
}
void strcpy(char *str1, char *str2) { // copies str1 into str2
  int i;
  for (i = 0; str1[i] != 0; i++)
    str2[i] = str1[i];
  str2[i] = 0;
}
int Stringlen(const char *s) {
  int i = 0;
  for (i = 0; s[i] != '\0'; i++)
    ;
  return i;
}

char *strcat(char *strg1, char *strg2) {
  char *start = strg1;
  while (*strg1 != '\0') {
    strg1++;
  }
  while (*strg2 != '\0') {
    *strg1 = *strg2;
    strg1++;
    strg2++;
  }
  *strg1 = '\0';
  return start;
}

void acquire(int *mutex) {
  while (_xchg(mutex, 1) != 0)
    ;
}

void release(int *mutex) { _xchg(mutex, 0); }

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}