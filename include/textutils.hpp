#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct word_t 
{
    char*  word_start = NULL;///< a pointer on the begin of line
    size_t word_len   = 0;///< length of line
};

struct text_t
{
    char *  buf   = NULL;///<text
    size_t  nChar = 0;///<count of characters
    word_t* words = NULL;///<fileLines array
};

void textCtor(text_t* text, FILE* const source);
size_t fileSize(FILE* const file);
void countInText(char* buf, char search, size_t* count);
void readInBuf(text_t* text, FILE* source);
void matchWords(text_t* text);
void textDtor(text_t* text); 
