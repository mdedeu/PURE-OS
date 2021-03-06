#ifndef LIBC
#define LIBC

#include "system.h"

void winClear();
void printString(char *string);
void printStringError(char *string);
void new_line();
char getChar();
int abs();
int atoi(char *buffer, int len);
void strcpy2(char *str1, char *str2);
int Stringlen(const char *s);
void scanf(char *buffer, int maxLen);
int strcmp(const char *s1, const char *s2);
char *itoa(int value, char *buffer, int base);
char isFloat(char *str);
float atof(char *arr);
char *strtokLib(char *s, char delim);
char isNumber(char c);
char *gtoa(int value, char *buffer, int base, int length);
char *reverse(char *buffer, int i, int j);
int pow(int base, int exponent);
char *strstrip(char *s, char c);
void ftoa(double f, char *buf, int precision);

#endif