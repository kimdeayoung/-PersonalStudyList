#ifndef PARENTHESES_H
#define PARENTHESES_H

#include <stddef.h>

#define TRUE (1)
#define FALSE (0)

#define STACK_LENGTH (128)

typedef struct {
    size_t opening_index;
    size_t closing_index;
} parenthesis_t;

typedef struct {
    size_t start_index;
    parenthesis_t* parentheses;
    size_t max_size;
} ringbuffer_t;

typedef enum {
    none,
    parenthesis,
    brace,
    bracket,
    chevron
} bracket_type_t;

typedef struct {
    bracket_type_t bracket_type;
    size_t opening_index;
} parenthesis_opening_info_t;

size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str);

void get_bracket_type(const char ch, bracket_type_t* out_bracket_type, int* out_is_opening_bracket);

#endif /* PARENTHESES_H */
