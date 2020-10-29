//#include "gtest/gtest.h"
//
//extern "C"{
//#include "../inc/file_metric.h"
//#include "../src/file_metric.c"
//}
//
//const char* dir1_path = "../../unit_tests/test_dir_1";
//const char* dir2_path = "../../unit_tests/test_dir_2";
//const char* dir3_path = "../../unit_tests/test_dir_3";;
//const size_t dir_num = 3;
//const char* test_dirs[dir_num] = {dir1_path, dir2_path, dir3_path};
//const size_t file_names_num = 3;
//const char* file_names[3] = {"test_file1.txt", "test_file2.txt", "test_file2.txt"};
//
//TEST(ParseDirTest, ParseDirWithSomeFiles){
//    Vector file_info_test_vec;
//    vec_init(&file_info_test_vec);
//    EXPECT_EQ(parse_dir(dir3_path, &file_info_test_vec), dir_num);
//    EXPECT_EQ(file_info_test_vec.size, dir_num);
//    vec_release((void(*)(void*))file_word_data_releaser, &file_info_test_vec);
//}
//
//TEST(ParseDirTest, ParseDirWithoutFiles){
//    Vector file_info_test_vec;
//    vec_init(&file_info_test_vec);
//    EXPECT_EQ(parse_dir(dir1_path, &file_info_test_vec), 0);
//    EXPECT_EQ(file_info_test_vec.size, 0);
//    vec_release((void(*)(void*))file_word_data_releaser, &file_info_test_vec);
//}
//
//TEST(ParseDirTest, ParseDirIncoorectPath){
//    Vector file_info_test_vec;
//    vec_init(&file_info_test_vec);
//    EXPECT_EQ(parse_dir("1", &file_info_test_vec), -1);
//    EXPECT_EQ(file_info_test_vec.size, 0);
//    vec_release((void(*)(void*))file_word_data_releaser, &file_info_test_vec);
//}
//
//TEST(ParseDirTest, ParseDirNULLPath){
//    Vector file_info_test_vec;
//    vec_init(&file_info_test_vec);
//    EXPECT_EQ(parse_dir(NULL, &file_info_test_vec), -1);
//    EXPECT_EQ(file_info_test_vec.size, 0);
//    vec_release((void(*)(void*))file_word_data_releaser, &file_info_test_vec);
//}
//
//TEST(ParseDirTest, ParseDirNULLVec){
//    EXPECT_EQ(parse_dir(dir3_path, NULL), -1);
//}
//
//TEST(GetWordsTEst, NormalGetWordTest){
//    StrMap word_map;
//    map_init(&word_map);
//    char file_path[MAX_FILE_PATH_LENGTH];
//    snprintf(file_path, sizeof file_path, "%s/%s", dir3_path, file_names[0]);
//    get_words(file_path, &word_map);
//    ASSERT_EQ(word_map.size, 6);
//    map_release(&word_map);
//}
//
//TEST(GetWordsTEst, EmptyFileGetWordTest){
//    StrMap word_map;
//    map_init(&word_map);
//    char file_path[MAX_FILE_PATH_LENGTH];
//    snprintf(file_path, sizeof file_path, "%s/%s", dir2_path, file_names[0]);
//    ASSERT_EQ(get_words(file_path, &word_map), -1);
//    map_release(&word_map);
//}
//
//TEST(GetWordsTEst, NULLMapGetWordTest){
//    char file_path[MAX_FILE_PATH_LENGTH];
//    snprintf(file_path, sizeof file_path, "%s/%s", dir2_path, file_names[0]);
//    ASSERT_EQ(get_words(file_path, NULL), -1);
//}
//
//TEST(GetWordsTEst, NULLPathGetWordTest){
//    StrMap word_map;
//    map_init(&word_map);
//    ASSERT_EQ(get_words(NULL, &word_map), -1);
//    map_release(&word_map);
//}
//
//void tester(StrMapData* data, void* ){
//    ASSERT_EQ(data->val, 1);
//}
//
//TEST(GetTfIdfMetricForFile, GetNormalFaile){
//    StrMap global_word_map;
//    map_init(&global_word_map);
//    FileWordData file_data;
//    file_word_data_init(&file_data, file_names[0], NULL, 0);
//    ASSERT_EQ(get_tf_metric_for_file(dir3_path, &file_data, &global_word_map), 0);
//    ASSERT_EQ(global_word_map.size, 6);
//    ASSERT_EQ(file_data.word_list_size, 6);
//    file_word_data_release(&file_data);
//    map_pre_order(&global_word_map, tester, NULL);
//    map_release(&global_word_map);
//}
//
//TEST(GetTfIdfMetricForFile, GetEmptyFaile){
//    StrMap global_word_map;
//    map_init(&global_word_map);
//    FileWordData file_data;
//    file_word_data_init(&file_data, file_names[0], NULL, 0);
//    ASSERT_EQ(get_tf_metric_for_file(dir2_path, &file_data, &global_word_map), -1);
//    ASSERT_EQ(global_word_map.size, 0);
//    ASSERT_EQ(file_data.word_list_size, 0);
//    file_word_data_release(&file_data);
//    map_release(&global_word_map);
//}
//
//TEST(GetTfIdfMetricForFile, GetFaileNULLPath){
//    StrMap global_word_map;
//    map_init(&global_word_map);
//    FileWordData file_data;
//    file_word_data_init(&file_data, file_names[0], NULL, 0);
//    ASSERT_EQ(get_tf_metric_for_file(NULL, &file_data, &global_word_map), -1);
//    file_word_data_release(&file_data);
//    map_release(&global_word_map);
//}
//
//TEST(GetTfIdfMetricForFile, GetFaileNULLFileData){
//    StrMap global_word_map;
//    map_init(&global_word_map);
//    ASSERT_EQ(get_tf_metric_for_file(NULL, NULL, &global_word_map), -1);
//    map_release(&global_word_map);
//}
//
//TEST(GetTfIdfMetricForFile, GetFaileNULLMapData){
//    FileWordData file_data;
//    file_word_data_init(&file_data, file_names[0], NULL, 0);
//    ASSERT_EQ(get_tf_metric_for_file(NULL, NULL, NULL), -1);
//    file_word_data_release(&file_data);
//}