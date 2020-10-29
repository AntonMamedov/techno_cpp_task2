#include <stdio.h>
#include <stdlib.h>
#include "file_metric.h"
int main(int argc, char** argv) {
    if (argc < 3){
        return -1;
    }
    else{
        const char* dir_path = argv[1];
        int thread_num = atoi(argv[2]);
        DirMetricData data;
        dir_metric_data_init(&data, thread_num);
        get_metric_for_dir(dir_path, &data);
        top_words_for_dir_out(stdout, &data);
        dir_metric_data_release(&data);
        return 0;
    }
}
