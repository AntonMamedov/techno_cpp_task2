#include <stdio.h>
#include <time.h>
#include "string.h"

#define FROZE_SPEED_NUM 10
#define MAX_TEST_PROC_OUTPUT_SIZE 100000
int main() {
    //замер скорости однопоточного варианта
    double non_thread_speed = 0;
    for (size_t i = 0; i < FROZE_SPEED_NUM; i++){
        clock_t  current_time = clock();
        FILE* non_thread_proc = popen("./../../non_thread_test/build/test", "r");
        current_time =  clock() - current_time;
        non_thread_speed+=(double)current_time / CLOCKS_PER_SEC;
        fclose(non_thread_proc);
    }
    non_thread_speed = non_thread_speed / FROZE_SPEED_NUM;
    //замер скорости многопоточного варианта
    double multy_thread_speed = 0;
    for (size_t i = 0; i < FROZE_SPEED_NUM; i++){
        clock_t  current_time = clock();
        FILE* multy_thread_proc = popen("./../../multi_thread_test/build/test", "r");
        current_time =  clock() - current_time;
        multy_thread_speed+=(double)current_time / CLOCKS_PER_SEC;
        fclose(multy_thread_proc);
    }
    multy_thread_speed= multy_thread_speed / FROZE_SPEED_NUM;

    //сравнение выводов
    FILE* non_thread_proc = popen("./../../non_thread_test/build/test", "r");
    FILE* multy_thread_proc = popen("./../../multi_thread_test/build/test", "r");

    char buf1[MAX_TEST_PROC_OUTPUT_SIZE];
    char buf2[MAX_TEST_PROC_OUTPUT_SIZE];
    size_t buf1_size = fread(buf1, sizeof(char), MAX_TEST_PROC_OUTPUT_SIZE, non_thread_proc);
    size_t buf2_size = fread(buf2, sizeof(char), MAX_TEST_PROC_OUTPUT_SIZE, multy_thread_proc);
    buf1[buf1_size] = '\0';
    buf2[buf2_size] = '\0';
    pclose(multy_thread_proc);
    pclose(non_thread_proc);
    int cmp_res = strcmp(buf2, buf1);
    printf("\n"
           "The average speed of a single-threaded version of the program is %f seconds\n"
           "The average speed of a multi-threaded version of the program is %f seconds\n"
           "The cmp function on a comparison of 2 pins showed %d\n",
           non_thread_speed, multy_thread_speed, cmp_res);
    return 0;
}
