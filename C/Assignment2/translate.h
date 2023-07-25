#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <assert.h>

#define TRUE (1)
#define FALSE (0)

typedef enum error_code {
    ERROR_CODE_WRONG_ARGUMENTS_NUMBER = 1,
    ERROR_CODE_INVALID_FLAG,
    ERROR_CODE_INVALID_FORMAT,
    ERROR_CODE_ARGUMENT_TOO_LONG,
    ERROR_CODE_INVALID_RANGE
} error_code_t;

typedef enum translate_set_type {
    NORMAL = 0,
    ESCAPE_CHARACTER,
    RANGE_CHARACTER
} translate_set_type_t;

int translate(int argc, const char** argv);

int initialize_translate_set(const char* input_set1, char* translate_set1, const char* intput_set2, char* translate_set2);

int simulate_translate_set(const char* src, char* simulate_result);

int get_translate_set_type(const char* translate_set);

char convert_escape_char(char escape_char);

int convert_range_char(const char* range_input, char* append_str, unsigned int* range_move_count, unsigned int* append_count);

void translate_string(char* target_string, const char* translate_set1, const char* translate_set2, int ignore_case);

int is_translate_able(char target_char, char translate_set, int ignore_case);

int compare_string(const char* str1, const char* str2);

#endif /* TRANSLATE_H */
