#ifdef __cplusplus
extern "C" {
#endif

#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>  // for size_t
#include <stdbool.h>

#define MAX_LOGS 1000
#define LOG_FILE "log.txt"

#define MAX_MESSAGE_LENGTH 256
#define MAX_TRACKED_LOGS 256

// 判断某条日志是否应该打印（基于打印频率限制）
int should_print_log(const char *message);

// 日志结构体
typedef struct {
    char timestamp[20];     // 格式 "YYYY-MM-DD HH:MM"
    char message[256];      // 日志内容
} log_entry_t;

// 日志模块
void add_log_entry(const char *message);
void load_logs(log_entry_t *logs, int *count);
void save_logs(const log_entry_t *logs, int count);
void sort_logs(log_entry_t *logs, int count);
void search_logs(log_entry_t *logs, int count, const char *keyword);

// 工具模块
int get_current_time(char *buffer, size_t size);
int is_one_hour_since_last_log(const char *last_time);

#endif

#ifdef __cplusplus
}
#endif