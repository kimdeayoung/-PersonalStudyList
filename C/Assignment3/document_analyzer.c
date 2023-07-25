#include "document_analyzer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static char**** s_pa_document_data = NULL;

int load_document(const char* document)
{
    FILE* document_file;
    int load_result_value = FALSE;
    
    char line[LINE_LENGTH];
    
    size_t paragraph_length = INITILIZE_PARAGRAPH_LENGTH;
    char**** pa_paragraph_list_ptr;
    
    document_file = fopen(document, "r");
    if (document_file == NULL) {
        goto file_close_with_return;
    }
    
    if (s_pa_document_data != NULL) {
        dispose();
    }
    
    while (TRUE) {
        if (fgets(line, LINE_LENGTH, document_file) == NULL) {
            clearerr(document_file);
            break;
        }
        
        if (*line != '\n') {
            ++paragraph_length;
        }
    }
    
    if (paragraph_length == INITILIZE_PARAGRAPH_LENGTH) {
        load_result_value = TRUE;
        goto file_close_with_return;
    }
    rewind(document_file);
    
    s_pa_document_data = malloc(paragraph_length * sizeof(char*));
    pa_paragraph_list_ptr = s_pa_document_data;
    
    while (TRUE) {
        if (fgets(line, LINE_LENGTH, document_file) == NULL) {
            clearerr(document_file);
            break;
        }
        
        if (*line != '\n') {
            *pa_paragraph_list_ptr++ = create_paragraph_malloc(line, ".!?");
        }
    }
    *pa_paragraph_list_ptr = NULL;
    
    load_result_value = TRUE;
    
file_close_with_return:
    if (document_file != NULL) {
        if (fclose(document_file) != 0) {
            perror("file close error");
        }
    }

    return load_result_value;
}

void dispose(void)
{
    char* pa_word_ptr;
    char** pa_sentence_ptr;
    char*** pa_paragraph_ptr;
    char**** pa_document_data_ptr;
    
    if (s_pa_document_data != NULL) {
        pa_document_data_ptr = s_pa_document_data;
        
        while (*pa_document_data_ptr != NULL) {
            pa_paragraph_ptr = *pa_document_data_ptr;
            while (*pa_paragraph_ptr != NULL) {
                pa_sentence_ptr = *pa_paragraph_ptr;
                while (*pa_sentence_ptr != NULL) {
                    pa_word_ptr = *pa_sentence_ptr++;
                    free(pa_word_ptr);
                    pa_word_ptr = NULL;
                }
                
                pa_sentence_ptr = *pa_paragraph_ptr++;
                free(pa_sentence_ptr);
                pa_sentence_ptr = NULL;
            }
            
            pa_paragraph_ptr = *pa_document_data_ptr++;
            free(pa_paragraph_ptr);
            pa_paragraph_ptr = NULL;
        }
    }
    
    free(s_pa_document_data);
    s_pa_document_data = NULL;
}

unsigned int get_total_word_count(void)
{
    unsigned int word_count = 0;
    
    char**** pa_paragraph_list = s_pa_document_data;
    
    if (s_pa_document_data != NULL) {
        while (*pa_paragraph_list != NULL) {
            word_count += get_paragraph_word_count(*(const char****)pa_paragraph_list++);
        }
    }
    
    return word_count;
}

unsigned int get_total_sentence_count(void)
{
    unsigned int sentence_count = 0;
    
    char**** pa_paragraph_list = s_pa_document_data;
    
    if (s_pa_document_data != NULL) {
        while (*pa_paragraph_list != NULL) {
            sentence_count += get_paragraph_sentence_count(*(const char****)pa_paragraph_list++);
        }
    }
    
    return sentence_count;
}

unsigned int get_total_paragraph_count(void)
{
    unsigned int paragraph_count = 0;
    
    char**** pa_paragraph_list = s_pa_document_data;
    
    if (s_pa_document_data != NULL) {
        while (*pa_paragraph_list++ != NULL) {
            ++paragraph_count;
        }
    }
    
    return paragraph_count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
    const char*** paragraph = NULL;
    
    if (get_total_paragraph_count() > paragraph_index) {
        paragraph = *(const char****)(s_pa_document_data + paragraph_index);
    }
    
    return paragraph;
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
    unsigned int word_count = 0;
    
    const char** pa_word_list;
    
    while (*paragraph != NULL) {
        pa_word_list = *paragraph++;
        while (*pa_word_list++ != NULL) {
            ++word_count;
        }
    }
    
    return word_count;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
    unsigned int sentence_count = 0;
    
    while (*paragraph++ != NULL) {
        ++sentence_count;
    }
    
    return sentence_count;
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
    const char** sentence = NULL;
    const char*** paragraph = get_paragraph_or_null(paragraph_index);
    
    if (paragraph != NULL) {
        if (get_paragraph_sentence_count(paragraph) > sentence_index) {
            sentence = *(const char***)(paragraph + sentence_index);
        }
    }
    
    return sentence;
}

unsigned int get_sentence_word_count(const char** sentence)
{
    unsigned int word_count = 0;
    
    while (*sentence++ != NULL) {
        ++word_count;
    }
    
    return word_count;
}

int print_as_tree(const char* filename)
{
    FILE* print_file;
    int print_result_value = FALSE;
    
    unsigned int paragraph_count;
    unsigned int paragraph_index;
    
    const char** sentence;
    unsigned int sentence_count;
    unsigned int sentence_index;
    
    if (s_pa_document_data == NULL) {
        goto return_value;
    }
    
    print_file = fopen(filename, "w");
    if (print_file == NULL) {
        goto return_value;
    }
    
    paragraph_count = get_total_paragraph_count();
    for (paragraph_index = 0; paragraph_index < paragraph_count;) {
        fprintf(print_file, "%s %d%c\n", "Paragraph", paragraph_index, ':');
        
        sentence_count = get_paragraph_sentence_count(get_paragraph_or_null(paragraph_index));
        for (sentence_index = 0; sentence_index < sentence_count; ++sentence_index) {
            fprintf(print_file, "%4s%s %d%c\n", "", "Sentence", sentence_index, ':');
            
            sentence = get_sentence_or_null(paragraph_index, sentence_index);
            while (*sentence != NULL) {
                fprintf(print_file, "%8s%s", "", *sentence++);
                
                if (paragraph_index != paragraph_count - 1 || sentence_index != sentence_count - 1 || *sentence != NULL) {
                    fprintf(print_file, "\n");
                }
            }
        }
        
        if (++paragraph_index < paragraph_count) {
            fprintf(print_file, "\n");
        }
    }
    
    if (fclose(print_file) != 0) {
        perror("file close error");
    }
    print_result_value = TRUE;
return_value:
    return print_result_value;
}

char*** create_paragraph_malloc(const char* str, const char* sentence_delim)
{
    char*** pa_sentence_list;
    char*** pa_sentence_list_ptr;
    
    size_t sentence_length = INITILIZE_MALLOC_LENGTH;
    
    const char* str_ptr = str;
    
    const char* sentence_start_address[SENTENCE_PTR_LENGTH] = { NULL, };
    const char** sentence_start_address_ptr = sentence_start_address;
    
    const char* sentence_end_address[SENTENCE_PTR_LENGTH] = { NULL, };
    const char** sentence_end_address_ptr = sentence_end_address;
    
    const char* delim_ptr;
    const char* find_delim_ptr = NULL;
    int is_find_delim;
    
    while (*str_ptr != '\n' && *str_ptr != '\0') {
        delim_ptr = sentence_delim;
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
        
        if (*sentence_start_address_ptr == NULL) {
            *sentence_start_address_ptr = str_ptr;
        }
        
        if (find_delim_ptr != NULL && is_find_delim == FALSE) {
            ++sentence_length;
            
            sentence_start_address_ptr++;
            *sentence_end_address_ptr++ = find_delim_ptr;
            find_delim_ptr = NULL;
        }
        ++str_ptr;
    }
    *sentence_end_address_ptr = find_delim_ptr;
    
    pa_sentence_list = malloc(sentence_length * sizeof(char*));
    pa_sentence_list_ptr = pa_sentence_list;
    
    sentence_start_address_ptr = sentence_start_address;
    sentence_end_address_ptr = sentence_end_address;

    while (*sentence_start_address_ptr != NULL) {
        *pa_sentence_list_ptr++ = create_sentence_malloc(*sentence_start_address_ptr++, *sentence_end_address_ptr++, " ,");
    }
    *pa_sentence_list_ptr = NULL;
    return pa_sentence_list;
}

char** create_sentence_malloc(const char* str, const char* create_end_str, const char* word_delim)
{
    char** pa_tokenize_strings;
    char** pa_tokenize_strings_ptr;
    
    size_t tokenize_strings_length = INITILIZE_MALLOC_LENGTH;
    
    char* pa_tokenize_string;
    
    const char* str_ptr = str;
    const char* tokenize_start_ptr;
    size_t token_length;
    
    const char* delim_ptr;
    const char* find_delim_ptr = NULL;
    int is_find_delim;
    
    while (*str_ptr != *create_end_str && *str_ptr != '\0') {
        delim_ptr = word_delim;
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
    
    pa_tokenize_strings = malloc(tokenize_strings_length * sizeof(char*));
    pa_tokenize_strings_ptr = pa_tokenize_strings;
    
    tokenize_start_ptr = str;
    find_delim_ptr = NULL;
    
    if (tokenize_strings_length != INITILIZE_MALLOC_LENGTH) {
        str_ptr = str;
        while (*str_ptr != *create_end_str && *str_ptr != '\0') {
            delim_ptr = word_delim;
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
    
    return pa_tokenize_strings;
}
