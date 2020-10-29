#include <stdio.h>
#include <file_metric.h>

int main() {
    DirMetricData metric_data;
    dir_metric_data_init(&metric_data);
    get_metric_for_dir("../../test_dirs/main_test_dir", &metric_data);
    top_words_for_dir_out(stdout, &metric_data);
    dir_metric_data_release(&metric_data);
    return 0;
}
