#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include "file_metric.h"

#define MAX_WORD_LENGTH 256
#define MAX_FILE_PATH_LENGTH 1024
#define NUMBER_OF_TOP_WORDS 5
#define MIN_FILE_NUM_IN_DIR 2
#define IMPOSSIBLE_TO_OPEN "The following files could not be opened."

//Данная структура используется при обходе дерева, для передачи в качестве аргумента для функции выполняющей работу
//на надое дерева
typedef struct{
    StrMap* global_word_map;  //Указатель на дерево подсчета встречаемости слова во всех файлах
    WordTf_idf* word_list;     //Массив слова встреченных в файле
    size_t word_list_size;     //Размер массива слов
    size_t word_list_index;    //Текущий индекс для вставки в массив слов
}WordListFillingData;

void file_word_data_init(FileWordData* data, const char *filename, WordTf_idf* word_list, size_t word_list_size);
int  parse_dir(const char *dir_path, Vector *dest);
int  get_words(const char *file_path, StrMap* word_map);
int  get_tf_metric_for_file(const char *dir_path, FileWordData* data, StrMap* global_word_map);
void get_tf_metric_for_dir(const char *dir_path, DirMetricData *metric_data,
                           size_t start_index_in_vec, size_t block_size);
void calculate_metric_for_dir(DirMetricData *metric_data, size_t start_index_in_vec, size_t block_size);
void word_list_filling(StrMapData* data, WordListFillingData* work_data);
void file_word_data_release(FileWordData* elem);
void file_word_data_releaser(FileWordData* elem);

/*
 * file_word_data_init - функция, инициализирующая структуру FileWordData
 * parse_dir - функция открывет диреткорию и заносит имена текстовых файлов в поле имен в векторе информации о файлах
 * 1 пргумент - путь, 2 аргумент - вектор
 * get_words - открывает, читает и закрывает файл, а также выделяет из файла все слова с помощью дерева слов
 * 1 аргумент - путь к файлу, 2 аргумент - дерево слов, содержащихся в файле
 * В случае успеха возвращает 0, в слуае неуспеха -1
 * get_tf_metric_for_file - функция, разбирающая конкртеный файл, она выделяет из него слова, заполняет
 * этими словами массив word_list, высчитывает для каждого слова tf метрику, а также помещает найденные
 * слова в глобальные map и инкрементирует знаечние счетчика в нем(в случае, если слово уже присутствует,
 * просто инкрементирует)
 * get_tf_metric_for_dir - собирает tf метрики для всех слов в указанном диапозоне файлов в диреткории
 * 1 аргумнет - путь к диреткории, 2 аргумнет - структура, содержащая данные, необходимые для разбора диретктории
 * 3 аргумнет индекс в векторе, с которого следует начинать разбор, количество разбираемых файлов
 * calculate_metric_for_dir - высчитывает все tf-idf метрики для всех слов в указанном диапозоне файлов в директории
 * word_list_filling - данная функция передается в качестве аргумента при обходе локального дерева слов,
 * из ключей локлаьного дерева слов заполняет глоабльную map. В глоабльный map добавляются слова, содержащиеся
 * в локаьном дереве, поле val всех добавленных в глобальный map элементов инкрементируется
 * 1 аргумент - данные содержащиеся в узле локлаьного дерева, 2 аргумент - структура с данными дял работы с функцией
 * file_word_data_release - очищает память, выделенную под FileWordData
 * file_word_data_releaser - функция передается в качестве аргумента в функцию очистки вектора, удаляет динамичнески
 * созданные экземпляры структуры FileWordData и очищает память, выделенную внутри этой структуры
 */

void file_word_data_init(FileWordData* data, const char *filename, WordTf_idf *word_list, size_t word_list_size){
    data->file_name = strdup(filename);
    data->word_list = word_list;
    data->word_list_size = word_list_size;
    pq_init(&data->idf_queue, 0);
}

int get_words(const char *file_path, StrMap* word_map){
    if (word_map == NULL || file_path == NULL)
        return -1;
    else {
        FILE *file = fopen(file_path, "rt");
        if (file == NULL)
            return -1;
        else {
            char buf[MAX_WORD_LENGTH + 1];
            char sym;
            //По слову читаем из файла
            for (int len = 0; (sym = (char) fgetc(file)) != EOF; len++) {
                if (len == MAX_WORD_LENGTH) {
                    fclose(file);
                    return -1;
                }
                //Если встречаем символ, являющийся небуквой и нецифрой, заносим слово с локальное дерево
                if (isalnum(sym) == 0 && len != 0) {
                    buf[len] = '\0';
                    StrMapData *data = map_insert_or_search(buf, word_map, &len);
                    data->val += 1;
                    len = -1;
                }
                    //Если мы встречаем символ не являющийся буковй или цифрой и len = 0, делаем len = -1
                else if (isalnum(sym) == 0 && len == 0)
                    len--;
                else
                    buf[len] = (char) tolower(sym);
            }
            fclose(file);
            return word_map->size > 0 ? 0 : -1;
        }
    }
}

int get_tf_metric_for_file(const char *dir_path, FileWordData* data, StrMap* global_word_map){
    if (data == NULL || dir_path == NULL)
        return - 1;
    else {
        //Объединение путя к директории и имя файла
        char file_path[MAX_FILE_PATH_LENGTH];
        if (dir_path[strlen(dir_path) - 1] == '/')
            snprintf(file_path, sizeof file_path, "%s%s", dir_path, data->file_name);
        else
            snprintf(file_path, sizeof file_path, "%s/%s", dir_path, data->file_name);
        //Инициализация дерева подсчета слов в конкретном файле
        StrMap word_map;
        map_init(&word_map);
        //Заполнение дерева
        //Если файл не открылся, возвращаем -1
        if (get_words(file_path, &word_map) == 0){
            //Создаем массив слов в файле, равный размеру дерева
            data->word_list = (WordTf_idf*)malloc(sizeof(WordTf_idf) * word_map.size);
            data->word_list_size = word_map.size;
            //Заполняем структуру, для передачи в функцию обхода
            WordListFillingData filling_data =
                    {global_word_map,
                     data->word_list,
                     data->word_list_size,
                     0};
            //Инкрементируем счетчик слов в глобальном дереве и заполняем массив слов в файле
            map_pre_order(&word_map, (void (*)(StrMapData*, void*))word_list_filling, &filling_data);
            //Очищаем локальное дерево
            map_release(&word_map);
            return 0;
        }
        else
            return -1;

    }
}

void get_tf_metric_for_dir(const char *dir_path, DirMetricData *metric_data, size_t start_index_in_vec, size_t block_size) {
    if (dir_path == NULL || metric_data == 0 || block_size == 0){
        return;
    }
    else {
        //Применяем функцию get_tf_metric_for_file для каждого файла директории
        for (size_t i = start_index_in_vec; i < start_index_in_vec + block_size; i++) {
            FileWordData *file_data =(FileWordData*) vec_get(i, &metric_data->file_info_vec);
            if (file_data != NULL) {
                //Если файл не открылся, чистим память под структуру и помечаем ячейку массива как NULL
                //А так же добавляем имя файла в веткор, содержащий имена неоткрывшихся файлов
                if (get_tf_metric_for_file(dir_path, file_data, &metric_data->global_word_map) == -1)
                    vec_push(strdup(file_data->file_name), &metric_data->file_error_vec);
            }
        }
    }
}

void calculate_metric_for_dir(DirMetricData *metric_data, size_t start_index_in_vec, size_t block_size) {
    //Считаем tf idf для каждого слова в каждом файле директории
    //Метрики помещаем в очередь с приоритетом
    for (size_t i = start_index_in_vec; i < start_index_in_vec + block_size; i++){
        FileWordData *file_data = (FileWordData*)vec_get(i, &metric_data->file_info_vec);
        if (file_data->word_list_size != 0) {
            pq_init(&file_data->idf_queue, file_data->word_list_size);
            for (size_t j = 0; j < file_data->word_list_size; j++) {
                double tf_idf = file_data->word_list[j].tf *
                                log10((double) (metric_data->file_info_vec.size - metric_data->file_error_vec.size) /
                                      (double) file_data->word_list[j].word->val);
                pq_push(tf_idf, j, &file_data->idf_queue);
            }
        }
    }
}

void word_list_filling(StrMapData* data, WordListFillingData* work_data){
    int flag = 0;
    //Добавляем в дерево подсчета частоты встречаемости слова во всех файлах слово и инкрментируем счетчик слов
    StrMapData* global_tre_node_data = map_insert_or_search(str_get(&data->key), work_data->global_word_map, &flag);
    global_tre_node_data->val+= 1;
    //В текущий индекс массива вставляем указатель на поле дата глобального дерева, содержащее слово
    work_data->word_list[work_data->word_list_index].word = global_tre_node_data;
    work_data->word_list[work_data->word_list_index].tf = (double)data->val / (double)work_data->word_list_size;
    //Инкрементируем индекс
    work_data->word_list_index+= 1;
}

void file_word_data_release(FileWordData* elem) {
    free(elem->word_list);
    free(elem->file_name);
    pq_release(&elem->idf_queue);
    elem->word_list_size = 0;
}

void file_word_data_releaser(FileWordData *elem) {
    file_word_data_release(elem);
    free(elem);
}

int top_words_for_dir_out(FILE *out_stream, DirMetricData *metric_data) {
    if (out_stream == NULL || metric_data == NULL)
        return -1;
    else {
        //Вывод первых 5 слов в очереди
        for (size_t i = 0; i < metric_data->file_info_vec.size; i++) {
            FileWordData *file_data = (FileWordData*)vec_get(i, &metric_data->file_info_vec);
            fprintf(out_stream, "%s\n", file_data->file_name);
            for (size_t j = 0; j < NUMBER_OF_TOP_WORDS; j++) {
                if (j < file_data->word_list_size) {
                    Tf_Idf tf_idf;
                    uint64_t index = pq_pop(&file_data->idf_queue, &tf_idf);
                    fprintf(out_stream, "  %s\n", str_get(&file_data->word_list[index].word->key));
                }
            }
        }
        //Вывод ошибок
        if (metric_data->file_error_vec.size > 0) {
            fprintf(out_stream, "%s\n", IMPOSSIBLE_TO_OPEN);
            for (size_t i = 0; i < metric_data->file_error_vec.size; i++)
                fprintf(out_stream, "  %s\n", (char *) vec_get(i, &metric_data->file_error_vec));
        }
        return 0;
    }
}

int get_metric_for_dir(char *dir_path, DirMetricData *metric_data) {
    if (dir_path == NULL || metric_data == NULL)
        return INCORRECT_ARGS;
    else if (metric_data->global_word_map.root != NULL || metric_data->file_error_vec.array != NULL ||
        metric_data->file_info_vec.array != NULL){
        return DATA_METRICS_NOT_INITIALIZED;
    }
    else{
        //Заносим в этот вектор имена всех файлов в директории
        //Если диреткория не найдена, возвращаем -1
        if (parse_dir(dir_path, &metric_data->file_info_vec) == -1)
            return DIRECTORY_NOT_FOUND;
        else{
            //Если в директории меньше 2 файлов, то tf-idf метрики вычислить невозможно
            if (metric_data->file_info_vec.size < MIN_FILE_NUM_IN_DIR){
                vec_release((void (*)(void*))file_word_data_releaser, &metric_data->file_info_vec);
                return UNCATCHABLE_METRIC;
            }
            else{;
                //Собираем в вектор file_info_vec слова встреченные в файле и их tf метрики
                get_tf_metric_for_dir(dir_path, metric_data, 0,
                                      metric_data->file_info_vec.size);
                //Высчитываем для каждого файла в векторе tf-idf метрику
                calculate_metric_for_dir(metric_data, 0, metric_data->file_info_vec.size);
                return 0;
            }
        }
    }
}

int dir_metric_data_init(DirMetricData *data) {
    if (data == NULL)
        return -1;
    else{
        vec_init(&data->file_info_vec);
        vec_init(&data->file_error_vec);
        map_init(&data->global_word_map);
        return 0;
    }
}

void dir_metric_data_release(DirMetricData *data) {
    if (data == NULL)
        return;
    vec_release((void(*)(void*))file_word_data_releaser, &data->file_info_vec);
    vec_release(free, &data->file_error_vec);
    map_release(&data->global_word_map);
}

int parse_dir(const char *dir_path, Vector *dest) {
    if (dir_path == NULL || dest == NULL)
        return -1;
    else {
        struct dirent *dir;
        DIR *sought_dir = opendir(dir_path);
        if (sought_dir != NULL) {
            while ((dir = readdir(sought_dir)) != NULL) {
                if (dir->d_type == DT_REG) {
                    FileWordData *file_data = (FileWordData *) malloc(sizeof(FileWordData));
                    file_word_data_init(file_data, dir->d_name, NULL, 0);
                    vec_push(file_data, dest);
                }
            }
            closedir(sought_dir);
            return dest->size;
        } else
            return -1;
    }
}


