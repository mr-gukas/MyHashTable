#pragma once

#include <string.h>

enum HASH_FUNC
{
    CONST_HASH = 1,
    FIRST_ASCII,
    WORD_LEN, 
    SUM_ASCII,
    ROL_HASH,
    ROR_HASH,
    PJW_HASH
};

unsigned int        getHash   (const char* str, HASH_FUNC mode);
static unsigned int constHash (const char* str);
static unsigned int firstAscii(const char* str);
static unsigned int wordLen   (const char* str);
static unsigned int sumAscii  (const char* str);
static unsigned int rolHash   (const char* str);
static unsigned int rorHash   (const char* str);
static unsigned int pjwHash   (const char* str);
static unsigned int my_rol    (int num, int shift);
static unsigned int my_ror    (int num, int shift);



