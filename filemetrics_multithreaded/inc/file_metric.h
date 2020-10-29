#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "str_map.h"
#include "tf_idf_priority_queue.h"
#include "tf_idf_data.h"
#include "vec.h"
#include "hash_map.h"
#include "pthread.h"
#define INCORRECT_ARGS -1
#define DATA_METRICS_NOT_INITIALIZED -2
#define DIRECTORY_NOT_FOUND -3
#define UNCATCHABLE_METRIC -4

//Структура запалняемая при разборе конкретного файла
typedef struct{
    char* file_name;                 //Имя обрабатываемого файла
    WordTf_idf* word_list;           //Массив вслов, встречающихся в этом файле
    Tf_IdfPriorityQueue idf_queue;   //Очередь с приоритетом, содержащая tf_idf метрики и индекс слова в word_list
    size_t word_list_size;           //Размер массива word_list
}FileWordData;

//Структура, содержащая в себе информацию, необходимую для сбора метрик с файлов диреткории
typedef struct {
    Vector file_info_vec;    //Вектор структур, содержащих имя файла, тф метрику и tf-idf метрику
    Vector file_error_vec;   //Вектор, содерджащий имена неоткрытых файлов
    HashMap global_word_map;  //Глобальная хеш-таблица слов, содержащее слова и частоту их встречаемсти в файлах
    pthread_mutex_t mutex;
    size_t thread_num;
}   DirMetricData;

int dir_metric_data_init(DirMetricData *data, size_t thread_num);
void dir_metric_data_release(DirMetricData* data);
int  get_metric_for_dir(char *dir_path, DirMetricData *metric_data);
int top_words_for_dir_out(FILE *out_stream, DirMetricData *metric_data);

/*
 * dir_metric_data_init - инициализирует структуру DirMetricData начальными значениями,
 * возвращает -1 при неудаче, 0 при удаче
 * dir_metric_data_release - очищает память, выделенную внутри структуры
 * get_metric_for_dir - отбирает файлы в директории, разбирает их на слова, и высчитывает метрики
 * 1 аргумент - путь к директории, 2 аргумент - структура с данными о директории
 * в случае успех возвращает 0, иначе один из кодов ошибки
 * top_words_for_dir_out - выводит в указанный поток топ 5 слов для каждого файла
 * 1 аргумент - поток, 2 аргумент - структура с данными о диретории
 * в случае, если аргументы корректные возвращает 0, иначе -1
 */