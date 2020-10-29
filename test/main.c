#include <stdio.h>
#include <time.h>
#include "string.h"

#define FROZE_SPEED_NUM 10
#define MAX_TEST_PROC_OUTPUT_SIZE 100000
#define MAX_COMMAND_LENGTH 500

/*
 * В этом таргете через popen вызываются 2 прграммы, многопоточная и однопоточная
 */
int main() {
    const char* multi_thread_test_path = "./../../multi_thread_test/build/multi_thread_test";
    const char* single_thread_test_path = "./../../non_thread_test/build/non_thread_test";
    //замер скорости однопоточного варианта
    double non_thread_speed = 0;
    for (size_t i = 0; i < FROZE_SPEED_NUM; i++){
        clock_t  current_time = clock();
        FILE* non_thread_proc = popen(single_thread_test_path, "r");
        current_time =  clock() - current_time;
        non_thread_speed+=(double)current_time / CLOCKS_PER_SEC;
        fclose(non_thread_proc);
    }
    non_thread_speed = non_thread_speed / FROZE_SPEED_NUM;
    //замер скорости многопоточного варианта
    int thread_num = 2;
    double multi_thread_speed = 0;
    char command[MAX_COMMAND_LENGTH];
    snprintf(command, sizeof command, "%s %d", multi_thread_test_path,thread_num);
    for (size_t i = 0; i < FROZE_SPEED_NUM; i++){
        clock_t  current_time = clock();
        FILE* multy_thread_proc = popen(command, "r");
        current_time =  clock() - current_time;
        multi_thread_speed+= (double)current_time / CLOCKS_PER_SEC;
        fclose(multy_thread_proc);
    }
    multi_thread_speed= multi_thread_speed / FROZE_SPEED_NUM;

    //сравнение выводов
    FILE* non_thread_proc = popen(single_thread_test_path, "r");
    FILE* multi_thread_proc = popen(command, "r");

    char buf1[MAX_TEST_PROC_OUTPUT_SIZE];
    char buf2[MAX_TEST_PROC_OUTPUT_SIZE];
    size_t buf1_size = fread(buf1, sizeof(char), MAX_TEST_PROC_OUTPUT_SIZE, non_thread_proc);
    size_t buf2_size = fread(buf2, sizeof(char), MAX_TEST_PROC_OUTPUT_SIZE, multi_thread_proc);
    buf1[buf1_size] = '\0';
    buf2[buf2_size] = '\0';
    pclose(multi_thread_proc);
    pclose(non_thread_proc);
    int cmp_res = strcmp(buf2, buf1);
    printf("\n"
           "The average speed of a single-threaded version of the program is %f seconds\n"
           "The average speed of a multi-threaded version of the program is %f seconds\n"
           "The cmp function on a comparison of 2 pins showed %d\n",
           non_thread_speed, multi_thread_speed, cmp_res);
    return 0;
}
