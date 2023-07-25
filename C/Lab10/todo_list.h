#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct todo_data {
    char* task_key;
    int32_t task_priority;
} todo_data_t;

typedef struct todo_list {
    todo_data_t* task_datas;
    size_t task_count;
    size_t task_max_count;
} todo_list_t;

todo_list_t init_todo_list(size_t max_size);

void finalize_todo_list(todo_list_t* todo_list);

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task);

bool complete_todo(todo_list_t* todo_list);

const char* peek_or_null(const todo_list_t* todo_list);

size_t get_higer_priority_arr_index(const todo_list_t* todo_list);

size_t get_count(const todo_list_t* todo_list);

bool is_empty(const todo_list_t* todo_list);

bool is_full(const todo_list_t* todo_list);

#endif /* TODO_LIST_H */
