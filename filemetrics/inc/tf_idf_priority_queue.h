#pragma once
#include <stdlib.h>
#include "tf_idf_data.h"

//Очередь с приоритетом для tf-idf метрик
typedef struct{
    Tf_Idf* array;      //массив содержащий tf-idf метрики
    size_t size;        //Количество элементов в массиве
    size_t alloc_size;  //Максимальное количество элементов в массиве
}Tf_IdfPriorityQueue;

int pq_init(Tf_IdfPriorityQueue* queue, size_t alloc_size);
int pq_push(double tf_idf, size_t index_in_word_tf_arr, Tf_IdfPriorityQueue* queue);
int64_t pq_pop(Tf_IdfPriorityQueue* queue, Tf_Idf* tf_idf);
void pq_release(Tf_IdfPriorityQueue* queue);

/*
 * pq_init - инициализирует очередь с приоритетом
 * 1 аргумент - очередь, 2 аргумент - макчимальное количество элементов в очереди
 * pq_push - добавляет элементы в очередь
 * 1 аргумент - tf-idf метрика, по которой происходит просеивание, 2 аргумент - индекс в массиве слов, 3 аргумент - очередь
 * pq_pop - извлекает элемент из очереди
 * 1 аргумент - очередь, 2 аргумент - tf-idf метрика
 * возвращает индекс слова, к которому привязана данная метрика, в случае неудачи возвращает -1
 * pq_release - освобождает память, выделенную под очередь
 */