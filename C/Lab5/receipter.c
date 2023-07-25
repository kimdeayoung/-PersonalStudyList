#include "receipter.h"

#define CHAR_ARR_SIZE (512)
#define MENU_SIZE (32)

unsigned int g_order_count = 0;

size_t g_insert_menu_count = 0;
char g_menu_names[MENU_SIZE][CHAR_ARR_SIZE];
double g_menu_prices[MENU_SIZE];

double g_tip_price = 0;
char g_receipt_message[CHAR_ARR_SIZE];

int add_item(const char* name, double price)
{
    if (g_insert_menu_count < MENU_LENGTH) {
        copy_string(name, *(g_menu_names + g_insert_menu_count), MENU_NAME_LENGTH - 1);
        g_menu_prices[g_insert_menu_count] = price;
        ++g_insert_menu_count;
        return TRUE;
    }
    return FALSE;
}

void copy_string(const char* src, char* dest, size_t dest_length)
{
    size_t copy_count = 0;
    char* dest_ptr = dest;

    while (copy_count++ < dest_length && *src != '\0') {
        *dest_ptr++ = *src++;
    }
    *dest_ptr = '\0';
}

void set_tip(double tip)
{
    g_tip_price = tip;
}

void set_message(const char* message)
{
    copy_string(message, g_receipt_message, MESSAGE_LENGTH);
}

size_t get_str_length(const char* str)
{
    const char* str_ptr = str;
    while (*str_ptr++ != '\0') {
    }
    return str_ptr - str - 1;
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* file = NULL;
    size_t loop_index;
    size_t message_print_offset = 0;
    size_t message_length;

    double menu_price;
    double sub_total_price = 0.0;
    double tax;

    struct tm* time;

    int print_result = FALSE;

    if (g_insert_menu_count == 0) {
        goto clear_data;
    }

    time = gmtime(&timestamp);
    message_length = get_str_length(g_receipt_message);

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("file open error");
        goto clear_data;
    }

    fprintf(file, "Charles' Seafood\n");
    fprintf(file, "--------------------------------------------------\n");
    fprintf(file, "%04d-%02d-%02d %02d:%02d:%02d%26s%05d\n", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec, "", g_order_count++);
    fprintf(file, "--------------------------------------------------\n");
    for (loop_index = 0; loop_index < g_insert_menu_count; ++loop_index) {
        menu_price = *(g_menu_prices + loop_index);
        sub_total_price += menu_price;
        fprintf(file, "%33.33s%17.2f\n", *(g_menu_names + loop_index), menu_price);
    }
    tax = sub_total_price * 0.05;
    tax += 0.001;
    
    fprintf(file, "\n");

    fprintf(file, "%33.33s%17.2f\n", "Subtotal", sub_total_price);
    if (g_tip_price != 0.0) {
        fprintf(file, "%33.33s%17.2f\n", "Tip", g_tip_price);
    }
    fprintf(file, "%33.33s%17.2f\n", "Tax", tax);
    fprintf(file, "%33.33s%17.2f\n", "Total", sub_total_price + g_tip_price + tax);
    fprintf(file, "\n");

    while (message_print_offset < message_length) {
        message_print_offset += fprintf(file, "%-1.50s\n", (g_receipt_message + message_print_offset));
        message_print_offset -= 1;
    }

    fprintf(file, "==================================================\n");
    fprintf(file, "%50s", "Tax#-51234");
    print_result = TRUE;
clear_data:
    g_insert_menu_count = 0;
    set_tip(0.0);
    set_message("\0");

    if (file != NULL) {
        if (fclose(file) != 0) {
            perror("file close error");
        }
    }
    return print_result;
}
