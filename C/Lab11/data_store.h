#ifndef DATA_STORE
#define DATA_STORE

#include "user.h"
#include <stdio.h>
#include <stdbool.h>

user_t* get_user_by_id_or_null(user_t** users_or_null, unsigned int id);
user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username);

bool update_email(user_t** users_or_null, unsigned int id, const char* email);
bool update_password(user_t** users_or_null, unsigned int id, const char* password);

#endif
