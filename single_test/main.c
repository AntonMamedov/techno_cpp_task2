#include <stdio.h>
#include "file_metric.h"
int main(int argc, char** argv) {
    if (argc < 2){
        return -1;
    }
    else{
        char* dir_path = argv[1];
        DirMetricData data;
        dir_metric_data_init(&data);
        get_metric_for_dir(dir_path, &data);
        top_words_for_dir_out(stdout, &data);
        dir_metric_data_release(&data);
        return 0;
    }
}
