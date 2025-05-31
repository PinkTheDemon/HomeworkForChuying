#ifndef __LEETCODELCR078_H__
#define __LEETCODELCR078_H__

/*
结构体名：ListNode
功能：定义链表节点结构体
元素：
    val: 节点的值
    *next: 指向下一个节点的指针
*/
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

ListNode* MergeKLists(ListNode** lists, int listsSize);

#endif // __LEETCODELCR078_H__