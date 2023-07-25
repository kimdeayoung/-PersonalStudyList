#include "todo_list.h"
#include <stdlib.h>
#include <string.h>

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t todo_list;
    todo_list.task_datas = malloc(max_size * sizeof(todo_data_t));
    todo_list.task_count = 0;
    todo_list.task_max_count = max_size;
    return todo_list;
}

void finalize_todo_list(todo_list_t* todo_list)
{
    todo_data_t* todo_datas_ptr = todo_list->task_datas;
    for (size_t loop_index = 0; loop_index < todo_list->task_count; ++loop_index) {
        todo_data_t* free_todo_data = todo_datas_ptr++;
        
        free(free_todo_data->task_key);
        free_todo_data->task_key = NULL;
    }
    
    free(todo_list->task_datas);
    todo_list->task_datas = NULL;
    
    todo_list->task_count = 0;
    todo_list->task_max_count = 0;
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (is_full(todo_list) == true) {
        return false;
    }
    
    size_t task_len = strlen(task);
    
    todo_data_t todo_data;
    todo_data.task_key = malloc(task_len + 1);
    strcpy(todo_data.task_key, task);
    *(todo_data.task_key + task_len) = '\0';
    todo_data.task_priority = priority;
    
    *(todo_list->task_datas + todo_list->task_count++) = todo_data;
    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    if (is_empty(todo_list) == true) {
        return false;
    }
    
    size_t complete_arr_index = get_higer_priority_arr_index(todo_list);
    {
        todo_data_t* free_todo_data = todo_list->task_datas + complete_arr_index;
        free(free_todo_data->task_key);
        free_todo_data->task_key = NULL;
    }
    
    --todo_list->task_count;
    for (size_t loop_index = complete_arr_index; loop_index < todo_list->task_count; ++loop_index) {
        *(todo_list->task_datas + loop_index) = *(todo_list->task_datas + loop_index + 1);
    }
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (is_empty(todo_list) == true) {
        return NULL;
    }
    
    todo_data_t* task_data_ptr = todo_list->task_datas + get_higer_priority_arr_index(todo_list);
    return task_data_ptr->task_key;
}

size_t get_higer_priority_arr_index(const todo_list_t* todo_list)
{
    size_t arr_index;
    int32_t higer_priority = INT32_MIN;
    
    todo_data_t* task_datas_ptr = todo_list->task_datas;
    for (size_t loop_index = 0; loop_index < todo_list->task_count; ++loop_index) {
        if (task_datas_ptr->task_priority > higer_priority) {
            arr_index = loop_index;
            higer_priority = task_datas_ptr->task_priority;
        }
        ++task_datas_ptr;
    }
    
    return arr_index;
}

size_t get_count(const todo_list_t* todo_list)
{
    return todo_list->task_count;
}

bool is_empty(const todo_list_t* todo_list)
{
    return get_count(todo_list) == 0 ? true : false;
}

bool is_full(const todo_list_t* todo_list)
{
    return get_count(todo_list) == todo_list->task_max_count ? true : false;
}
