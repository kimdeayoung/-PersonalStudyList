#include "tokenize.h"
#include <string.h>
#include <stdlib.h>

char** tokenize_malloc(const char* str, const char* delim)
{
    char** pa_tokenize_strings;
    char** pa_tokenize_strings_ptr;
    
    size_t tokenize_strings_length = INIT_TOKENIZE_STRINGS_LENGTH;
    
    char* pa_tokenize_string;
    
    const char* str_ptr;
    const char* tokenize_start_ptr;
    size_t token_length;
    
    const char* delim_ptr;
    const char* find_delim_ptr = NULL;
    int is_find_delim;
    
    str_ptr = str;
    while (*str_ptr != '\0') {
        delim_ptr = delim;
        is_find_delim = FALSE;
        
        while (*delim_ptr != '\0') {
            if (*str_ptr == *delim_ptr) {
                if (find_delim_ptr == NULL) {
                    find_delim_ptr = str_ptr;
                }
                is_find_delim = TRUE;
                break;
            }
            ++delim_ptr;
        }
        
        if (find_delim_ptr != NULL && is_find_delim == FALSE) {
            ++tokenize_strings_length;
            find_delim_ptr = NULL;
        }
        ++str_ptr;
    }
    
    if (str == str_ptr) {
        pa_tokenize_strings = malloc(sizeof(char*));
        *pa_tokenize_strings = NULL;
        
        goto return_tokenize_strings;
    }
    
    pa_tokenize_strings = malloc(tokenize_strings_length * sizeof(char*));
    pa_tokenize_strings_ptr = pa_tokenize_strings;
    
    tokenize_start_ptr = str;
    find_delim_ptr = NULL;
    
    if (tokenize_strings_length != INIT_TOKENIZE_STRINGS_LENGTH) {
        str_ptr = str;
        while (*str_ptr != '\0') {
            delim_ptr = delim;
            is_find_delim = FALSE;
            
            while (*delim_ptr != '\0') {
                if (*str_ptr == *delim_ptr) {
                    if (find_delim_ptr == NULL) {
                        find_delim_ptr = str_ptr;
                    }
                    is_find_delim = TRUE;
                    break;
                }
                ++delim_ptr;
            }
            
            if (find_delim_ptr != NULL && is_find_delim == FALSE) {
                token_length = find_delim_ptr - tokenize_start_ptr;
                pa_tokenize_string = malloc((token_length + 1) * sizeof(char));
                memcpy(pa_tokenize_string, tokenize_start_ptr, token_length);
                *(pa_tokenize_string + token_length) = '\0';
                *pa_tokenize_strings_ptr++ = pa_tokenize_string;
                
                tokenize_start_ptr = str_ptr;
                find_delim_ptr = NULL;
            }
            ++str_ptr;
        }
    }
    
    {
        if (find_delim_ptr == NULL) {
            find_delim_ptr = str_ptr;
        }
        
        token_length = find_delim_ptr - tokenize_start_ptr;
        pa_tokenize_string = malloc((token_length + 1) * sizeof(char));
        memcpy(pa_tokenize_string, tokenize_start_ptr, token_length);
        *(pa_tokenize_string + token_length) = '\0';
        *pa_tokenize_strings_ptr++ = pa_tokenize_string; 
    }
    *pa_tokenize_strings_ptr = NULL;
    
return_tokenize_strings:
    return pa_tokenize_strings;
}
