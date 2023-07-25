#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#include <assert.h>
#include <stdio.h>
#include <stddef.h>

#define TRUE (1)
#define FALSE (0)

enum length_data {
    MINION_LENGTH = 3,
    KEY_NAME_LENGTH = 32,
    NAME_LENGTH = 51
};

typedef struct {
    char name[NAME_LENGTH];
    unsigned int health;
    unsigned int strength;
    unsigned int defence;
} minion_t;

typedef struct {
    unsigned int fire;
    unsigned int cold;
    unsigned int lightning;
} elemental_resistance_t;

typedef struct {
    char name[NAME_LENGTH];
    unsigned int level;
    unsigned int health;
    unsigned int mana;
    unsigned int strength;
    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int evasion;
    unsigned int leadership;
    unsigned int minion_count;
    elemental_resistance_t elemental_resistance;
    minion_t minions[MINION_LENGTH];
} character_v3_t;

int get_character(const char* filename, character_v3_t* out_character);

int get_specification_version(const char* line);

int is_equal_string(const char* str1, const char* str2);

void append_string(char* buffer, size_t buffer_length, const char* str1, const char* str2);

void copy_string(char* buffer, size_t copy_length, const char* str);

void uitoa(unsigned int value, char* buffer, size_t buffer_length);

void reverse_by_length(char* str, const size_t str_length);

size_t get_name_length(const char* name);

void initalize_character_version_1(const char* data, character_v3_t* out_character);

void initalize_character_version_2(const char* data, character_v3_t* out_character);

void initalize_character_version_3(const char* data, character_v3_t* out_character);

void initalize_minion(const char* data, minion_t* out_minion);

#endif /* CHARACTER_DESERIALIZER_H */
