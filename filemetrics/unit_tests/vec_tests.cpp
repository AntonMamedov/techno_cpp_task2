#include "gtest/gtest.h"
extern "C"{
#include "../inc/vec.h"
#include "../src/vec.c"
}

//Тестирования функции инициализации веткора
TEST(VecInitTest, NormalVecInitTest){
    Vector vec;
    int indicator = vec_init(&vec);
    ASSERT_EQ(vec.size, 0);
    ASSERT_EQ(vec.alloc_size, 0);
    ASSERT_EQ(indicator, 0);
}

TEST(VecInitTest, NULLVecInitTest){
    int indicator = vec_init(NULL);
    ASSERT_EQ(indicator, -1);
}

//Тестирование функции добавления в вектор
TEST(VecPushTest, NoExtendPushTest){
    Vector vec;
    vec_init(&vec);
    size_t elem_num = 3;
    char* test_str = "111";
    for (size_t i = 0; i < elem_num; i++)
        ASSERT_EQ(vec_push(test_str, &vec), 0);
    ASSERT_EQ(vec.size, elem_num);
    ASSERT_EQ(vec.alloc_size, DEFAULT_ALLOC_SIZE);
    vec_release(NULL, &vec);
}

TEST(VecPushTest, ExtendPushTest){
    Vector vec;
    vec_init(&vec);
    size_t elem_num = DEFAULT_ALLOC_SIZE + 1;
    char* test_str = "111";
    for (size_t i = 0; i < elem_num; i++) {
        ASSERT_EQ(vec_push(test_str, &vec), 0);
    }
    ASSERT_EQ(vec.size, elem_num);
    ASSERT_EQ(vec.alloc_size, DEFAULT_ALLOC_SIZE * 2);
    vec_release(NULL, &vec);
}

TEST(VecPushTest, NUllElemPushTest){
    Vector vec;
    vec_init(&vec);
    ASSERT_EQ(vec_push(NULL, &vec), -1);
}

TEST(VecPushTest, NUllVecPushTest){
    Vector vec;
    vec_init(&vec);
    char* test_str = "111";
    ASSERT_EQ(vec_push(test_str, NULL), -1);
}

//Тестирование функции взятия элемента по индексу
TEST(VecGetTest, NormalElemGetTest){
    Vector vec;
    vec_init(&vec);
    size_t elem_num = 3;
    char* test_str = "111";
    for (size_t i = 0; i < elem_num; i++)
        ASSERT_EQ(vec_push(test_str, &vec), 0);
    for (size_t i = 0; i < elem_num; i++){
        char* elem = (char*)vec_get(i, &vec);
        ASSERT_STREQ(test_str, elem);
    }
    vec_release(NULL, &vec);
}

TEST(VecGetTest, BigIndexElemGetTest){
    const size_t big_index = 5;
    Vector vec;
    vec_init(&vec);
    size_t elem_num = 3;
    char* test_str = "111";
    for (size_t i = 0; i < elem_num; i++)
        vec_push(test_str, &vec);
    char* elem = (char*)vec_get(big_index, &vec);
    ASSERT_STREQ(elem, NULL);
    vec_release(NULL, &vec);
}

TEST(VecGetTest, NullVecGetTest){
    char* elem = (char*)vec_get(0, NULL);
    ASSERT_STREQ(elem, NULL);
}

//Тестирование функции удаления из вектора
TEST(VecReleadeTest, StaticElemReleaseTest){
    const size_t big_index = 5;
    Vector vec;
    vec_init(&vec);
    size_t elem_num = 3;
    char* test_str = "111";
    for (size_t i = 0; i < elem_num; i++)
        vec_push(test_str, &vec);
    ASSERT_EQ(vec_release(NULL, &vec), 0);
    ASSERT_EQ(vec.size, 0);
    ASSERT_EQ(vec.alloc_size, 0);
}

TEST(VecReleadeTest, DynamicElemReleaseTest){
    const size_t big_index = 5;
    Vector vec;
    vec_init(&vec);
    size_t elem_num = 3;
    char* test_str = "111";
    for (size_t i = 0; i < elem_num; i++)
        vec_push(strdup(test_str), &vec);
    ASSERT_EQ(vec_release(free, &vec), 0);
    ASSERT_EQ(vec.size, 0);
    ASSERT_EQ(vec.alloc_size, 0);
}

TEST(VecReleadeTest, NULLVecReleaseTest) {
    ASSERT_EQ(vec_release(NULL, NULL), -1);
}