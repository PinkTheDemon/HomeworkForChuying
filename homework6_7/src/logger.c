#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logger.h"

// 添加一条日志
void add_log_entry(const char *message) {
    log_entry_t logs[MAX_LOGS];
    int count = 0;
    char now[20];

    load_logs(logs, &count);
    get_current_time(now, sizeof(now));

    if (count >= MAX_LOGS) {
        printf("日志已满，无法添加新日志。\n");
        return;
    }

    snprintf(logs[count].timestamp, sizeof(logs[count].timestamp), "%s", now);
    snprintf(logs[count].message, sizeof(logs[count].message), "%s", message);
    count++;

    save_logs(logs, count);
    printf("日志添加成功。\n");
}

// 从文件加载日志
void load_logs(log_entry_t *logs, int *count) {
    *count = 0;
    FILE *file = fopen(LOG_FILE, "r");
    if (!file) return;

    // 跳过 UTF-8 BOM（EF BB BF）
    unsigned char bom[3];
    fread(bom, 1, 3, file);
    if (!(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)) {
        fseek(file, 0, SEEK_SET); // 没有 BOM，回退
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // 去除行尾换行
        line[strcspn(line, "\r\n")] = '\0';

        // 拆分为 timestamp（两部分）和 message
        char date[11] = {0};   // YYYY-MM-DD
        char time[6]  = {0};   // HH:MM
        char message[256] = {0};

        int matched = sscanf(line, "%10s %5s %[^\n]", date, time, message);
        if (matched == 3) {
            snprintf(logs[*count].timestamp, sizeof(logs[*count].timestamp), "%s %s", date, time);
            strncpy(logs[*count].message, message, sizeof(logs[*count].message) - 1);
            (*count)++;
            if (*count >= MAX_LOGS) break;
        }
        // 否则是格式错误行，自动跳过
    }

    fclose(file);
}

// 保存日志到文件
void save_logs(const log_entry_t *logs, int count) {
    FILE *file = fopen(LOG_FILE, "w");

    if (!file) {
        perror("日志写入失败");
        return;
    }

    // 写入 UTF-8 BOM（防止中文乱码，尤其是 Notepad 和部分终端）
    unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    (void)fwrite(bom, sizeof(bom), 1, file);

    for (int i = 0; i < count; ++i) {
        (void)fprintf(file, "%s %s\n", logs[i].timestamp, logs[i].message);
    }

    (void)fclose(file);
}

typedef struct {
    char message[MAX_MESSAGE_LENGTH];
    time_t first_seen;
    int count_within_minute;
    time_t suppress_until;
    time_t last_printed;
} log_print_state_t;

static log_print_state_t print_states[MAX_TRACKED_LOGS];
static int state_count = 0;

int should_print_log(const char *message) {
    time_t now = time(NULL);

    for (int i = 0; i < state_count; ++i) {
        if (strcmp(print_states[i].message, message) == 0) {
            if (now <= print_states[i].suppress_until) {
                if (now - print_states[i].last_printed >= 3600) {
                    print_states[i].last_printed = now;
                    return 1; // 每小时打印一次
                }
                return 0; // 抑制中
            }

            // 在一分钟内
            if (now - print_states[i].first_seen <= 60) {
                print_states[i].count_within_minute++;
                if (print_states[i].count_within_minute >= 60) {
                    print_states[i].suppress_until = now + 3600;
                    print_states[i].last_printed = now;
                    return 1; // 打印一条后开始抑制
                }
            } else {
                // 超过一分钟，重置计数
                print_states[i].first_seen = now;
                print_states[i].count_within_minute = 1;
            }
            return 1;
        }
    }

    // 新日志内容，加入追踪
    if (state_count < MAX_TRACKED_LOGS) {
        strncpy(print_states[state_count].message, message, MAX_MESSAGE_LENGTH - 1);
        print_states[state_count].message[MAX_MESSAGE_LENGTH - 1] = '\0';
        print_states[state_count].first_seen = now;
        print_states[state_count].count_within_minute = 1;
        print_states[state_count].suppress_until = 0;
        print_states[state_count].last_printed = now;
        state_count++;
    }

    return 1;
}
