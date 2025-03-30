#include "main.h"

#include "leetcode46.c"
#include "leetcode120.c"
#include "leetcode1823.c"

/*
函数名：PrintNums
功能：  打印数组中的所有元素
*/
void PrintNums(int* nums, int numsSize)
{
    // 入参检查
    if (numsSize <= 0) {
        printf("parameters error!");
        return;
    }

    printf("[%d", nums[0]);
    for (int i = 1; i < numsSize; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
    
    return;
}

/*
函数名：PrintNumsOfNums
功能：  打印数组中的所有数组
*/
void PrintNumsOfNums(int** nums, int numsSize, int* numsColSize)
{
    // 入参检查
    if (numsSize <= 0) {
        printf("parameters error!");
        return;
    }

    printf("[");
    PrintNums(nums[0], numsColSize[0]);
    for (int i = 1; i < numsSize; i++) {
        printf(", ");
        PrintNums(nums[i], numsColSize[i]);
    }
    printf("]");

    return;
}

/*
函数名：Free2ndPtr
功能：  释放二级指针指向的各个一级指针的内存
*/
void Free2ndPtr(int** ptr, int ptrSize)
{
    for (int i = 0; i < ptrSize; i++) {
        free(ptr[i]);
        ptr[i] = NULL;
    }

    return;
}

/*
函数名：Test1823
功能：  1823题测试用例1
备注：  如需测试不同用例，修改p1、p2即可
*/
void Test1823()
{
    // 参数定义及初始化
    int p1 = 5;
    int p2 = 2;

    // 测试并打印相关信息
    printf("Case for 1823 : \n  n = %d, k = %d", p1, p2);
    int result = FindTheWinner(p1, p2);
    printf("\n  result = %d.\n", result);

    return;
}

/*
函数名：Test46
功能：  46题测试用例1
备注：  如需测试不同用例，修改a1、p2即可
*/
void Test46()
{
    // 参数定义及初始化
    int a1[] = {1, 2, 3};
    int* p1 = a1;
    int p2 = 3;
    int* p3 = (int*)malloc(sizeof(int));
    if (p3 == NULL) {
        printf("malloc failed!");
        return;
    }
    int** p4 = (int**)malloc(sizeof(int*));
    if (p4 == NULL) {
        printf("malloc failed!");
        return;
    }

    // 测试并打印相关信息
    printf("Case for 46 : \n  nums = ");
    PrintNums(p1, p2);
    printf("\n  result = ");
    int** result = Permute(p1, p2, p3, p4);
    PrintNumsOfNums(result, *p3, *p4);
    printf(".\n");

    // 释放分配的内存
    free(p3);
    p3 = NULL;
    free(p4[0]);
    p4[0] = NULL;
    free(p4);
    p4 = NULL;

    return;
}

/*
函数名：Test120
功能：  120题测试用例1
备注：  如需测试不同用例，修改a1~4、p2即可
*/
void Test120()
{
    // 参数定义及初始化
    int a1[] = {2};
    int a2[] = {3,4};
    int a3[] = {6,5,7};
    int a4[] = {4,1,8,3};
    int* a[] = {a1, a2, a3, a4};
    int** p1 = a;
    int p2 = 4;
    int* p3 = (int*)malloc(sizeof(int) * p2);
    for (int i = 0; i < p2; i++) {
        p3[i] = i + 1;
    }

    // 测试并打印相关信息
    printf("Case for 120 : \n  triangle = ");
    PrintNumsOfNums(p1, p2, p3);
    int result = MinimumTotal(p1, p2, p3);
    printf("\n  result = %d.\n", result);

    // 释放分配的内存
    free(p3);
    p3 = NULL;

    return;
}

int main()
{
    Test1823();
    Test46();
    Test120();

    getchar();
    return 0;
}

