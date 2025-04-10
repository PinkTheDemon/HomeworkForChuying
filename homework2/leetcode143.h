#ifndef __LEETCODE143_H__
#define __LEETCODE143_H__

#include <stdbool.h>
#include <stdio.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

void ReorderList(struct ListNode *head);

#endif // __LEETCODE143_H__