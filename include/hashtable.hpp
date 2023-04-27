#pragma once

#include "../include/textutils.hpp"
#include "../include/hashfunc.hpp"
#include "../include/list.hpp"
#include <string.h>
#include <cstdint> 
#include <immintrin.h>
#include <stdint.h>

const size_t table_size = 1000;
const size_t list_size  = 12;

struct hashtable_t 
{
    word_t* words;
    list_t* lists;     
    hash_t  hashfunc;
    
    int     isReset;
};

struct hashtable_state_t
{
    size_t word_cnt;
    FILE*  output;
    FILE*  words_list;
    int    isReset;
    int    isProcessed;
};

int hashtableCtor  (hashtable_t* hashtable, text_t* data, hashtable_state_t* state);
int hashtableDtor  (hashtable_t* hashtable, hashtable_state_t* state);
int hashtableFill  (hashtable_t* hashtable, hashtable_state_t* state);
int hashtableStat  (hashtable_t* hashtable, hashtable_state_t* state);
int hashtableReset (hashtable_t* hashtable);
int findinTable    (hashtable_t* hashtable, const char* word);
inline int findinList     (list_t*      list,      const char* word);
int hashtableFinder(hashtable_t* hashtable, text_t* tests);
int avx2_strcmp(const char* str1, const char* str2); 
int asm_strcmp(const char* str1, const char* str2);
inline unsigned int avx_crc32(const char* str);

