#include "hashmap.h"
#include <string.h>
#include <stdlib.h>

hashmap_t* init_hashmap_malloc(size_t length, unsigned int (*p_hash_func)(const char* key))
{
    hashmap_t* hashmap = malloc(sizeof(hashmap_t));
    hashmap->hash_func = p_hash_func;
    hashmap->plist = malloc(sizeof(node_t*) * length);
    node_t** plist_ptr = hashmap->plist;
    for (size_t loop_index = 0; loop_index < length; ++loop_index) {
        *plist_ptr++ = NULL;
    }
    
    hashmap->length = length;
    return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    node_t** plist_ptr = hashmap->plist + get_hash(hashmap, key);
    
    while (*plist_ptr != NULL) {
        if (strcmp((*plist_ptr)->key, key) == 0) {
            return FALSE;
        }
        
        plist_ptr = &((*plist_ptr)->next);
    }
    
    size_t key_len = strlen(key);
    
    node_t* new_node = malloc(sizeof(node_t));
    new_node->key = malloc(sizeof(char) * (key_len + 1));
    strcpy(new_node->key, key);
    *(new_node->key + key_len) = '\0';
    new_node->value = value;
    new_node->next = NULL;
    
    *plist_ptr = new_node;
    return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    node_t** plist_ptr = hashmap->plist + get_hash(hashmap, key);
    while (*plist_ptr != NULL) {
        if (strcmp((*plist_ptr)->key, key) == 0) {
            return (*plist_ptr)->value;
        }
        
        plist_ptr = &((*plist_ptr)->next);
    }
    
    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    node_t** plist_ptr = hashmap->plist + get_hash(hashmap, key);
    while (*plist_ptr != NULL) {
        if (strcmp((*plist_ptr)->key, key) == 0) {
            (*plist_ptr)->value = value;
            return TRUE;
        }
        
        plist_ptr = &((*plist_ptr)->next);
    }
    
    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    node_t** plist_ptr = hashmap->plist + get_hash(hashmap, key);
    while (*plist_ptr != NULL) {
        if (strcmp((*plist_ptr)->key, key) == 0) {
            node_t* free_node = *plist_ptr;
            *plist_ptr = (*plist_ptr)->next;
            
            free(free_node->key);
            free_node->key = NULL;
            
            free(free_node);
            free_node = NULL;
            return TRUE;
        }
        
        plist_ptr = &((*plist_ptr)->next);
    }
    
    return FALSE;
}

unsigned int get_hash(const hashmap_t* hashmap, const char* key)
{
    unsigned int hash = hashmap->hash_func(key) % hashmap->length;
    
    return hash;
}

void destroy(hashmap_t* hashmap)
{
    hashmap_t* free_hashmap = hashmap;
    node_t** plist_ptr = hashmap->plist;
    
    for (size_t loop_index = 0; loop_index < hashmap->length; ++loop_index) {
        node_t* free_nodes_ptr = *plist_ptr++;
        
        while (free_nodes_ptr != NULL) {
            node_t* free_node = free_nodes_ptr;
            free_nodes_ptr = free_node->next;
            
            free(free_node->key);
            free_node->key = NULL;
            
            free(free_node);
            free_node = NULL;
        }
    }
    
    free(free_hashmap->plist);
    free_hashmap->plist = NULL;
    
    free(free_hashmap);
    free_hashmap = NULL;
}

