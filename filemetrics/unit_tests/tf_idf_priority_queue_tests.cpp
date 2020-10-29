#include "gtest/gtest.h"
extern "C"{
#include "../inc/tf_idf_priority_queue.h"
#include "../src/tf_idf_priority_queue.c"
}

TEST(PQueueInitTest, NormalInitTest){
    const size_t queue_size = 10;
    Tf_IdfPriorityQueue queue;
    ASSERT_EQ(pq_init(&queue, queue_size), 0);
    ASSERT_EQ(queue.size, 1);
    ASSERT_EQ(queue.alloc_size, queue_size+1);
    pq_release(&queue);
}

TEST(PQueueInitTest, NullSizeInitTest){
    const size_t queue_size = 0;
    Tf_IdfPriorityQueue queue;
    ASSERT_EQ(pq_init(&queue, queue_size), 0);
    ASSERT_EQ(queue.size, 1);
    ASSERT_EQ(queue.alloc_size, queue_size);
    pq_release(&queue);
}

TEST(PQueueInitTest, NULLInitTest) {
    const size_t queue_size = 10;
    ASSERT_EQ(pq_init(NULL, queue_size), -1);
}

const size_t test_tf_idf_arr_size = 6;
const double test_tf_idf_val[test_tf_idf_arr_size]= {1.0, 1.8, 3.2, 5.1, 5.6, 9.5};
TEST(PQueueSwapTest, NormalSwapTest){
    Tf_Idf first = {test_tf_idf_val[0], 0};
    Tf_Idf second = {test_tf_idf_val[1], 0};
    swap(&first, &second);
    ASSERT_DOUBLE_EQ(first.tf_idf, test_tf_idf_val[1]);
    ASSERT_DOUBLE_EQ(second.tf_idf, test_tf_idf_val[0]);
}

TEST(PQueueSwapTest, FirstNULLSwapTest){
    Tf_Idf first = {test_tf_idf_val[1], 0};
    swap(&first, NULL);
    ASSERT_DOUBLE_EQ(first.tf_idf, test_tf_idf_val[1]);
}

TEST(PQueuePushTest, NormalPushTest){
    const size_t queue_size = 5;
    Tf_IdfPriorityQueue queue;
    ASSERT_EQ(pq_init(&queue, queue_size), 0);
    for (size_t i = 0; i < queue_size; i++){
        ASSERT_EQ(pq_push(test_tf_idf_val[i], 0, &queue), 0);
    }
    pq_release(&queue);
}

TEST(PQueuePushTest, OverflowPushTest){
    const size_t queue_size = 5;
    Tf_IdfPriorityQueue queue;
    ASSERT_EQ(pq_init(&queue, queue_size), 0);
    for (size_t i = 0; i < queue_size; i++){
        ASSERT_EQ(pq_push(test_tf_idf_val[i], 0, &queue), 0);
    }
    ASSERT_EQ(pq_push(test_tf_idf_val[test_tf_idf_arr_size-1], 0, &queue), -1);
    pq_release(&queue);
}

TEST(PQueuePushTest, NullQusePushTest){
    ASSERT_EQ(pq_push(0, 0, NULL), -1);
}

TEST(PQueuePopTest, NormalPopTest){
    const size_t queue_size = 6;
    Tf_IdfPriorityQueue queue;
    ASSERT_EQ(pq_init(&queue, queue_size), 0);
    for (size_t i = 0; i < queue_size; i++){
        ASSERT_EQ(pq_push(test_tf_idf_val[i], i, &queue), 0);
    }
    for (size_t i = 0; i < queue_size; i++){
        Tf_Idf test_elem;
        ASSERT_EQ(pq_pop(&queue, &test_elem), queue_size - (i + 1));
        ASSERT_DOUBLE_EQ(test_elem.tf_idf, test_tf_idf_val[test_tf_idf_arr_size - (i + 1)]);
        ASSERT_EQ(test_elem.index_in_word_tf_arr, queue_size - (i + 1));
    }
    pq_release(&queue);
}

TEST(PQueuePopTest, EmptyPopTest){
    const size_t queue_size = 6;
    Tf_IdfPriorityQueue queue;
    ASSERT_EQ(pq_init(&queue, queue_size), 0);
    for (size_t i = 0; i < queue_size; i++){
        Tf_Idf test_elem;
        ASSERT_EQ(pq_pop(&queue, &test_elem),  -1);
        ASSERT_DOUBLE_EQ(test_elem.tf_idf, 0.0);
        ASSERT_EQ(test_elem.index_in_word_tf_arr, 0);
    }
    pq_release(&queue);
}

TEST(PQueuePopTest, NullQueuePopTest){
    Tf_Idf test_elem;
    ASSERT_EQ(pq_pop(NULL, &test_elem), -1);
    ASSERT_EQ(test_elem.tf_idf, 0.0);
    ASSERT_EQ(test_elem.index_in_word_tf_arr, 0.0);
}

TEST(PQueuePopTest, NullResElemPopTest){
    const size_t queue_size = 6;
    Tf_IdfPriorityQueue queue;
    ASSERT_EQ(pq_init(&queue, queue_size), 0);
    ASSERT_EQ(pq_pop(&queue, NULL), -1);
    pq_release(&queue);
}

TEST(PQueueReleaseTest, NormalReleaseTest){
    const size_t queue_size = 6;
    Tf_IdfPriorityQueue queue;
    pq_init(&queue, queue_size);
    ASSERT_EQ(queue.size, 1);
    ASSERT_EQ(queue.alloc_size, queue_size + 1);
    for (size_t i = 0; i < queue_size; i++){
        ASSERT_EQ(pq_push(test_tf_idf_val[i], 0, &queue), 0);
    }
    pq_release(&queue);
    ASSERT_EQ(queue.size, 1);
    ASSERT_EQ(queue.alloc_size, 0);

}
