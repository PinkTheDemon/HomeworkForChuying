#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "logger.h"

// 用于测试前的清理和准备
void ClearLogFile() {
    std::remove(LOG_FILE);
}

// 模拟日志写入和读取测试
TEST(LoggerTest, AddAndLoadLog) {
    ClearLogFile();

    add_log_entry("测试日志1");
    add_log_entry("测试日志2");

    log_entry_t logs[MAX_LOGS];
    int count = 0;
    load_logs(logs, &count);

    ASSERT_EQ(count, 2);
    EXPECT_STREQ(logs[0].message, "测试日志1");
    EXPECT_STREQ(logs[1].message, "测试日志2");
}

// 时间格式测试
TEST(LoggerTest, TimeFormatCorrectness) {
    char buffer[20];
    int len = get_current_time(buffer, sizeof(buffer));
    ASSERT_GT(len, 0);
    EXPECT_EQ(strlen(buffer), 16);  // YYYY-MM-DD HH:MM
}

// 判断一小时是否过去
TEST(UtilsTest, OneHourCheck) {
    EXPECT_EQ(is_one_hour_since_last_log("2000-01-01 00:00"), 1);  // 肯定过去了
}

// should_print_log 频率控制基本测试
TEST(ShouldPrintTest, FrequencyControl) {
    const char* msg = "重复日志";
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(should_print_log(msg), 1);  // 初始允许
    }
}

// 排序测试
TEST(SortTest, AlphabeticalOrder) {
    log_entry_t logs[3] = {
        {"2025-06-01 12:00", "z消息"},
        {"2025-06-01 12:01", "a消息"},
        {"2025-06-01 12:02", "m消息"}
    };
    sort_logs(logs, 3);
    EXPECT_STREQ(logs[0].message, "a消息");
    EXPECT_STREQ(logs[1].message, "m消息");
    EXPECT_STREQ(logs[2].message, "z消息");
}
