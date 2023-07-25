#include "data_store.h"
#include <string.h>

#ifdef RELEASE
static void encryption_email_string(char* dest, const char* src)
{
    const char* src_ptr = src;
    char* dest_ptr = dest;
    
    bool is_copy_encryption_string = true;
    unsigned int encryption_count = 0;
    
    const unsigned int partial_disclosure_able_count = 2;
    
    while (*src_ptr != '\0') {
        if (is_copy_encryption_string == true) {
            if (*src_ptr == '@') {
                is_copy_encryption_string = false;
                *dest_ptr++ = *src_ptr;
            } else {
                *dest_ptr++ = '*';
                ++encryption_count;
            }
        } else {
            *dest_ptr++ = *src_ptr;
        }
        
        ++src_ptr;
    }
    *dest_ptr = '\0';
    
    if (encryption_count >= partial_disclosure_able_count) {
        *dest = *src;
        
        if (encryption_count > partial_disclosure_able_count) {
            *(dest + encryption_count - 1) = *(src + encryption_count - 1);
        }
    }
}

static void encryption_password_string(char* dest, const char* src)
{
    char* dest_ptr = dest;
    
    const unsigned int partial_disclosure_able_count = 2;
    
    unsigned int encryption_count = strlen(src);
    for (size_t loop_count = 0; loop_count < encryption_count; ++loop_count) {
        *dest_ptr++ = '*';
    }
    *dest_ptr = '\0';
    
    if (encryption_count >= partial_disclosure_able_count) {
        *dest = *src;
        
        if (encryption_count > partial_disclosure_able_count) {
            *(dest + encryption_count - 1) = *(src + encryption_count - 1);
        }
    }
}
#endif

user_t* get_user_by_id_or_null(user_t** users_or_null, unsigned int id)
{
    if (users_or_null == NULL) {
        return NULL;
    }
    
    user_t** users_ptr = users_or_null;
    while (*users_ptr != NULL) {
        if ((*users_ptr)->id == id) {
            return *users_ptr;
        }
        
        ++users_ptr;
    }
    
    return NULL;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    if (users_or_null == NULL) {
        return NULL;
    }
    
    user_t** users_ptr = users_or_null;
    while (*users_ptr != NULL) {
        if (strcmp((*users_ptr)->username, username) == 0) {
            return *users_ptr;
        }
        
        ++users_ptr;
    }
    
    return NULL;
}

bool update_email(user_t** users_or_null, unsigned int id, const char* email)
{
    user_t* user = get_user_by_id_or_null(users_or_null, id);
    if (user == NULL) {
        return false;
    }
    
    FILE* file = fopen("log.txt", "a");
#ifdef RELEASE
    char encryption_unupdated_email[USER_INFO_STRING_LENGTH];
    encryption_email_string(encryption_unupdated_email, user->email);
    
    char encryption_updated_email[USER_INFO_STRING_LENGTH];
    encryption_email_string(encryption_updated_email, email);
    
    fprintf(file, "TRACE: User %d updated email from \"%s\" to \"%s\"\n", user->id, encryption_unupdated_email, encryption_updated_email);
#else
    fprintf(file, "TRACE: User %d updated email from \"%s\" to \"%s\"\n", user->id, user->email, email);
#endif
    fclose(file);
    
    strcpy(user->email, email);
    return true;
}

bool update_password(user_t** users_or_null, unsigned int id, const char* password)
{
    user_t* user = get_user_by_id_or_null(users_or_null, id);
    if (user == NULL) {
        return false;
    }
    
    FILE* file = fopen("log.txt", "a");
#ifdef RELEASE
    char encryption_unupdated_password[USER_INFO_STRING_LENGTH];
    encryption_password_string(encryption_unupdated_password, user->password);
    
    char encryption_updated_password[USER_INFO_STRING_LENGTH];
    encryption_password_string(encryption_updated_password, password);
    
    fprintf(file, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", user->id, encryption_unupdated_password, encryption_updated_password);
#else
    fprintf(file, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", user->id, user->password, password);
#endif
    fclose(file);
    
    strcpy(user->password, password);
    return true;
}
