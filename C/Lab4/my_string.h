#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>

#define TRUE (1)
#define FALSE (0)

size_t get_string_length(const char* str);

void reverse(char* str);

void reverse_by_length(char* str, const size_t str_length);

int index_of(const char* str, const char* word);

void reverse_by_words(char* str);

char* tokenize(char* str_or_null, const char* delims);

char* reverse_tokenize(char* str_or_null, const char* delims);

#endif /* MY_STRING_H */
