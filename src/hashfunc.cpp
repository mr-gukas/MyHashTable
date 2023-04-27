#include "../include/hashfunc.hpp"

unsigned int constHash(const char* str)
{
    return 1;
}

unsigned int firstAscii(const char* str)
{
    return (unsigned int) str[0];
}

unsigned int wordLen(const char* str)
{
    return strlen(str);
}

unsigned int sumAscii(const char* str)
{
    unsigned int ascii_sum = 0;
    size_t       index     = 0;

    while (*(str + index))
    {
        ascii_sum += *((str + index++));
    }

    return ascii_sum;
}

unsigned int my_ror(int num, int shift)
{
    return (num >> shift) | (num << (32 - shift));
}

unsigned int my_rol(int num, int shift)
{
    return (num << shift) | (num >> (32 - shift));
}

unsigned int rolHash(const char* str)
{
    unsigned int hash  = 0;
    size_t       index = 0;

    while (*(str + index))
    {
        hash = my_rol(hash, 1) ^ str[index++];
    }

    return hash;
}

unsigned int rorHash(const char* str)
{
    unsigned int hash  = 0;
    size_t       index = 0;

    while (*(str + index))
    {
        hash = my_ror(hash, 1) ^ str[index++];
    }

    return hash;
}

unsigned int pjwHash(const char* str)
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

