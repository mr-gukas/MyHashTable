#pragma once

#include "../include/textutils.hpp"
#include "../include/hashfunc.hpp"
#include "../include/list.hpp"

const size_t table_size = 500;
const size_t list_size  = 12;

struct hashtable_t 
{
    word_t* words;
    list_t* lists;     
};

int hashtableCtor(hashtable_t* hashtable, word_t* words);
int hashtableDtor(hashtable_t* hashtable);
