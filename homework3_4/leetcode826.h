#ifndef __LEETCODE826_H__
#define __LEETCODE826_H__

/*
结构体名:   Job
功能:       存储工作的难度和收益
元素:       hard: 工作的难度
            income: 工作的收益
*/
typedef struct Job {
    int hard; // 难度
    int income; // 收益
} Job;

int MaxProfitAssignments(int *difficulty, int *profit, int workerCount, int workerDifficulty);

#endif // __LEETCODE826_H__