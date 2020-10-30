#include "hash_map.h"

#include <string.h>
uint64_t RS_hash(const char* str) {
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        hash = hash * a + (str[i]);
        a *= b;
    }
    return hash;
}

int hash_map_init(HashMap *map) {
    if (map == NULL)
        return -1;
    else {
        for (size_t i = 0; i < HASH_MAP_SIZE; i++) {
            map_init(&map->table[i]);
            pthread_mutex_init(&map->mutex_table[i], NULL);
        }
        return 0;
    }
}

void hash_map_release(HashMap *map) {
    if (map == NULL)
        return;
    for (size_t i = 0; i < HASH_MAP_SIZE; i++) {
        map_release(&map->table[i]);
        pthread_mutex_destroy(&map->mutex_table[i]);
    }
}

StrMapData *hash_map_insert_or_search_and_inc(const char *key, uint64_t inc_num, HashMap *map, int *flag) {
    if (key == NULL || map == NULL || flag == NULL)
        return NULL;
    else {
        uint64_t index = RS_hash(key) % HASH_MAP_SIZE;
        pthread_mutex_lock(&map->mutex_table[index]);
        StrMapData *data = map_insert_or_search(key, &map->table[index], flag);
        data->val += inc_num;
        pthread_mutex_unlock(&map->mutex_table[index]);
        return data;
    }
}

