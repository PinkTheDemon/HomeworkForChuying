#include <stdlib.h>

#include "leetcode532.h"

/*
函数名：Compare
功能：比较两个整数的大小，用于qsort排序
参数：
    a: 指向第一个整数的指针
    b: 指向第二个整数的指针
返回值：
    如果a小于b，返回负数；如果a等于b，返回0；如果a大于b，返回正数
*/
int Compare(const void *a, const void *b)
{
    return *((int*)a) - *((int*)b);
}

/*
函数名：FindPairs
功能：查找数组中所有k-diff对的数量
参数：
    nums: 输入的整数数组
    numsSize: 数组的大小
    k: 差值k
返回值：
    数组中所有k-diff对的数量
*/
int FindPairs(int *nums, int numsSize, int k) {
    // 特殊情况处理：nums只有一个元素
    if (1 == numsSize) {
        return 0;
    }
    // 从小到大排序
    qsort(nums, numsSize, sizeof(int), Compare);
    // 双指针查找k-diff对
    int left = 0, right = 1;
    int ret = 0;
    while (right < numsSize) {
        if (nums[right] - nums[left] < k) {
            right++;
        } else if (nums[right] - nums[left] > k) {
            left++;
        } else {
            if (left < right) {
                ret++;
                right++;
                while (right < numsSize && nums[right] == nums[right - 1]) {
                    right++;
                }
            } else {
                right++;
            }
        }
    }
    return ret;
}