#pragma once 

#include "../include/hashtable.hpp"
#include <cstdlib>


int hashtableCtor(hashtable_t* hashtable, word_t* words)
{
    if (!(hashtable && words)) return 1;

    hashtable->words = words;

    hashtable->lists = (list_t*) calloc(table_size, sizeof(list_t));
    if (hashtable->lists == nullptr) 
        return 1;

    return 0;
}

int hashtableDtor(hashtable_t* hashtable)
{
    if (!hashtable) return 1;
    
    for (size_t index = 0; index < table_size; index++)
        if (hashtable->lists[index].data != nullptr)
            ListDtor(&hashtable->lists[index]);

    free(hashtable->lists);

    return 0;
}
