#ifndef USER_H
#define USER_H

#define USER_INFO_STRING_LENGTH (64)

typedef struct user {
    unsigned int id;
    char username[USER_INFO_STRING_LENGTH];
    char email[USER_INFO_STRING_LENGTH];
    char password[USER_INFO_STRING_LENGTH];
} user_t;
#endif
