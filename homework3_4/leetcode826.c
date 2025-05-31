#include <stdlib.h>
#include "leetcode826.h"

#define MALLOCERROR -1


/*
函数名: Compare
功能:   根据收益比较两个job结构体的大小
参数：  结构体a，结构体b
返回值：若a的收益大，输出为负；若b的收益大，输出为正；若收益相同，输出为0
*/
int Compare(const void *a, const void *b)
{
    return ((Job*)b)->income - ((Job*)a)->income;
}

/*
函数名: MaxProfitAssignment
功能:   安排工作以达到最大收益
参数：  difficulty: 工作的难度数组
        difficultySize: 难度数组的大小
        profit: 工作的收益数组
        profitSize: 收益数组的大小
        worker: 工人的能力数组
        workerSize: 工人的数量
返回值：把工人分配到工作岗位后，所能获得的最大利润 
*/
int MaxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize)
{
    Job *jobs = malloc(sizeof(Job) * profitSize);
    if (NULL == jobs) {
        printf("jobs malloc fail!");
        return MALLOCERROR;
    }
    // 填充工作数组
    for (int i = 0; i < profitSize; i++) {
        jobs[i].hard = difficulty[i];
        jobs[i].income = profit[i];
    }
    // 从大到小排序工作数组
    qsort(jobs, profitSize, sizeof(Job), Compare);
    // 按收益从大到小依次判断工人是否能完成工作
    int totalProfit = 0;
    for (int i = 0; i < workerSize; i++) {
        for (int j = 0; j < profitSize; j++) {
            if (worker[i] >= jobs[j].hard) {
                totalProfit += jobs[j].income;
                break;
            }
        }
    }
    // 返回总收益
    return totalProfit;
}