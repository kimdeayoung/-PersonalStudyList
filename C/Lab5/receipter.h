#ifndef RECEIPTER_H
#define RECEIPTER_H

#include <stdio.h>
#include <stddef.h>
#include <time.h>

#define TRUE (1)
#define FALSE (0)

#define MENU_LENGTH (10)
#define MENU_NAME_LENGTH (26)
#define MESSAGE_LENGTH (75)

int add_item(const char* name, double price);

void copy_string(const char* src, char* dest, size_t dest_length);

void set_tip(double tip);

void set_message(const char* message);

size_t get_str_length(const char* str);

int print_receipt(const char* filename, time_t timestamp);

#endif /* RECEIPTER_H */
