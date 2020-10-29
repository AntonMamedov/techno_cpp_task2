#include "vec.h"

#define VECTOR_EXTEND_CONST 2

int vec_init(Vector *vec) {
    if (vec == NULL)
        return -1;
    else {
        vec->array = NULL;
        vec->size = 0;
        vec->alloc_size = 0;
        return 0;
    }
}

int vec_push(void* elem, Vector *vec) {
    if (vec == NULL || elem == NULL)
        return -1;
    else {
        if (vec->alloc_size == 0) {
            vec->alloc_size = DEFAULT_ALLOC_SIZE;
            vec->array = (void**)malloc(sizeof(void*) * DEFAULT_ALLOC_SIZE);
            if (vec->array == NULL)
                return -1;
            else {
                vec->array[vec->size++] = elem;
                return 0;
            }
        } else {
            if (vec->size < vec->alloc_size)
                vec->array[vec->size++] = elem;
            else {
                void **temp_vec = (void**)realloc(vec->array, sizeof(void *) * vec->alloc_size * VECTOR_EXTEND_CONST);
                if (temp_vec == NULL)
                    return -1;
                else {
                    if (temp_vec != vec->array)
                        vec->array = temp_vec;
                    vec->alloc_size *= VECTOR_EXTEND_CONST;
                    vec->array[vec->size++] = elem;
                }
            }
            return 0;
        }
    }
}

void *vec_get(size_t index, Vector *vec) {
    if (vec == NULL)
        return NULL;
    else{
        if (index > vec->size)
            return NULL;
        else
            return vec->array[index];
    }
}

int vec_release(void (*releaser)(void*), Vector *vec) {
    if (vec == NULL)
        return -1;
    else {
        if (releaser != NULL) {
            for (size_t i = 0; i < vec->size; i++)
                releaser(vec->array[i]);
        }
        free(vec->array);
        vec->size = 0;
        vec->alloc_size = 0;
        vec->array = NULL;
        return 0;
    }
}
