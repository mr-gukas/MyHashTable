#include "../include/hashtable.hpp"
#include <time.h>


int main(void) {
    FILE* data_txt = {};

    if ((data_txt = fopen("../data/all_words.txt", "r")) == nullptr) {
        fprintf(stderr, "incorrect data input\n");
        return 1;
    }
	
    text_t data = {};
    textCtor(&data, data_txt);

    hashtable_t       hashtable = {};
    hashtable_state_t state     = {};

    hashtableCtor(&hashtable, &data, &state);

    clock_t start, end = {};
   
    hashtable.isProcessed = 1;
    hashtableFill(&hashtable);
  
    FILE* tests_txt = {};
    
    if ((tests_txt = fopen("../data/all_words.txt", "r")) == nullptr)
    {
        fprintf(stderr, "incorrect data input\n");
        return 1;
    }
    text_t tests = {};
    textCtor(&tests, tests_txt);

    start = clock();
    hashtableFinder(&hashtable, &tests);
    end   = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; 
    printf("Execution time: %lf seconds\n", cpu_time_used);

    hashtableDtor(&hashtable);
    textDtor     (&tests);
    textDtor     (&data);
    fclose       (tests_txt);
  

    return 0;
}
