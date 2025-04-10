#include "leetcode1823.h"

/*
函数名：FindNextAviLoc
功能：  从当前位置出发，返回走过指定数量的可行位置后的位置
入参：  circle——记录位置可行性的数组
        circleSize——数组大小
        nowLoc——当前位置
        incLoc——位置增量
返回值：走过指定数量后的位置
*/
int FindNextAviLoc(bool *circle, int circleSize, int nowLoc, int incLoc)
{
    // 入参检查
    if (nowLoc < 0 || nowLoc >= circleSize) {
        printf("illegal parameter(nowLoc)!");
    }
    if (incLoc <= 0) {
        printf("illegal parameter(incLoc)!");
    }
    // 函数主体
    int num = 0; // 用于记录走过的可行位置的数量
    int loc = nowLoc; // 为避免修改入参值
    while (num < incLoc) {
        loc++;
        if (loc >= circleSize) {
            loc %= circleSize;
        }
        // 如果当前位置已经出局，则继续向后查找
        if (circle[loc]) {
            num++;
        }
    }

    return loc;
}

/*
函数名：FindTheWinner
功能：  找出游戏的胜利者
入参：  n: 游戏人数
        k: 整数，1 <= k <= n
返回值：游戏胜利者对应的编号
*/
int FindTheWinner(int n, int k)
{
    // 特殊情况处理：如果n为1，那么将不淘汰人，所以直接返回1
    if (n == 1) {
        return 1;
    }
    // 定义circle用于记录对应位置是否还在游戏中
    bool *circle = malloc(sizeof(bool) * n);
    if (circle == NULL) { // 检查内存是否分配成功
        printf("malloc failed!");
    }
    // 初始化circle
    for (int i = 0; i < n; i ++) {
        circle[i] = true;
    }
    // 第一个出局的是数字k，对应序号为k-1，可以直接踢掉，并记录当前位置为k-1
    int outLoc = k-1;
    circle[outLoc] = false;
    // 游戏循环
    for (int i = 1; i < (n - 1); i++) { // 共淘汰n-1人即可，第一个已经出局所以从i=1开始
        // 计算下一个出局的位置距离当前位置的增量，不能是0，因为当前的位置已经出局
        int incLoc = k % (n - i);
        if (incLoc == 0) {
            incLoc = n - i;
        }
        // 找淘汰位置
        outLoc = FindNextAviLoc(circle, n, outLoc, incLoc);
        // 记录淘汰位置
        circle[outLoc] = false;
    }
    // 查找获胜位置
    int winLoc = 0;
    for (int i = 0; i < n; i++) {
        if (circle[i]) {
            winLoc = i + 1;
            break;
        }
    }
    // 释放内存
    free(circle);

    return winLoc;
}