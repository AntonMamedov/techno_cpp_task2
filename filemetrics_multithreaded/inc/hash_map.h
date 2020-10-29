#pragma once
#include <pthread.h>
#include <stdlib.h>
#include "str_map.h"

#define HASH_MAP_SIZE 70001

typedef struct{
    StrMap table[HASH_MAP_SIZE];
    pthread_mutex_t mutex_table[HASH_MAP_SIZE];
}HashMap;

void hash_map_init(HashMap* map);

StrMapData* hash_map_insert_or_search_and_inc(char* key, uint64_t inc_num, HashMap * map, int* flag);

void hash_map_release(HashMap* map);