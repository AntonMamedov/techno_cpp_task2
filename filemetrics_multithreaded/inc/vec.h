#pragma once
#include <stdlib.h>

#define DEFAULT_ALLOC_SIZE 34

typedef struct{
    void** array;       //Массив элементов
    size_t size;        //Количество элментов в массиве
    size_t alloc_size;  //Общий размер массива
}Vector;

int vec_init(Vector* vec);
int vec_push(void* elem, Vector* vec);
void* vec_get(size_t index, Vector* vec);
int vec_release(void (*releaser)(void* elem), Vector* vec);

/*
 * vec_init - инициализирует вектор, в случе успеха возвращает 0, иначе -1
 * vec_push - добавляет элемент в вектор, в случае успеха возвразает 0 иначе 1
 * 1 аргумнет - элемент, 2 аргумент - веткор
 * vec_get - предоставляет доступ к элементу веткора по индексу
 * 1 аргумент - индекс, 2 аргумент - вектор
 * vec_release - очищает вектор
 * 1 аргумнет - функция очистки памяти, применимая к каждому элемнету веткора, 2 аргумент - вектор
 * в случе успеха возвращает 0, иначе -1
 */