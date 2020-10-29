#include "gtest/gtest.h"
extern "C"{
#include "../inc/str_map.h"
#include "../src/str_map.c"
}

//Тестирование функции инициализации дерева
TEST(StrMapInitTest, NormalInitTest){
    StrMap map;
    int state = map_init(&map);
    ASSERT_EQ(map.size, 0);
    ASSERT_EQ(state, 0);
}

TEST(StrMapInitTest, NULLlInitTest){
    int state = map_init(NULL);
    ASSERT_EQ(state, -1);
}

//Тестироание функции инициализации ноды дерева
TEST(StrMapNodeInitTest, NormalMapNodeInitTest) {
    char *key = "111";
    StrMapNode *map_node = map_node_init(key);
    ASSERT_EQ(NULL, map_node->left);
    ASSERT_EQ(NULL, map_node->right);
    ASSERT_STREQ(key, str_get(&map_node->data.key));
    ASSERT_EQ(0, map_node->data.val);
    str_release(&map_node->data.key);
    free(map_node);
}

TEST(StrMapNodeInitTest, NULLMapNodeInitTest) {
    char *key = NULL;
    StrMapNode *map_node = map_node_init(NULL);
    ASSERT_EQ(NULL, map_node);

}

//Тестирования функции вставки и поиска в дереве
TEST(StrInsertSearchTest, NewElemInsertTest){
    const size_t elem_num = 10;
    const size_t test_str_len = 3;
    StrMap map;
    map_init(&map);
    char test_str[test_str_len] = {'b', 'c', 'a'};
    //В цикле вставляем в дерево 10 новых строк и инерментируем значение val в поле дата ноды дерева
    //Строка изменяет посредствам прибавления к аски коду одного из символов строки единицы в конце каждой итерации
    for (size_t i = 0; i < elem_num; i++) {
        int flag = 0;
        StrMapData* data = map_insert_or_search(test_str, &map, &flag);
        data->val+=1;
        ASSERT_STREQ(str_get(&data->key), test_str);
        ASSERT_EQ(data->val, 1);
        ASSERT_EQ(flag, INSERTED);
        test_str[elem_num % test_str_len]+=1;
    }
    ASSERT_EQ(map.size, elem_num);
    map_release(&map);
}

TEST(StrInsertSearchTest, ElemSearchTest){
    const size_t elem_num = 10;
    const size_t test_str_len = 3;
    StrMap map;
    map_init(&map);
    char test_str[test_str_len] = {'b', 'c', 'a'};
    int flag = 0;
    //Вставляем элемент в дерево
    StrMapData* data = map_insert_or_search(test_str, &map, &flag);
    data->val+=1;
    ASSERT_STREQ(str_get(&data->key), test_str);
    ASSERT_EQ(data->val, 1);
    ASSERT_EQ(flag, INSERTED);
    //9 раз ищем вставленный элемент и инкрментируем поле val
    for (size_t i = 1; i < elem_num; i++) {
        StrMapData* data = map_insert_or_search(test_str, &map, &flag);
        data->val+=1;
        ASSERT_STREQ(str_get(&data->key), test_str);
        ASSERT_EQ(data->val, i+1);
        ASSERT_EQ(flag, FOUND);
    }
    ASSERT_EQ(map.size, 1);
    map_release(&map);
}

TEST(StrInsertSearchTest, NullMapSearchInsertTest){
    int flag = 0;
    StrMapData* data = map_insert_or_search("111", NULL, 0);
    ASSERT_EQ(NULL, data);
}

TEST(StrInsertSearchTest, NULLKeyInsertSearchTest){
    int flag = 0;
    StrMap map;
    map_init(&map);
    StrMapData* data = map_insert_or_search(NULL, &map, &flag);
    ASSERT_EQ(NULL, data);
}

//Структура для тестирования обхода дерева
struct map_pre_order_test_data{
    size_t* bypass_order;
    char** keys;
    size_t current_index;
};

//Функция, передаваемая в функцию обхода, во время тестирования обхода
void map_pre_order_test_func(StrMapData* data, void* w_data){
    struct map_pre_order_test_data* work_data = (map_pre_order_test_data*)w_data;
    //Сравниваем строку в узле, в котором находимся со строкой в массиве строк, по индексу в массиве индексов
    ASSERT_STREQ(str_get(&data->key), work_data->keys[work_data->bypass_order[work_data->current_index]]);
    work_data->current_index+=1;
}

TEST(MapPreOrderTest, NormalPreOrderTest){
    const size_t key_num = 5;
    //Создаем массив односимвольных слов для теста
    char* keys[key_num] = {"5", "2", "6", "3", "8"};
    //Создаем массив, который отрожает порядок обхода дерева, содержит индексы строк в массиве keys
    size_t bypass_order[key_num] = {0, 2, 4, 1, 3};
    StrMap map;
    map_init(&map);
    //Заносим слова в дерево
    for(size_t i = 0; i < key_num; i++){
        int flag = 0;
        map_insert_or_search(keys[i], &map, &flag);
    }
    struct map_pre_order_test_data work_data {bypass_order, keys, 0};
    //Тестируем обход
    int indicator = map_pre_order(&map, map_pre_order_test_func, (void*)&work_data);
    ASSERT_EQ(0, indicator);
    map_release(&map);
}

TEST(MapPreOrderTest, NULLPreOrderTest){
    int indicator =map_pre_order(NULL, NULL, NULL);
    ASSERT_EQ(indicator, -1);
}

//Тестирование функции очищения
TEST(MapReleaseTest, NormalReleaseTest){
    StrMap map;
    map_init(&map);
    const size_t test_str_len = 3;
    const size_t elem_num = 10;
    char test_str[test_str_len] = {'b', 'c', 'a'};
    //В цикле вставляем в дерево 10 новых строк и инерментируем значение val в поле дата ноды дерева
    //Строка изменяет посредствам прибавления к аски коду одного из символов строки единицы в конце каждой итерации
    for (size_t i = 0; i < elem_num; i++) {
        int flag = 0;
        StrMapData* data = map_insert_or_search(test_str, &map, &flag);
        data->val+=1;
        test_str[elem_num % test_str_len]+=1;
    }
    ASSERT_EQ(elem_num, map.size);
    int indicator = map_release(&map);
    ASSERT_EQ(0, indicator);
    ASSERT_EQ(0, map.size);
}

TEST(MapReleaseTest, NULLReleaseTest){
    int indicator = map_release(NULL);
    ASSERT_EQ(indicator, -1);
}