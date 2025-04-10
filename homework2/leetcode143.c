#include "leetcode143.h"

/*
函数名：ReorderList
功能：  重排链表
输入：  head: 链表头结点指针
输出：  无，直接在原链表上进行重排
*/
void ReorderList(struct ListNode *head)
{
    int numNodes = 0; // 存储链表节点数量
    ListNode *now = head;
    while (now != NULL) {
        now = now->next;
        numNodes++;
    }
    // 简单情况处理：当节点数量小于2时，均可不做改动直接返回
    if (numNodes <= 2) {
        return;
    }
    // 其他情况处理
    ListNode **listNodes = malloc(sizeof(ListNode*) * numNodes);
    if (listNodes == NULL) {
        printf("malloc failed!");
        return;
    }
    now = head;
    for (int i = 0; i < numNodes; i++) { // 将各个结点依次存入数组
        listNodes[i] = now;
        now = now->next;
    }
    bool isLeft = false; // 用于记录是否从左边取结点
    int left = 1;
    int right = numNodes - 1;
    now = head;
    while (left <= right) { // 按要求重排
        if (isLeft) {
            now->next = listNodes[left];
            left++;
        } else {
            now->next = listNodes[right];
            right--;
        }
        now = now->next;
        isLeft = !isLeft;
    }
    now->next = NULL;

    return;
}