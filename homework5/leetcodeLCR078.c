#include <stdlib.h>
#include <stdbool.h>

#include "leetcodeLCR078.h"

/*
结构体名：PriorityQueue
功能：实现一个优先队列，用于合并K个有序链表
元素：
    data: 存储链表节点的数组
    size: 当前队列中的元素数量
    capacity: 队列的最大容量
*/
typedef struct PriorityQueue {
    ListNode **data;
    int size;
    int capacity;
} PriorityQueue;

/*
函数名：CreateQueue
功能：创建一个优先队列
参数：
    capacity: 队列的最大容量
返回值：
    返回一个指向新创建的优先队列的指针
*/
PriorityQueue *CreateQueue(int capacity)
{
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    if (NULL == pq) {
        return NULL;
    }
    pq->data = malloc(capacity * sizeof(ListNode*));
    if (NULL == pq->data) {
        free(pq);
        return NULL;
    }
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

/*
函数名：Swap
功能：交换两个链表节点的指针
参数：
    a: 指向第一个链表节点指针的指针
    b: 指向第二个链表节点指针的指针
*/
void Swap(ListNode **a, ListNode **b)
{
    ListNode *temp = *a;
    *a = *b;
    *b = temp;
    return;
}

/*
函数名：HeapifyUp
功能：将新插入的节点上浮到正确的位置
参数：
    pq: 指向优先队列的指针
    index: 新插入节点的索引
*/
void HeapifyUp(PriorityQueue *pq, int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->data[index]->val < pq->data[parent]->val) {
            Swap(&pq->data[index], &pq->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
    return;
}

/*
函数名：HeapifyDown
功能：将根节点下沉到正确的位置
参数：
    pq: 指向优先队列的指针
    index: 根节点的索引
*/
void HeapifyDown(PriorityQueue *pq, int index)
{
    int left, right, smallest;
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < pq->size && pq->data[left]->val < pq->data[smallest]->val)
            smallest = left;
        if (right < pq->size && pq->data[right]->val < pq->data[smallest]->val)
            smallest = right;

        if (smallest != index) {
            Swap(&pq->data[index], &pq->data[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
    return;
}

/*
函数名：Push
功能：将一个链表节点插入到优先队列中
参数：
    pq: 指向优先队列的指针
    node: 要插入的链表节点
*/
void Push(PriorityQueue *pq, ListNode *node)
{
    if (pq->size < pq->capacity) {
        pq->data[pq->size++] = node;
        HeapifyUp(pq, pq->size - 1);
    }
}

/*
函数名：Pop
功能：从优先队列中弹出最小的链表节点
参数：
    pq: 指向优先队列的指针
返回值：
    返回指向被弹出节点的指针，如果队列为空则返回NULL
*/
ListNode *Pop(PriorityQueue *pq)
{
    if (pq->size == 0) {
        return NULL;
    }
    ListNode *minNode = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    HeapifyDown(pq, 0);
    return minNode;
}

/*
函数名：IsEmpty
功能：检查优先队列是否为空
参数：
    pq: 指向优先队列的指针
返回值：
    如果队列为空，返回true；否则返回false
*/
bool IsEmpty(PriorityQueue *pq)
{
    return pq->size == 0;
}

/*
函数名：MergeKLists
功能：合并K个有序链表
参数：
    lists: 指向链表数组的指针
    listsSize: 链表数组的大小
返回值：
    返回合并后的有序链表的头指针
*/
ListNode *MergeKLists(ListNode **lists, int listsSize)
{
    // 创建一个优先队列
    PriorityQueue *pq = CreateQueue(listsSize);
    // 将所有链表的非空头节点插入到优先队列中
    for (int i = 0; i < listsSize; i++) {
        if (lists[i] != NULL) {
            Push(pq, lists[i]);
        }
    }
    // 创建一个虚拟头节点
    ListNode dummy;
    ListNode *tail = &dummy;
    dummy.next = NULL;
    // 从优先队列中弹出最小的节点，并将其添加到结果链表中
    while (!IsEmpty(pq)) {
        ListNode *minNode = Pop(pq);
        tail->next = minNode;
        tail = tail->next;
        if (minNode->next != NULL) {
            Push(pq, minNode->next);
        }
    }
    // 释放优先队列的内存
    free(pq->data);
    free(pq);
    // 返回合并后的链表的头节点
    return dummy.next;
}