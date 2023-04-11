#pragma once

#include <string.h>

int getHash   (const char* str, int func_num);
static unsigned int constHash (const char* str);
static unsigned int firstAscii(const char* str);
static unsigned int wordLen   (const char* str);
static unsigned int sumAscii  (const char* str);
static unsigned int rolHash   (const char* str);
static unsigned int rorHash   (const char* str);
static unsigned int pjwHash   (const char* str);
static unsigned int my_rol    (int num, int shift);
static unsigned int my_ror    (int num, int shift);



