#ifndef __LEETCODE46_H__
#define __LEETCODE46_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
结构体名：LabeledNums
元素：  nums: 整型数组
        isUsed: 数组中对应位置是否使用过的标记
        numsSize: 数组大小
*/
typedef struct LabeledNums{
    int* nums;
    bool* isUsed;
    int numsSize;
} LabeledNums;

int Fact(int n);
void Fill(int** perm, int permSize, int targetLen, int nowLen, LabeledNums* labeledNums);
int** Permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

#endif