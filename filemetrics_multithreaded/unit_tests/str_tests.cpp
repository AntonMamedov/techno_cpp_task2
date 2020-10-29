#include "gtest/gtest.h"
extern "C"{
#include "../inc/str.h"
#include "../src/str.c"
}


TEST(StrInitTest, NormalInitTest){
    String str;
    const char* src_str = "abcd";
    ASSERT_STREQ(src_str, str_init(src_str, &str));
    str_release(&str);
}

TEST(StrInitTest, NULLInitTest){
    String str;
    const char* src_str = NULL;
    ASSERT_EQ(NULL, str_init(src_str, &str));
    str_release(&str);
}

TEST(GetStrTest, GetStaticBufferTest){
    String str;
    const char* src_str = "abcd";
    str_init(src_str, &str);
    ASSERT_STREQ(src_str, str_get(&str));
    str_release(&str);
}

TEST(GetStrTest, GetDynamicBufferTest){
    String str;
    const char* src_str = "123456789987654321123456789";
    str_init(src_str, &str);
    ASSERT_STREQ(src_str, str_get(&str));
    str_release(&str);
}

TEST(GetStrTest, GetNULLBufferTest){
    String str;
    const char* src_str = NULL;
    str_init(src_str, &str);
    ASSERT_EQ(src_str, str_get(&str));
    str_release(&str);
}

TEST(ReleaseStrTest, StaticBufRelease){
    String str;
    const char* src_str = "abcd";
    str_init(src_str, &str);
    str_release(&str);
    ASSERT_EQ(str.length, 0);
}

TEST(ReleaseStrTest, DynamicBufRelease){
    String str;
    const char* src_str = "123456789987654321123456789";
    str_init(src_str, &str);
    str_release(&str);
    ASSERT_EQ(str.length, 0);
}