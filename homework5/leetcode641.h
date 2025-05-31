#ifndef __LEETCODE641_H__
#define __LEETCODE641_H__

#include <stdbool.h>

/*
结构体名：Node
功能：循环双端队列的节点
元素：
    pre: 前驱节点
    next: 后继节点
    val: 节点值
*/
typedef struct Node {
    struct Node *pre;
    struct Node *next;
    int val;
} Node;

/*
结构体名：MyCircularDeque
功能：创建一个循环双端队列
元素：
    capacity: 容量
    size: 当前元素个数
    head: 虚拟头结点
    tail: 尾结点
*/
typedef struct MyCircularDeque {
    int capacity;
    int size;
    Node *head;
    Node *tail;
} MyCircularDeque;


MyCircularDeque *MyCircularDequeCreate(int k);
bool MyCircularDequeInsertFront(MyCircularDeque *obj, int value);
bool MyCircularDequeInsertLast(MyCircularDeque *obj, int value);
bool MyCircularDequeDeleteFront(MyCircularDeque *obj);
bool MyCircularDequeDeleteLast(MyCircularDeque *obj);
int MyCircularDequeGetFront(MyCircularDeque *obj);
int MyCircularDequeGetRear(MyCircularDeque *obj);
bool MyCircularDequeIsEmpty(MyCircularDeque *obj);
bool MyCircularDequeIsFull(MyCircularDeque *obj);
void MyCircularDequeFree(MyCircularDeque *obj);

#endif // __LEETCODE641_H__