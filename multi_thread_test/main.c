#include <stdio.h>
#include <file_metric.h>

int main(int argc, char** argv) {
    int thread_num = atoi(argv[2]);
    DirMetricData metric_data;
    dir_metric_data_init(&metric_data, thread_num);
    get_metric_for_dir(argv[1], &metric_data);
    top_words_for_dir_out(stdout, &metric_data);
    dir_metric_data_release(&metric_data);
    return 0;
}
