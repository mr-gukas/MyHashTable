#pragma once

#include "../include/textutils.hpp"
#include "../include/hashfunc.hpp"
#include "../include/list.hpp"
#include <string.h>

const size_t table_size = 500;
const size_t list_size  = 12;

struct hashtable_t 
{
    word_t* words;
    size_t  word_cnt;
    list_t* lists;     
    FILE*   output;
    int     isReset;
};

int hashtableCtor (hashtable_t* hashtable, word_t* words, size_t word_cnt);
int hashtableDtor (hashtable_t* hashtable);
int hashtableFill (hashtable_t* hashtable, HASH_FUNC mode);
int hashtableStat (hashtable_t* hashtable);
int hashtableReset(hashtable_t* hashtable);
int findinTable   (hashtable_t* hashtable, const char* word, unsigned int hash);

