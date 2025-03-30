#include "leetcode46.h"

/*
函数名：Fact
功能：  计算阶乘
入参：  n: 不大于12的正整数
返回值：n的阶乘
*/
int Fact(int n)
{
    int ret = 1;

    for (int i = 2; i <= n; i ++) {
        ret *= i;
    }

    return ret;
}

/*
函数名：Fill
功能：  填充全排列数组
入参：  perm: 全排列的数组
        permSize: 所有排列的个数
        targetLen: 每个排列的长度
        nowLen: 当前已经填充的长度
        labeledNums: 相关数据
返回值：无
*/
void Fill(int** perm, int permSize, int targetLen, int nowLen, LabeledNums* labeledNums)
{
    // 入参检查
    if (nowLen >= targetLen) {
        return;
    }

    // 计算 每个字母需要填充的个数 = 总共需要填充的大小 / 剩余字母数
    int remainNum = targetLen - nowLen;
    int fillNum = permSize / remainNum;

    // 填充
    int iFill = 0; // 记录当前已经填充完毕几个数字
    for (int i = 0; i < labeledNums->numsSize; i++) {
        // 查找剩余可用数字
        if (!labeledNums->isUsed[i]) {
            // 对可用数字进行填充，填充个数为上面计算出的个数
            for (int j = iFill * fillNum; j < (iFill + 1) * fillNum; j++) {
                perm[j][nowLen] = labeledNums->nums[i];
            }
            // 将该数字标记为使用过
            labeledNums->isUsed[i] = true;
            // 如果填充后仍未达到目标长度，需要进一步填充
            if (nowLen + 1 < targetLen) {
                Fill((perm + iFill * fillNum), fillNum, targetLen, (nowLen + 1), labeledNums);
            }
            // 将该数字恢复为未使用
            labeledNums->isUsed[i] = false;
            // iFill增加
            iFill++;
        }
    }

    return;
}

/*
函数名：Permute
功能：  返回一个数组的全排列
入参：  nums: 整型数组
        numsSize: 数组nums的大小
        returnSize: 所返回的排列的个数
        returnColumnSizes: 所返回的各个排列的大小
返回值：所有排列组成的数组
*/
int** Permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    // 计算返回的排列个数，返回值的Size数组初始化
    *returnSize = Fact(numsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    if (returnColumnSizes == NULL) {
        printf("malloc failed!");
        return NULL;
    }

    // 初始化返回值列表以及返回值的列大小
    int** ret = (int**)malloc(sizeof(int*) * (*returnSize));
    if (ret == NULL) {
        printf("malloc failed!");
        return NULL;
    }
    for (int i = 0; i < *returnSize; i++) {
        returnColumnSizes[0][i] = numsSize;
        ret[i] = (int*)malloc(sizeof(int) * numsSize);
        if (ret[i] == NULL) {
            printf("malloc failed!");
            return NULL;
        }
    }

    // 初始化标记数组，并赋全0值
    bool* isUsed = (bool*)malloc(sizeof(bool) * numsSize);
    if (isUsed == NULL) {
        printf("malloc failed!");
        return NULL;
    }
    for (int i = 0; i < numsSize; i++) {
        isUsed[i] = false;
    }

    // 填充返回列表
    LabeledNums* labeledNums = (LabeledNums*)malloc(sizeof(LabeledNums));
    if (labeledNums == NULL) {
        printf("malloc failed!");
        return NULL;
    }
    labeledNums->nums = nums;
    labeledNums->isUsed = isUsed;
    labeledNums->numsSize = numsSize;
    Fill(ret, *returnSize, numsSize, 0, labeledNums);

    return ret;
}