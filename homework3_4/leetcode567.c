#include "leetcode567.h"

#define CHARNUM 26

/*
函数名：CheckInclusion
功能：检查字符串s2中是否包含字符串s1的排列
参数：
    s1：要检查的字符串
    s2：要搜索的字符串
返回值：
    如果s2中包含s1的排列，返回true；否则返回false
*/
bool CheckInclusion(char *s1, char *s2) {
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    if (s1_len > s2_len) {
        return false;
    }
    // 定义两个数组来存储字符出现的次数
    int s1_count[CHARNUM] = {0};
    int s2_count[CHARNUM] = {0};
    // 统计s1和s2中前s1_len个字符的出现次数
    for (int i = 0; i < s1_len; i++) {
        s1_count[s1[i] - 'a']++;
        s2_count[s2[i] - 'a']++;
    }
    // 滑动窗口遍历s2，从s2的第一个字符开始，直到s2_len - s1_len
    for (int i = 0; i <= s2_len - s1_len; i++) {
        if (i > 0) {
            s2_count[s2[i - 1] - 'a']--;
            s2_count[s2[i + s1_len - 1] - 'a']++;
        }
        if (memcmp(s1_count, s2_count, sizeof(s1_count)) == 0) {
            return true;
        }
    }
    // 如果没有找到匹配的排列，返回false
    return false;
}