#include "../include/hashtable.hpp"

extern "C" unsigned int rolHash_asm(const char* str);

int hashtableFill  (hashtable_t* hashtable, hashtable_state_t* state) {
  if (!(hashtable && state))
    return 1;

  hashtable->isReset = 0;
  
  for (size_t index = 0; index < state->word_cnt - 1; index++) 
  {
    unsigned int hash = hashtable->hashfunc(hashtable->words[index].word_start) % table_size;

    if (hashtable->lists[hash].size == 0)
      ListCtor(&(hashtable->lists[hash]), list_size);

    if (findinTable(hashtable, hashtable->words[index].word_start) == 0)
    {
      if (state->isProcessed == 0) 
      {
        fprintf(state->words_list, "%-31s",
                hashtable->words[index].word_start);
        fprintf(state->words_list, "\n");
      }

      ListInsertTail(&(hashtable->lists[hash]),
                     hashtable->words[index].word_start);
    }
  }

  state->isProcessed = 1;

  return 0;
}


int findinTable(hashtable_t *hashtable, const char *word) {
  if (!(hashtable && word))
    return -1;

  unsigned int hash = hashtable->hashfunc(word) % table_size;
  findinList(&hashtable->lists[hash], word);
  for (size_t index = 0; index <= hashtable->lists[hash].size; index++)
  {
    if (hashtable->lists[hash].data[index].value && 
        avx2_strcmp(word, hashtable->lists[hash].data[index].value) == 0)
        return 1;
  }
  
  return 0;
}

inline int findinList(list_t* list, const char* word) {
  if (!(list && word))
    return -1;

  for (size_t index = 0; index <= list->size; index++)
  {
    if (list->data[index].value && 
        avx2_strcmp(word, list->data[index].value) == 0)
        return 1;
  }

  return 0;
}


int hashtableStat  (hashtable_t* hashtable, hashtable_state_t* state) {
  if (!(hashtable && hashtable->lists))
    return 1;

  for (size_t index = 0; index < table_size; index++)
    fprintf(state->output, "%lu\t%lu\n", index,
            hashtable->lists[index].size);

  fprintf(state->output, "\n");

  return 0;
}

int hashtableReset(hashtable_t *hashtable) {
  if (!hashtable)
    return 1;

  for (size_t index = 0; index < table_size; index++)
    if (hashtable->lists[index].data != nullptr)
      ListDtor(&hashtable->lists[index]);

  hashtable->isReset = 1;

  return 0;
}

int hashtableCtor  (hashtable_t* hashtable, text_t* data, hashtable_state_t* state) {
  if (!(hashtable && data && state))
    return 1;

  hashtable->words    = data->words;
  state->word_cnt     = data->word_cnt;
  hashtable->hashfunc = &avx_crc32;

  hashtable->lists = (list_t *)calloc(table_size, sizeof(list_t));
  if (hashtable->lists == nullptr)
    return 1;

  state->output = fopen("../data/output.csv", "w");
  //hashtable->words_list = fopen("../data/wordlist.txt", "w+");

  return 0;
}

int hashtableDtor(hashtable_t* hashtable, hashtable_state_t* state) {
  if (!(hashtable && state))
    return 1;

  if (!hashtable->isReset)
    hashtableReset(hashtable);

  free(hashtable->lists);

  fclose(state->output);
  //fclose(hashtable->words_list);

  return 0;
}

int hashtableFinder(hashtable_t *hashtable, text_t *tests)
{
  if (!(hashtable && tests)) return 1;

  size_t index = 0;
  
  while (tests->words[index].word_start) {
    for (int i = 0; i < 500; i++) {
      unsigned int hash = avx_crc32(tests->words[index].word_start) % table_size;
      findinTable(hashtable, tests->words[index].word_start);
    }

    ++index;
  }
  
  return 0;
}

int asm_strcmp(const char* str1, const char* str2) 
{
    int res = 0;
    asm (
        ".intel_syntax noprefix;"
        "1: "
        "lodsb;"
        "scasb;"
        "jne 2f;"
        "test al, al;"
        "jne 1b;"
        "xor eax, eax;"
        "jmp 3f;"
        "2: "
        "dec edi;"
        "sbb eax, eax;"
        "3: "
        ".att_syntax" 
        : "=a" (res)
        : "S" (str1), "D" (str2)
        : "memory"
    );
    return res;
}

unsigned int avx_crc32(const char* str) {
    __m256i      data = _mm256_load_si256((__m256i*)str);
    unsigned int hash = _mm_crc32_u32(0, _mm256_extract_epi64(data, 0));

    hash = _mm_crc32_u32(hash, _mm256_extract_epi64(data, 1));
    hash = _mm_crc32_u32(hash, _mm256_extract_epi64(data, 2));
    hash = _mm_crc32_u32(hash, _mm256_extract_epi64(data, 3));
    return hash;
}

inline int avx2_strcmp(const char* str1, const char* str2) {
    __m256i a   = _mm256_load_si256((__m256i*)str1);
    __m256i b   = _mm256_load_si256((__m256i*)str2);
    __m256i cmp = _mm256_cmpeq_epi8(a, b);

    int mask = _mm256_movemask_epi8(cmp);
    
    return (mask == 0xffffffff) ? 0 : 1;
}

