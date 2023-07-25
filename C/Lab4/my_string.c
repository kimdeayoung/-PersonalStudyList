#include "my_string.h"

size_t get_string_length(const char* str)
{
    const char* ptr = str;

    while (*ptr++ != '\0') {
    }

    return ptr - str - 1;
}

void reverse(char* str)
{
    size_t str_length = get_string_length(str);
    reverse_by_length(str, str_length);
}

int index_of(const char* str, const char* word)
{
    const char* str_ptr = str;

    size_t loop_index;
    size_t loop_count;
    unsigned int is_find;

    size_t word_find_index = 0;
    size_t word_length = get_string_length(word);
    loop_count = get_string_length(str) - word_length + 1;

    if (word_length == 0) {
        return 0;
    }

    for (loop_index = 0; loop_index < loop_count; ++loop_index) {
        is_find = TRUE;
        for (word_find_index = 0; word_find_index < word_length; ++word_find_index) {
            if (*(str_ptr + loop_index + word_find_index) != *(word + word_find_index)) {
                is_find = FALSE;
                break;
            }
        }
        if (is_find == TRUE) {
            return loop_index;
        }
    }

    return -1;
}

void reverse_by_length(char* str, const size_t str_length)
{
    char* ptr1;
    char* ptr2;

    size_t loop_index;
    size_t loop_count;

    loop_count = str_length / 2;

    for (loop_index = 0; loop_index < loop_count; ++loop_index) {
        ptr1 = str + loop_index;
        ptr2 = str + str_length - loop_index - 1;

        *ptr1 = *ptr1 ^ *ptr2;
        *ptr2 = *ptr1 ^ *ptr2;
        *ptr1 = *ptr1 ^ *ptr2;
    }
}

void reverse_by_words(char* str)
{
    char* ptr = str;

    size_t reverse_str_length = 0;

    while (*ptr != '\0') {
        if (*ptr == ' ') {
            reverse_by_length(ptr - reverse_str_length, reverse_str_length);
            reverse_str_length = 0;
        } else {
            ++reverse_str_length;
        }
        ++ptr;
    }
    reverse_by_length(ptr - reverse_str_length, reverse_str_length);
}

char* tokenize(char* str_or_null, const char* delims)
{
    static char* s_tokenize_str = NULL;
    unsigned int is_find_delims;
    unsigned int find_delims_count = 0;

    size_t token_size = 0;

    const char* delims_ptr;

    if (str_or_null == NULL) {
        if (s_tokenize_str == NULL) {
            return NULL;
        }
    } else {
        s_tokenize_str = str_or_null;
    }

    while (*s_tokenize_str != '\0') {
        is_find_delims = FALSE;
        delims_ptr = delims;
        
        while (*delims_ptr != '\0') {
            if (*s_tokenize_str == *delims_ptr++) {
                is_find_delims = TRUE;
                if (find_delims_count++ == 0) {
                    *s_tokenize_str = '\0';
                }
                break;
            }
        }

        if (find_delims_count > 0 && is_find_delims == FALSE) {
            if (find_delims_count == token_size) {
                find_delims_count = 0;
                token_size = 0;
            } else {
                return s_tokenize_str - token_size;
            }
        }

        ++s_tokenize_str;
        ++token_size;
    }

    if (token_size > 0) {
        return s_tokenize_str - token_size;
    }

    return NULL;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* tokenize_str = tokenize(str_or_null, delims);
    if (tokenize_str == NULL) {
        return NULL;
    }

    reverse(tokenize_str);
    return tokenize_str;
}
