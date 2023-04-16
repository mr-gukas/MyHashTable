#include "../include/hashfunc.hpp"


unsigned int getHash(const char* str, HASH_FUNC mode)
{
    if (!str) return -1;

    switch (mode)
    {
        case 1: return constHash (str);
        case 2: return firstAscii(str);
        case 3: return wordLen   (str);
        case 4: return sumAscii  (str);
        case 5: return rolHash   (str);
        case 6: return rorHash   (str);
        case 7: return pjwHash   (str);
        default: return -1;
    }
}

static unsigned int constHash(const char* str)
{
    return 1;
}

static unsigned int firstAscii(const char* str)
{
    return (unsigned int) str[0];
}

static unsigned int wordLen(const char* str)
{
    return strlen(str);
}

static unsigned int sumAscii(const char* str)
{
    unsigned int ascii_sum = 0;
    size_t       index     = 0;

    while (*(str + index))
    {
        ascii_sum += *((str + index++));
    }

    return ascii_sum;
}

static unsigned int my_ror(int num, int shift)
{
    return (num >> shift) | (num << (32 - shift));
}

static unsigned int my_rol(int num, int shift)
{
    return (num << shift) | (num >> (32 - shift));
}

static unsigned int rolHash(const char* str)
{
    unsigned int hash  = 0;
    size_t       index = 0;

    while (*(str + index))
    {
        hash = my_rol(hash, 1) ^ str[index++];
    }

    return hash;
}

static unsigned int rorHash(const char* str)
{
    unsigned int hash  = 0;
    size_t       index = 0;

    while (*(str + index))
    {
        hash = my_ror(hash, 1) ^ str[index++];
    }

    return hash;
}

static unsigned int pjwHash(const char* str)
{
    unsigned int hash = 0;
    unsigned int test = 0;

    size_t index = 0;
    while(*(str+index))
    {
        hash = (hash << 4) + (unsigned char) (*(str + index++));
    
        if ((test = hash & 0xF0000000) != 0)
            hash = ((hash ^ (test >> 24)) & (0xFFFFFFFF));
    }

    return hash;
}

