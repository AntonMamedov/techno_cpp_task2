#pragma once
#include <stdlib.h>
#include "str_map.h"

//Данная структура содержит в себе слово и его tf
typedef struct {
    StrMapData* word;  //Указатель на узел в глоабльном дереве, содержащий слово
    double tf;         //tf слова, содержащегося в поле word
}WordTf_idf;

//Данная структура содержит в себе индекс слова в массиве WordTf_idf структур и их tf-idf метрики
typedef struct {
    double tf_idf;                 //метрика
    size_t index_in_word_tf_arr;   //индекс
}Tf_Idf;
