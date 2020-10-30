#include <string.h>
#include "str_map.h"

StrMapNode *map_node_init(const char *key);
StrMapData* local_map_insert_or_search(char *key, StrMapNode *node, int* flag, size_t* size);
void local_map_release(StrMapNode* node);
void local_map_pre_order(StrMapNode* node, void (*work)(StrMapData *, void *), void *data_for_work);
/*
 * map_node_init - создает и инцициализирует узел дерева, на вход принимает ключ
 * Остальные функции - локальные копии объявленных в .h файле пользовательский функций, вместо
 * указателя на на инкопсулирующую в себе корень структуры, принимают указатель на ноду дерева
 */

int map_init(StrMap *map){
    if (map == NULL)
        return -1;
    else {
        map->root = NULL;
        map->size = 0;
        return 0;
    }
}

StrMapData *map_insert_or_search(char *key, StrMap *map, int* flag){
    if (key == NULL || flag == NULL)
        return NULL;
    else {
        *flag = INSERTED;
        if (map->root == NULL) {
            map->root = map_node_init(key);
            map->size+= 1;
            return &map->root->data;
        } else {
            int cmp = strcmp(str_get(&map->root->data.key), key);
            if (cmp > 0) {
                if (map->root->right == NULL) {
                    map->root->right = map_node_init(key);
                    map->size+=1;
                    return &map->root->right->data;
                } else
                    return local_map_insert_or_search(key, map->root->right, flag, &map->size);
            } else if (cmp < 0) {
                if (map->root->left == NULL) {
                    map->root->left = map_node_init(key);
                    map->size+=1;
                    return &map->root->left->data;
                } else
                    return local_map_insert_or_search(key, map->root->left, flag, &map->size);
            } else{
                *flag = FOUND;
                return &map->root->data;
            }
        }
    }
}

StrMapData* local_map_insert_or_search(char *key, StrMapNode *node, int* flag, size_t* size){
    if (key == NULL || flag == NULL || node == NULL)
        return NULL;
    else {
        int cmp = strcmp(str_get(&node->data.key), key);
        if (cmp > 0) {
            if (node->right == NULL) {
                node->right = map_node_init(key);
                *size+=1;
                return &node->right->data;
            } else
                return local_map_insert_or_search(key, node->right, flag, size);
        } else if (cmp < 0) {
            if (node->left == NULL) {
                node->left = map_node_init(key);
                *size+=1;
                return &node->left->data;
            } else
                return local_map_insert_or_search(key, node->left, flag, size);
        } else{
            *flag = FOUND;
            return &node->data;
        }

    }
}

int map_pre_order(StrMap *map, void (*work)(StrMapData* data, void* data_for_work), void *data_for_work){
    if (work == NULL || map == NULL || map->size == 0)
        return -1;
    else {
        work(&map->root->data, data_for_work);
        local_map_pre_order(map->root->left, work, data_for_work);
        local_map_pre_order(map->root->right, work, data_for_work);
        return 0;
    }
}

void local_map_pre_order(StrMapNode* node, void (*work)(StrMapData* data, void* data_for_work), void *data_for_work){
    if (node == NULL)
        return;
    work(&node->data, data_for_work);
    local_map_pre_order(node->left, work, data_for_work);
    local_map_pre_order(node->right, work, data_for_work);
}

int map_release(StrMap *map){
    if (map == NULL || map->size == 0)
        return - 1;
    else {
        local_map_release(map->root->left);
        local_map_release(map->root->right);
        str_release(&map->root->data.key);
        free(map->root->left);
        free(map->root->right);
        free(map->root);
        map->size = 0;
        map->root = NULL;
        return 0;
    }
}

void local_map_release(StrMapNode* node){
    if (node == NULL)
        return;
    local_map_release(node->left);
    local_map_release(node->right);
    str_release(&node->data.key);
    free(node->left);
    free(node->right);
}

StrMapNode *map_node_init(const char *key) {
        if (key == NULL)
            return NULL;
        else {
            StrMapNode* elem = (StrMapNode*)malloc(sizeof(StrMapNode));
            elem->left = NULL;
            elem->right = NULL;
            str_init(key, &elem->data.key);
            elem->data.val = 0;
            return elem;
        }
}