#pragma once
#include <stdlib.h>

#define STATIC_STR_DEFAULT_LENGTH 15
//объединение, необходимое для использования small string optimization
typedef union{
    char static_str[STATIC_STR_DEFAULT_LENGTH + 1];  //статический буфер равный 15 + 1 символ для \0
    char* dynamic_str;                               //динамический буфер
}StringData;

//Структура, инкопсулирующая строку и предоставляющая способы работы с ней
typedef struct String{
    size_t length;   //Длина строки
    StringData str;  //Объединение, содержащее строку
}String;

char* str_init(const char* src, String* dest);
char* str_get(String* str);
void str_release(String* str);

/*
 * str_init - копирует строку src в статический буфер, если она меньше 15 и в динамический если больше
 * str_get - возвращает адрес буфера строки, динамического если размер больше 15 и статического если меньше
 * str_release - в случае динамического выделения памяти, очищает динамический буфер
 */