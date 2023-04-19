#include "../include/hashtable.hpp"


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "expected: the name of the file with the text to be processed\n");
        return 1;
    }
    
    FILE* source_txt = 0;

    if ((source_txt = fopen(argv[1], "r")) == nullptr)
    {
        fprintf(stderr, "incorrect data input\n");
        return 1;
    }
	
    text_t text = {};
    textCtor(&text, source_txt);
         
    hashtable_t hashtable = {};
    hashtableCtor(&hashtable, text.words, text.word_cnt);
  
    for (int hash_mode = 1; hash_mode <= 7; hash_mode++)
    {
        hashtableFill (&hashtable, (HASH_FUNC) hash_mode);    
        hashtableStat (&hashtable);
        hashtableReset(&hashtable);
    }
 
    hashtableDtor(&hashtable);
    textDtor     (&text);
    fclose       (source_txt);

    return 0;
}
