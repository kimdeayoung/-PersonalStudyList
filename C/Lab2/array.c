#include "array.h"
#include <limits.h>

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t index;

    if (num == INT_MIN) {
        return -1;
    }

    for (index = 0; index < element_count; ++index) {
        if (numbers[index] == num) {
            return index;
        }
    }

    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    int index;

    if (num == INT_MIN) {
        return -1;
    }

    for (index = element_count - 1; index >= 0; --index) {
        if (numbers[index] == num) {
            return index;
        }
    }

    return -1;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    int higher_value = INT_MIN;
    size_t max_index = 0;
    size_t index;

    if (element_count == 0) {
        return -1;
    }

    for (index = 0; index < element_count; ++index) {
        if (numbers[index] > higher_value) {
            higher_value = numbers[index];
            max_index = index;
        }
    }

    return higher_value == INT_MIN ? -1 : max_index;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    int min_value = INT_MAX;
    size_t min_index = 0;
    size_t index;

    if (element_count == 0) {
        return -1;
    }

    for (index = 0; index < element_count; ++index) {
        if (numbers[index] != INT_MIN && numbers[index] < min_value) {
            min_value = numbers[index];
            min_index = index;
        }
    }

    return min_index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    size_t index;
    int is_only_int_min = TRUE;

    for (index = 0; index < element_count; ++index) {
        if (numbers[index] != INT_MIN) {
            is_only_int_min = FALSE;
            if (numbers[index] < 0) {
                return FALSE;
            }
        }
    }

    return !is_only_int_min && TRUE;
}

int has_even(const int numbers[], const size_t element_count)
{
    size_t index;

    for (index = 0; index < element_count; ++index) {
        if (numbers[index] != INT_MIN) {
            if (numbers[index] % 2 == 0) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    size_t index;
    int replace_value;
    int is_inserted = FALSE;

    if (num == INT_MIN) {
        return is_inserted;
    }

    for (index = pos; index <= element_count; ++index) {
        if (index == pos) {
            replace_value = numbers[index];
            numbers[index] = num;
            is_inserted = TRUE;
        } else {
            replace_value = replace_value ^ numbers[index];
            numbers[index] = replace_value ^ numbers[index];
            replace_value = replace_value ^ numbers[index];
        }
    }

    return is_inserted;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    size_t find_index;
    int is_removed = FALSE;

    for (find_index = index; find_index < element_count; ++find_index) {
        if (find_index + 1 >= element_count) {
            numbers[find_index] = INT_MIN;
        } else {
            numbers[find_index] = numbers[find_index + 1];
        }
        is_removed = TRUE;
    }

    return is_removed;
}
