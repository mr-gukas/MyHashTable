#include "../include/hashtable.hpp"


int hashtableFill(hashtable_t* hashtable, HASH_FUNC mode)
{
    if (!hashtable) return 1;
    
    hashtable->isReset = 0;

    for (size_t index = 0; index < hashtable->word_cnt; index++)
    {
        unsigned int hash = getHash(hashtable->words[index].word_start, mode) % table_size;

        if (hashtable->lists[hash].size == 0)
            ListCtor(&(hashtable->lists[hash]), list_size);
        
        if  (findinTable(hashtable, hashtable->words[index].word_start, hash) == 0)  
            ListInsertTail(&(hashtable->lists[hash]), hashtable->words[index].word_start);
    }

    return 0;
}

int findinTable(hashtable_t* hashtable, const char *word, unsigned int hash)
{
    if (!(hashtable && word)) return -1;
    
    for (size_t index = 0; index < hashtable->lists[hash].size; index++)
    {
        if (hashtable->lists[hash].data[index].value && 
            strcmp(word, hashtable->lists[hash].data[index].value) == 0)
            return 1;
    }

    return 0;
}

int hashtableStat(hashtable_t* hashtable)
{
    if (!(hashtable && hashtable->lists)) return 1;
    
    for (size_t index = 0; index < table_size; index++)
        fprintf(hashtable->output, "%lu\t%lu\n", index, hashtable->lists[index].size);

    fprintf(hashtable->output, "\n");

    return 0;
}

int hashtableReset(hashtable_t* hashtable)
{
    if (!hashtable) return 1;

    for (size_t index = 0; index < table_size; index++)
        if (hashtable->lists[index].data != nullptr)
            ListDtor(&hashtable->lists[index]);

    hashtable->isReset = 1;

    return 0;
}

int hashtableCtor(hashtable_t* hashtable, word_t* words, size_t word_cnt)
{
    if (!(hashtable && words)) return 1;

    hashtable->words    = words;
    hashtable->word_cnt = word_cnt; 

    hashtable->lists = (list_t*) calloc(table_size, sizeof(list_t));
    if (hashtable->lists == nullptr) 
        return 1;
    
    hashtable->output = fopen("../data/output.csv", "w");

    return 0;
}



int hashtableDtor(hashtable_t* hashtable)
{
    if (!hashtable) return 1;
    
    if (!hashtable->isReset)
        hashtableReset(hashtable);

    free(hashtable->lists); 

    fclose(hashtable->output);

    return 0;
}
