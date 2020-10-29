#include "tf_idf_priority_queue.h"

#define INDEX_DELIM 2

void swap(Tf_Idf* fist, Tf_Idf* second);
void fix_up(size_t index, Tf_Idf* p_queue);
void fix_down(size_t index, size_t size, Tf_Idf* p_queue);
/*
 * swap - обмен узлов очереди
 * fix_up - восстановление пирамидальной структуры путем всплытия
 * fix_down - восстановления пирамидальной структуры путем погружения
 */

void fix_up(size_t index, Tf_Idf* p_queue){
    if (p_queue == NULL)
        return;
    while(index > 1 && p_queue[index / INDEX_DELIM].tf_idf < p_queue[index].tf_idf){
        swap(&p_queue[index / INDEX_DELIM], &p_queue[index]);
        index/= 2;
    }
}

void fix_down(size_t index, size_t size, Tf_Idf* p_queue){
    if (p_queue == NULL)
        return;
    while(2 * index < size){
        int j = INDEX_DELIM * index;
        if (j < size && p_queue[j].tf_idf < p_queue[j + 1].tf_idf)
            j++;
        if (p_queue[index].tf_idf >= p_queue[j].tf_idf)
            break;
        swap(&p_queue[index], &p_queue[j]);
        index = j;
    }
}

int pq_init(Tf_IdfPriorityQueue* queue, size_t alloc_size){
    if (queue == NULL)
        return -1;
    else {
        if (alloc_size != 0) {
            queue->array = (Tf_Idf *) malloc(sizeof(Tf_Idf) * ++alloc_size);
            if (queue->array == NULL)
                return -1;
        } else
            queue->array = NULL;
        queue->alloc_size = alloc_size;
        queue->size = 1;
        return 0;
    }
}

int pq_push(double tf_idf, size_t index_in_word_tf_arr, Tf_IdfPriorityQueue* queue){
    if (queue == NULL)
        return -1;
    else {
        if (queue->size < queue->alloc_size) {
            queue->array[queue->size].tf_idf = tf_idf;
            queue->array[queue->size].index_in_word_tf_arr = index_in_word_tf_arr;
            fix_up(queue->size, queue->array);
            queue->size++;
            return 0;
        } else
            return -1;
    }
}

int64_t pq_pop(Tf_IdfPriorityQueue* queue, Tf_Idf* tf_idf){
    if (tf_idf == NULL)
        return -1;
    else if(queue == NULL || queue->size == 1){
        tf_idf->index_in_word_tf_arr = 0;
        tf_idf->tf_idf = 0.0;
        return -1;
    }
    else {
        *tf_idf = queue->array[1];
        queue->array[1].tf_idf = 0;
        queue->array[1].index_in_word_tf_arr = 0;
        swap(&queue->array[1], &queue->array[--queue->size]);
        fix_down(1, queue->size, queue->array);
        return tf_idf->index_in_word_tf_arr;
    }
}

void pq_release(Tf_IdfPriorityQueue *queue) {
    if (queue == NULL)
        return;
    free(queue->array);
    queue->size = 1;
    queue->alloc_size = 0;
    queue->array = NULL;
}

void swap(Tf_Idf* fist, Tf_Idf* second){
    if (fist == NULL || second == NULL)
        return;
    Tf_Idf temp = *fist;
    *fist = *second;
    *second = temp;
}