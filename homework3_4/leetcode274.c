#include "leetcode274.h"

/*
函数名：Compare
功能：比较两个整数的大小。
参数：
    a: 第一个整数
    b: 第二个整数
返回值：
    如果第一个整数小于第二个整数，返回负值；如果相等，返回0；如果大于，返回正值。
*/
int Compare(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

/*
函数名：hIndex
功能：计算h指数。
参数：
    citations: 引用次数数组
    citationsSize: 引用次数数组的大小
返回值：
    h指数
*/
int hIndex(int *citations, int citationsSize)
{
    // 从小到大给文章的引用次数数组排序
    qsort(citations, citationsSize, sizeof(int), Compare);
    // 从0开始判断是否满足h指数条件
    int h = 0, i = citationsSize - 1;
    while (i >= 0 && citations[i] > h) {
        h++;
        i--;
    }
    // 返回h指数
    return h;
}