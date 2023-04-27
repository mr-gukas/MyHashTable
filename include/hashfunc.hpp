#pragma once

#include <string.h>
typedef unsigned int (*hash_t)(const char*);

unsigned int constHash (const char* str);
unsigned int firstAscii(const char* str);
unsigned int wordLen   (const char* str);
unsigned int sumAscii  (const char* str);
unsigned int rolHash   (const char* str);
unsigned int rorHash   (const char* str);
unsigned int pjwHash   (const char* str);
unsigned int my_rol    (int num, int shift);
unsigned int my_ror    (int num, int shift);



