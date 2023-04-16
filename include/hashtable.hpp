#pragma once

#include "../include/textutils.hpp"
#include "../include/hashfunc.hpp"
#include "../include/list.hpp"
#include <string.h>

const size_t table_size = 1000;
const size_t list_size  = 12;

struct hashtable_t 
{
    word_t* words;
    size_t  word_cnt;
    size_t  non_repeating;
    list_t* lists;     
    FILE*   output;
    FILE*   words_list;

    int     isReset;
    int     isProcessed;
};

int hashtableCtor  (hashtable_t* hashtable, word_t* words, size_t word_cnt);
int hashtableDtor  (hashtable_t* hashtable);
int hashtableFill  (hashtable_t* hashtable, HASH_FUNC mode);
int hashtableStat  (hashtable_t* hashtable);
int hashtableReset (hashtable_t* hashtable);
inline int findinTable    (hashtable_t* hashtable, const char* word, unsigned int hash);
inline int avx2_findinTable(hashtable_t *hashtable, const char *word, unsigned int hash);
int hashtableFinder(hashtable_t* hashtable, text_t* tests,  HASH_FUNC mode);
int avx2_strcmp    (const char* str1, const char* str2); 

