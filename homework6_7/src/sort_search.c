#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logger.h"

// 按 message 字典序排序
void sort_logs(log_entry_t *logs, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (strcmp(logs[i].message, logs[j].message) > 0) {
                log_entry_t tmp = logs[i];
                logs[i] = logs[j];
                logs[j] = tmp;
            }
        }
    }
    printf("日志排序完成。\n");
}

#define MAX_TRACKED_MESSAGES 1024

typedef struct {
    char message[MAX_MESSAGE_LENGTH];
    char last_printed_time[20];  // 格式 "YYYY-MM-DD HH:MM"
} printed_record_t;

// 辅助函数：将 "YYYY-MM-DD HH:MM" 转换为 time_t
time_t parse_to_time(const char *datetime) {
    struct tm tm_time = {0};
    int year, month, day, hour, minute;

    if (sscanf(datetime, "%d-%d-%d %d:%d", &year, &month, &day, &hour, &minute) != 5)
        return (time_t)-1;

    tm_time.tm_year = year - 1900;
    tm_time.tm_mon  = month - 1;
    tm_time.tm_mday = day;
    tm_time.tm_hour = hour;
    tm_time.tm_min  = minute;
    tm_time.tm_sec  = 0;

    return mktime(&tm_time);
}

void search_logs(log_entry_t *logs, int count, const char *keyword) {
    int found = 0;
    printed_record_t printed[MAX_TRACKED_MESSAGES];
    int printed_count = 0;

    printf("搜索关键字: %s\n", keyword);

    for (int i = 0; i < count; ++i) {
        if (!strstr(logs[i].message, keyword)) {
            continue;
        }

        // 构造日志时间戳："YYYY-MM-DD HH:MM"
        char full_time[20];
        snprintf(full_time, sizeof(full_time), "%s %.*s", logs[i].timestamp, 5, logs[i].message);

        time_t current_log_time = parse_to_time(full_time);
        if (current_log_time == (time_t)-1) {
            fprintf(stderr, "日志时间格式错误: %s\n", full_time);
            continue;
        }

        int should_skip = 0;
        for (int j = 0; j < printed_count; ++j) {
            if (strcmp(printed[j].message, logs[i].message) == 0) {
                time_t last_time = parse_to_time(printed[j].last_printed_time);
                if (last_time != (time_t)-1 && difftime(current_log_time, last_time) < 3600) {
                    should_skip = 1;
                } else {
                    strncpy(printed[j].last_printed_time, full_time, sizeof(printed[j].last_printed_time) - 1);
                    printed[j].last_printed_time[sizeof(printed[j].last_printed_time) - 1] = '\0';
                }
                break;
            }
        }

        if (!should_skip) {
            if (should_print_log(logs[i].message)) {
                printf("[%s] %s\n", logs[i].timestamp, logs[i].message);
                if (printed_count < MAX_TRACKED_MESSAGES) {
                    strncpy(printed[printed_count].message, logs[i].message, MAX_MESSAGE_LENGTH - 1);
                    printed[printed_count].message[MAX_MESSAGE_LENGTH - 1] = '\0';
                    strncpy(printed[printed_count].last_printed_time, full_time, sizeof(printed[printed_count].last_printed_time) - 1);
                    printed[printed_count].last_printed_time[sizeof(printed[printed_count].last_printed_time) - 1] = '\0';
                    printed_count++;
                }
                found = 1;
            }
        }
    }

    if (!found) {
        printf("未找到相关日志。\n");
    }
}