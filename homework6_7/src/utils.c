#include <stdio.h>
#include <time.h>
#include "logger.h"

#define STARTYEAR 1900
#define HOUR2SECOND 3600

// 获取当前时间 "YYYY-MM-DD HH:MM"
int get_current_time(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    if (!tm_info) return 0;
    return strftime(buffer, size, "%Y-%m-%d %H:%M", tm_info);
}

// 判断是否过去了一小时
int is_one_hour_since_last_log(const char *last_time) {
    struct tm tm_last = {0};
    time_t t_last, t_now;

    int year, month, day, hour, minute;
    if (sscanf(last_time, "%d-%d-%d %d:%d", &year, &month, &day, &hour, &minute) != 5)
        return 1;

    tm_last.tm_year = year - STARTYEAR;
    tm_last.tm_mon  = month - 1;
    tm_last.tm_mday = day;
    tm_last.tm_hour = hour;
    tm_last.tm_min  = minute;
    tm_last.tm_sec  = 0;

    t_last = mktime(&tm_last);
    (void)time(&t_now);

    return difftime(t_now, t_last) >= HOUR2SECOND;
}
