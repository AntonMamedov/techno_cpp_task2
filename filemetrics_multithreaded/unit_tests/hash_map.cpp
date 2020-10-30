#include "gtest/gtest.h"
extern "C"{
#include "../inc/hash_map.h"
#include "../src/hash_map.c"
}

TEST(HashMapInitTest, NormalHashMapInitTest){
    HashMap map;
    EXPECT_EQ(hash_map_init(&map), 0);
    hash_map_release(&map);
}

TEST(HashMapInitTest, NULLHashMapInitTest) {
    EXPECT_EQ(hash_map_init(NULL), -1);
}

TEST(HashMapInserSearchTest, InsertOneElemTest){
    const char* key = "111";
    HashMap map;
    hash_map_init(&map);
    int flag = 0;
    StrMapData* data = hash_map_insert_or_search_and_inc(key, 1, &map, &flag);
    EXPECT_STREQ(str_get(&data->key), key);
    EXPECT_EQ(data->val, 1);
    EXPECT_EQ(flag, INSERTED);
    hash_map_release(&map);
}

TEST(HashMapInserSearchTest, InsertNULLKeyElemTest){
    const char* key = NULL;
    HashMap map;
    hash_map_init(&map);
    int flag = 0;
    StrMapData* data = hash_map_insert_or_search_and_inc(key, 1, &map, &flag);
    bool test_flag = false;
    if (data == NULL)
        test_flag = true;
    EXPECT_EQ(true, test_flag);
    hash_map_release(&map);
}

TEST(HashMapInserSearchTest, InsertNULLMapElemTest){
    const char* key = NULL;
    int flag = 0;
    StrMapData* data = hash_map_insert_or_search_and_inc(key, 1, NULL, &flag);
    bool test_flag = false;
    if (data == NULL)
        test_flag = true;
    EXPECT_EQ(true, test_flag);
}

TEST(HashMapInserSearchTest, InsertNULLFlagElemTest){
    const char* key = NULL;
    HashMap map;
    hash_map_init(&map);
    StrMapData* data = hash_map_insert_or_search_and_inc(key, 1, &map, NULL);
    bool test_flag = false;
    if (data == NULL)
        test_flag = true;
    EXPECT_EQ(true, test_flag);
    hash_map_release(&map);
}

TEST(HashMapInserSearchTest, InsertAlotElemTest){
    const size_t key_len = 3;
    const size_t insert_num = 10;
    char key[key_len] = {'a', 'b', 'c'};
    HashMap map;
    hash_map_init(&map);

    int flag = 0;
    StrMapData* data = hash_map_insert_or_search_and_inc(key, 1, &map, &flag);
    EXPECT_STREQ(str_get(&data->key), key);
    EXPECT_EQ(data->val, 1);
    EXPECT_EQ(flag, INSERTED);
    for (size_t i = 0; i < insert_num; i++){
        key[insert_num % key_len]+=1;
        data = hash_map_insert_or_search_and_inc(key, 1, &map, &flag);
        EXPECT_STREQ(str_get(&data->key), key);
        EXPECT_EQ(data->val, 1);
        EXPECT_EQ(flag, INSERTED);
    }
    hash_map_release(&map);
}

TEST(HashMapInserSearchTest, SearchElemTest){
    const size_t key_len = 3;
    const size_t insert_num = 10;
    char key[key_len] = {'a', 'b', 'c'};
    HashMap map;
    hash_map_init(&map);
    int flag = 0;
    StrMapData* data = hash_map_insert_or_search_and_inc(key, 1, &map, &flag);
    EXPECT_STREQ(str_get(&data->key), key);
    EXPECT_EQ(data->val, 1);
    EXPECT_EQ(flag, INSERTED);
    for (size_t i = 0; i < insert_num; i++){
        data = hash_map_insert_or_search_and_inc(key, 0, &map, &flag);
        EXPECT_STREQ(str_get(&data->key), key);
        EXPECT_EQ(data->val, 1);
        EXPECT_EQ(flag, FOUND);
    }
    hash_map_release(&map);
}
const size_t iter_num = 1000000;
void* thread_worker(void* data){
    const char* key = "111";
    int flag = 0;
    HashMap* map = (HashMap*)data;
    for (size_t i = 0; i < iter_num; i++)
        hash_map_insert_or_search_and_inc(key, 1, map, &flag);
    return NULL;
}
TEST(HashMapInserSearchTest, SearchAndIncMultiThreadInSingleElemTest){
    const size_t thread_num = 300;
    const char* key = "111";
    HashMap map;
    hash_map_init(&map);
    pthread_t threads[thread_num];
    for (size_t i = 0; i <  thread_num; i++)
        pthread_create(&threads[i], NULL, thread_worker, (void*)&map);
    for (size_t i = 0; i < thread_num; i++) {
        void** res;
        pthread_join(threads[i], res);
    }
    int flag = 0;
    StrMapData* data = hash_map_insert_or_search_and_inc(key, 0, &map, &flag);
    EXPECT_EQ(data->val, iter_num * thread_num);
    hash_map_release(&map);
}
