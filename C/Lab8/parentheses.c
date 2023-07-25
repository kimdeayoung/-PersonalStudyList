#include "parentheses.h"
#include <assert.h>
#include <stdlib.h>

size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
    const char* str_ptr = str;
    
    size_t parentheses_index = 0;
    size_t matching_count = 0;
    
    bracket_type_t bracket_type;
    int is_opening_bracket;
    
    size_t parenthesis_opening_index_stack[STACK_LENGTH];
    unsigned int parenthesis_count = 0;
    
    size_t brace_opening_index_stack[STACK_LENGTH];
    unsigned int brace_count = 0;
    
    size_t bracket_opening_index_stack[STACK_LENGTH];
    unsigned int bracket_count = 0;
    
    size_t chevron_opening_index_stack[STACK_LENGTH];
    unsigned int chevron_count = 0;
    
    ringbuffer->start_index = 0;
    
    while (*str_ptr != '\0') {
        size_t opening_index;
        
        get_bracket_type(*str_ptr++, &bracket_type, &is_opening_bracket);
        if (bracket_type == none) {
            continue;
        }
        
        if (is_opening_bracket == TRUE) {
            opening_index = str_ptr - str - 1;
            
            switch (bracket_type) {
            case parenthesis:
                parenthesis_opening_index_stack[parenthesis_count++] = opening_index;
                break;
            case brace:
                brace_opening_index_stack[brace_count++] = opening_index;
                break;
            case bracket:
                bracket_opening_index_stack[bracket_count++] = opening_index;
                break;
            case chevron:
                chevron_opening_index_stack[chevron_count++] = opening_index;
                break;
            default:
                assert(0);
                break;
            }
        } else {
            int is_init_opening_index = FALSE;
            
            switch (bracket_type) {
            case parenthesis:
                if (parenthesis_count > 0) {
                    opening_index = parenthesis_opening_index_stack[--parenthesis_count];
                    is_init_opening_index = TRUE;
                }
                break;
            case brace:
                if (brace_count > 0) {
                    opening_index = brace_opening_index_stack[--brace_count];
                    is_init_opening_index = TRUE;
                }
                break;
            case bracket:
                if (bracket_count > 0) {
                    opening_index = bracket_opening_index_stack[--bracket_count];
                    is_init_opening_index = TRUE;
                }
                break;
            case chevron:
                if (chevron_count > 0) {
                    opening_index = chevron_opening_index_stack[--chevron_count];
                    is_init_opening_index = TRUE;
                }
                break;
            default:
                assert(0);
                break;
            }
            
            if (is_init_opening_index == FALSE) {
                continue;
            }
            
            {
                size_t closing_index = str_ptr - str - 1;
                parenthesis_t* parentheses_ptr = ringbuffer->parentheses + parentheses_index;
                if (matching_count >= ringbuffer->max_size) {
                    ringbuffer->start_index = (ringbuffer->start_index + 1) % ringbuffer->max_size;
                }
                parentheses_ptr->opening_index = opening_index;
                parentheses_ptr->closing_index = closing_index;
                
                parentheses_index = (parentheses_index + 1) % ringbuffer->max_size;
            }
            
            ++matching_count;
        }
    }
    
    return matching_count;
}

void get_bracket_type(const char ch, bracket_type_t* out_bracket_type, int* out_is_opening_bracket)
{
    switch (ch) {
    case 40:
        *out_bracket_type = parenthesis;
        *out_is_opening_bracket = TRUE;
        break;
    case 41:
        *out_bracket_type = parenthesis;
        *out_is_opening_bracket = FALSE;
        break;
    case 60:
        *out_bracket_type = chevron;
        *out_is_opening_bracket = TRUE;
        break;
    case 62:
        *out_bracket_type = chevron;
        *out_is_opening_bracket = FALSE;
        break;
    case 91:
        *out_bracket_type = bracket;
        *out_is_opening_bracket = TRUE;
        break;
    case 93:
        *out_bracket_type = bracket;
        *out_is_opening_bracket = FALSE;
        break;
    case 123:
        *out_bracket_type = brace;
        *out_is_opening_bracket = TRUE;
        break;
    case 125:
        *out_bracket_type = brace;
        *out_is_opening_bracket = FALSE;
        break;
    default:
        *out_bracket_type = none;
        *out_is_opening_bracket = FALSE;
        break;
    }
}
