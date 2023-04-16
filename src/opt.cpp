#include "../include/hashtable.hpp"
#include <time.h>


int main(void)
{
    FILE* tests_txt = {};
    if ((tests_txt = fopen("../data/wordlist.txt", "r")) == nullptr)
    {
        fprintf(stderr, "incorrect data input\n");
        return 1;
    }
	
    text_t tests = {};
    textCtor(&tests, tests_txt);

    tests.word_cnt--;
         
    hashtable_t hashtable = {};
    hashtableCtor(&hashtable, tests.words, tests.word_cnt);

    clock_t start, end = {};

    hashtableFill(&hashtable, ROL_HASH);
    hashtableReset(&hashtable);
    
    hashtable.isProcessed = 1;
    hashtableFill(&hashtable, ROL_HASH);

    start = clock();
    hashtableFinder(&hashtable, &tests, ROL_HASH);
    end   = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; 
    printf("Execution time: %lf seconds\n", cpu_time_used);

    hashtableDtor(&hashtable);
    textDtor     (&tests);
    fclose       (tests_txt);
  

    return 0;
}
