#include "translate.h"
#include <stdio.h>

#define ESCAPE_SLASH (92)
#define HYPHEN (45)

#define TRANSLATE_SET_LENGTH (512)
#define TRANSLATE_INITIALIZE_LENGTH (1024)

#define LINE_LENGTH (1024)

int translate(int argc, const char** argv)
{
    const char* input_set1;
    const char* input_set2;

    char set1[TRANSLATE_SET_LENGTH];
    char set2[TRANSLATE_SET_LENGTH];
    int ignore_case;

    char line[LINE_LENGTH];

    int translate_result = 0;

    if (argc == 3) {
        ignore_case = FALSE;
        input_set1 = *++argv;
        input_set2 = *++argv;
    } else if (argc == 4) {
        if (compare_string(*++argv, "-i") == TRUE) {
            ignore_case = TRUE;
            input_set1 = *++argv;
            input_set2 = *++argv;
        } else {
            translate_result = ERROR_CODE_INVALID_FLAG;
            goto func_end;
        }
    } else {
        translate_result = ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
        goto func_end;
    }

    translate_result = initialize_translate_set(input_set1, set1, input_set2, set2);
    if (translate_result != 0) {
        goto func_end;
    }

    while (TRUE) {
        if (fgets(line, LINE_LENGTH, stdin) == NULL) {
            clearerr(stdin);
            break;
        }
        translate_string(line, set1, set2, ignore_case);
        printf("%s", line);
    }

func_end:
    return translate_result;
}

int initialize_translate_set(const char* input_set1, char* translate_set1, const char* intput_set2, char* translate_set2)
{
    /* simulate values */
    char translate_set1_simulate[TRANSLATE_INITIALIZE_LENGTH];
    char translate_set2_simulate[TRANSLATE_INITIALIZE_LENGTH];

    char* translate_set1_simulate_ptr = translate_set1_simulate;
    char* translate_set2_simulate_ptr = translate_set2_simulate;

    char* translate_set2_ptr = translate_set2;

    /* find same translate set value */
    size_t loop_index;
    size_t initialize_count = 0;
    int initialized_char_index;

    int func_result_value = 0;

    func_result_value = simulate_translate_set(input_set1, translate_set1_simulate);
    if (func_result_value != 0) {
        goto func_end;
    }
    func_result_value = simulate_translate_set(intput_set2, translate_set2_simulate);
    if (func_result_value != 0) {
        goto func_end;
    }

    while (*translate_set1_simulate_ptr != '\0') {
        initialized_char_index = -1;
        for (loop_index = 0; loop_index < initialize_count; ++loop_index) {
            if (*(translate_set1_simulate + loop_index) == *translate_set1_simulate_ptr) {
                initialized_char_index = loop_index;
                break;
            }
        }

        if (initialized_char_index == -1) {
            *translate_set1++ = *translate_set1_simulate_ptr;
            *translate_set2_ptr++ = *translate_set2_simulate_ptr;
        } else {
            *(translate_set2 + initialized_char_index) = *translate_set2_simulate_ptr;
        }

        if (++initialize_count >= TRANSLATE_SET_LENGTH) {
            func_result_value = ERROR_CODE_ARGUMENT_TOO_LONG;
            goto func_end;
        }

        ++translate_set1_simulate_ptr;
        if (*++translate_set2_simulate_ptr == '\0') {
            --translate_set2_simulate_ptr;
        }
    }

    *translate_set1 = '\0';
    *translate_set2_ptr = '\0';

func_end:
    return func_result_value;
}

int simulate_translate_set(const char* src, char* simulate_result)
{
    enum translate_set_type set_type;

    char* simulate_ptr = simulate_result;

    unsigned int src_move_count;
    unsigned int append_count;
    int convert_range_result = 0;

    while (*src != '\0') {
        set_type = get_translate_set_type(src);
        
        switch (set_type) {
        case NORMAL:
            *simulate_ptr++ = *src++;
            break;
        case ESCAPE_CHARACTER:
            *simulate_ptr = convert_escape_char(*++src);
            if (*simulate_ptr == '\0') {
                convert_range_result = ERROR_CODE_INVALID_FORMAT;
                goto func_end;
            }
            ++simulate_ptr;
            ++src;
            break;
        case RANGE_CHARACTER:
            convert_range_result = convert_range_char(src, simulate_ptr, &src_move_count, &append_count);
            if (convert_range_result != 0) {
                goto func_end;
            }
            src += src_move_count;
            simulate_ptr += append_count;
            break;
        default:
            assert(0);
            break;
        }
    }

func_end:
    *simulate_ptr = '\0';
    return convert_range_result;
}

int get_translate_set_type(const char* translate_set)
{
    int find_hyphen_index = *translate_set == ESCAPE_SLASH ? 2 : 1;
    if (*(translate_set + find_hyphen_index) == HYPHEN) {
        if (*translate_set != '\0' && *(translate_set + find_hyphen_index + 1) != '\0') {
            return RANGE_CHARACTER;
        }
    }

    if (*translate_set == ESCAPE_SLASH) {
        return ESCAPE_CHARACTER;
    } else {
        return NORMAL;
    }
}

char convert_escape_char(char escape_char)
{
    switch (escape_char) {
    case ESCAPE_SLASH:
        return '\\';
    case 97:
        return '\a';
    case 98:
        return '\b';
    case 102:
        return '\f';
    case 110:
        return '\n';
    case 114:
        return '\r';
    case 116:
        return '\t';
    case 118:
        return '\v';
    case 39:
        return '\'';
    case 34:
        return '\"';
    default:
        return '\0';
    }
}

int convert_range_char(const char* range_input, char* append_str, unsigned int* range_move_count, unsigned int* append_count)
{
    char range_start_char;
    char range_end_char;
    const char* range_input_ptr = range_input;

    int convert_range_char_result = 0;

    *append_count = 0;

    if (*range_input_ptr == ESCAPE_SLASH) {
        range_start_char = convert_escape_char(*++range_input_ptr);
        ++range_input_ptr;
    } else {
        range_start_char = *range_input_ptr++;
    }
    ++range_input_ptr;
    if (*range_input_ptr == ESCAPE_SLASH) {
        range_end_char = convert_escape_char(*++range_input_ptr);
    } else {
        range_end_char = *range_input_ptr;
    }
    ++range_input_ptr;
    *range_move_count = range_input_ptr - range_input;

    if (range_start_char > range_end_char) {
        convert_range_char_result = ERROR_CODE_INVALID_RANGE;
        goto func_end;
    }

    while (range_start_char != range_end_char + 1) {
        *append_str++ = range_start_char++;
        ++(*append_count);
    }

func_end:
    return convert_range_char_result;
}

void translate_string(char* target_string, const char* translate_set1, const char* translate_set2, int ignore_case)
{
    const char* translate_set1_ptr;
    
    while (*target_string != '\0') {
        translate_set1_ptr = translate_set1;
        
        while (*translate_set1_ptr != '\0') {
            if (is_translate_able(*target_string, *translate_set1_ptr, ignore_case) == TRUE) {
                *target_string = *(translate_set2 + (translate_set1_ptr - translate_set1));
                break;
            }
            ++translate_set1_ptr;
        }
        ++target_string;
    }
}

int is_translate_able(char target_char, char translate_set, int ignore_case)
{
    const char SEPARATOR = 32;
    
    if (target_char == translate_set) {
        return TRUE;
    } else if (ignore_case == TRUE) {
        if (translate_set >= 65) {
            return target_char == (translate_set >= 97 ? translate_set - SEPARATOR : translate_set + SEPARATOR);
        }
    }
    
    return FALSE;
}

int compare_string(const char* str1, const char* str2)
{
    while (*str1 != '\0' && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    
    return *str1 == *str2 ? TRUE : FALSE;
}
