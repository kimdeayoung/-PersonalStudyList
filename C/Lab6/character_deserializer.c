#include "character_deserializer.h"

#define LINE_LENGTH (2048)

int get_character(const char* filename, character_v3_t* out_character)
{
    FILE* file = NULL;
    int version = 0;
    
    char line[LINE_LENGTH];
    size_t loop_index;
    
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("file open error");
        goto file_close;
    }
    
    if (fgets(line, LINE_LENGTH, file) == NULL) {
        clearerr(file);
        goto file_close;
    }
    version = get_specification_version(line);
    
    switch (version) {
    case 1:
        initalize_character_version_1(line, out_character);
        break;
    case 2:
        if (fgets(line, LINE_LENGTH, file) == NULL) {
            clearerr(file);
            goto file_close;
        }
        initalize_character_version_2(line, out_character);
        break;
    case 3:
        if (fgets(line, LINE_LENGTH, file) == NULL) {
            clearerr(file);
            goto file_close;
        }
        initalize_character_version_3(line, out_character);
        if (out_character->minion_count > 0) {
            fgets(line, LINE_LENGTH, file);
            for (loop_index = 0; loop_index < out_character->minion_count; ++loop_index) {
                fgets(line, LINE_LENGTH, file);
                initalize_minion(line, &out_character->minions[loop_index]);
            }
        }
        break;
    default:
        assert(0);
        break;
    }
    
file_close:
    if (file != NULL) {
        if (fclose(file) != 0) {
            perror("file close error");
        }
    }

    return version;
}

int get_specification_version(const char* line)
{
    while (*line != '\0') {
        if (*line == ':') {
            return 1;
        } else if (*line == ',') {
            return 2;
        } else if (*line == '|') {
            return 3;
        }
        ++line;
    }
    return 0;
}

int is_equal_string(const char* str1, const char* str2)
{
    while (*str1 != '\0' && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    
    return *str1 - *str2 == 0 ? TRUE : FALSE;
}

void append_string(char* buffer, size_t buffer_length, const char* str1, const char* str2)
{
    char* buffer_ptr = buffer;
    size_t length = 0;
    
    while (*str1 != '\0' && length++ < buffer_length - 1) {
        *buffer_ptr++ = *str1++;
    }
    
    while (*str2 != '\0' && length++ < buffer_length - 1) {
        *buffer_ptr++ = *str2++;
    }
    
    *(buffer + length) = '\0';
}

void copy_string(char* buffer, size_t copy_length, const char* str)
{
    char* buffer_ptr = buffer;
    
    size_t length = 0;
    
    while (*str != '\0' && length++ < copy_length) {
        *buffer_ptr++ = *str++;
    }
    *(buffer + length - 1) = '\0';
}

void uitoa(unsigned int value, char* buffer, size_t buffer_length)
{
    char* buffer_ptr = buffer;
    size_t length = 0;
    
    if (value == 0) {
        *buffer_ptr++ = '0';
    } else {
        while (value != 0 && length++ < buffer_length) {
            *buffer_ptr++ = 48 + value % 10;
            value /= 10;
        }
    }
    *buffer_ptr = '\0';
    reverse_by_length(buffer, length);
}

void reverse_by_length(char* str, const size_t str_length)
{
    char* ptr1;
    char* ptr2;

    size_t loop_index;
    size_t loop_count;

    loop_count = str_length / 2;

    for (loop_index = 0; loop_index < loop_count; ++loop_index) {
        ptr1 = str + loop_index;
        ptr2 = str + str_length - loop_index - 1;

        *ptr1 = *ptr1 ^ *ptr2;
        *ptr2 = *ptr1 ^ *ptr2;
        *ptr1 = *ptr1 ^ *ptr2;
    }
}

size_t get_name_length(const char* name)
{
    size_t length = 0;
    while (*name != '\0') {
        if ((*name >= 65 && *name <= 90) || (*name >= 97 && *name <= 122) || (*name >= 48 && *name <= 57) || *name == 95) {
            ++length;
            ++name;
        } else {
            break;
        }
    }
    
    return length;
}

void initalize_character_version_1(const char* data, character_v3_t* out_character)
{
    char key_name[KEY_NAME_LENGTH];
    char* key_name_ptr = key_name;
    
    unsigned int value;
    char string_value[NAME_LENGTH];
    
    const char* data_ptr = data;
    
    while (*data_ptr != '\0') {
        if (*data_ptr == ':') {
            *key_name_ptr = '\0';
            sscanf(++data_ptr, "%d", &value);
            
            if (is_equal_string(key_name, "id") == TRUE) {
                uitoa(value, string_value, NAME_LENGTH);
                append_string(out_character->name, NAME_LENGTH, "player_", string_value);
            } else if (is_equal_string(key_name, "lvl") == TRUE) {
                out_character->level = value;
            } else if (is_equal_string(key_name, "str") == TRUE) {
                out_character->strength = value;
            } else if (is_equal_string(key_name, "dex") == TRUE) {
                out_character->dexterity = value;
                out_character->evasion = value / 2;
            } else if (is_equal_string(key_name, "intel") == TRUE) {
                out_character->intelligence = value;
            } else if (is_equal_string(key_name, "def") == TRUE) {
                out_character->armour = value;
            } else if (is_equal_string(key_name, "hp") == TRUE) {
                out_character->health = value;
            } else if (is_equal_string(key_name, "mp") == TRUE) {
                out_character->mana = value;
            }
            
            key_name_ptr = key_name;
        } else if ((*data_ptr >= 65 && *data_ptr <= 90) || (*data_ptr >= 97 && *data_ptr <= 122)) {
            *key_name_ptr++ = *data_ptr;
        }
        
        ++data_ptr;
    }
    
    out_character->evasion = out_character->dexterity / 2;
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
    
    value = out_character->armour / 4 / 3;
    out_character->elemental_resistance.fire = value;
    out_character->elemental_resistance.cold = value;
    out_character->elemental_resistance.lightning = value;
}

void initalize_character_version_2(const char* data, character_v3_t* out_character)
{
    const char* data_ptr = data;
    const char* value_start_ptr = data_ptr;
    
    size_t character_name_length;
    
    unsigned int init_count = 0;
    unsigned int uint_value;
    
    while (*data_ptr != '\0') {
        if (*data_ptr == ',') {
            switch (init_count++) {
            case 0:
                character_name_length = get_name_length(value_start_ptr);
                if (character_name_length > NAME_LENGTH - 1) {
                    character_name_length = NAME_LENGTH - 1;
                }
                copy_string(out_character->name, character_name_length, value_start_ptr);
                break;
            case 1:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->level = uint_value;
                break;
            case 2:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->strength = uint_value;
                break;
            case 3:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->dexterity = uint_value;
                break;
            case 4:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->intelligence = uint_value;
                break;
            case 5:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->armour = uint_value;
                break;
            case 6:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->evasion = uint_value;
                break;
            case 7:
                sscanf(value_start_ptr, "%d", &uint_value);
                uint_value /= 3;
                out_character->elemental_resistance.fire = uint_value;
                out_character->elemental_resistance.cold = uint_value;
                out_character->elemental_resistance.lightning = uint_value;
                break;
            case 8:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->health = uint_value;
                break;
            default:
                assert(0);
                break;
            }
            value_start_ptr = ++data_ptr;
        } else {
            ++data_ptr;
        }
    }
    sscanf(value_start_ptr, "%d", &uint_value);
    out_character->mana = uint_value;
    
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
}

void initalize_character_version_3(const char* data, character_v3_t* out_character)
{
    const char* data_ptr = data;
    const char* value_start_ptr = data_ptr;
    
    size_t character_name_length;
    
    unsigned int init_count = 0;
    unsigned int uint_value;
    
    while (*data_ptr != '\0') {
        if (*data_ptr == '|') {
            switch (init_count++) {
            case 0:
                character_name_length = get_name_length(value_start_ptr);
                if (character_name_length > NAME_LENGTH - 1) {
                    character_name_length = NAME_LENGTH - 1;
                }
                copy_string(out_character->name, character_name_length, value_start_ptr);
                break;
            case 1:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->level = uint_value;
                break;
            case 2:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->health = uint_value;
                break;
            case 3:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->mana = uint_value;
                break;
            case 4:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->strength = uint_value;
                break;
            case 5:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->dexterity = uint_value;
                break;
            case 6:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->intelligence = uint_value;
                break;
            case 7:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->armour = uint_value;
                break;
            case 8:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->evasion = uint_value;
                break;
            case 9:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->elemental_resistance.fire = uint_value;
                break;
            case 10:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->elemental_resistance.cold = uint_value;
                break;
            case 11:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->elemental_resistance.lightning = uint_value;
                break;
            case 12:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_character->leadership = uint_value;
                break;
            default:
                assert(0);
                break;
            }
            value_start_ptr = ++data_ptr;
        } else {
            ++data_ptr;
        }
    }
    
    sscanf(value_start_ptr, "%d", &uint_value);
    out_character->minion_count = uint_value;
}

void initalize_minion(const char* data, minion_t* out_minion)
{
    const char* data_ptr = data;
    const char* value_start_ptr = data_ptr;
    
    size_t character_name_length;
    
    unsigned int init_count = 0;
    unsigned int uint_value;
    
    while (*data_ptr != '\0') {
        if (*data_ptr == '|') {
            switch (init_count++) {
            case 0:
                character_name_length = get_name_length(value_start_ptr);
                if (character_name_length > NAME_LENGTH - 1) {
                    character_name_length = NAME_LENGTH - 1;
                }
                copy_string(out_minion->name, character_name_length, value_start_ptr);
                break;
            case 1:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_minion->health = uint_value;
                break;
            case 2:
                sscanf(value_start_ptr, "%d", &uint_value);
                out_minion->strength = uint_value;
                break;
            default:
                assert(0);
                break;
            }
            value_start_ptr = ++data_ptr;
        } else {
            ++data_ptr;
        }
    }
    
    sscanf(value_start_ptr, "%d", &uint_value);
    out_minion->defence = uint_value;
}
