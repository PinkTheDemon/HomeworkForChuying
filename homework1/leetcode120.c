#include "leetcode120.h"

/*
函数名：MinimumTotal
功能：  计算三角形的最小路径和
入参：  triangle: 三角形整型数组的每一行
        triangleSize: 三角形的行数
        triangleColSize: 各行的元素个数
返回值：从顶到底的最小路径和
*/
int MinimumTotal(int **triangle, int triangleSize, int *triangleColSize)
{
    // 计算到该位置的最小路径
    for (int i = 1; i < triangleSize; i++) {
        triangle[i][0] += triangle[i - 1][0];
        for (int j = 1; j < i; j++) {
            triangle[i][j] += (triangle[i - 1][j - 1] < triangle[i - 1][j])? triangle[i - 1][j - 1] : triangle[i - 1][j];
        }
        triangle[i][i] += triangle[i-1][i-1];
    }
    // 查找最后一行的路径的最小值
    int minSum = triangle[triangleSize - 1][0];
    for (int i = 1; i < triangleSize; i++) {
        if (triangle[triangleSize - 1][i] < minSum) {
            minSum = triangle[triangleSize - 1][i];
        }
    }

    return minSum;
}