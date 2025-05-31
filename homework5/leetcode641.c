#include <stdlib.h>

#include "leetcode641.h"

/*
函数名：MyCircularDequeCreate
功能：创建一个循环双端队列
参数：
    k: 队列的容量
返回值：
    返回一个指向MyCircularDeque结构体的指针，如果创建失败则返回NULL
*/
MyCircularDeque *MyCircularDequeCreate(int k) {
    MyCircularDeque *obj = malloc(sizeof(MyCircularDeque));
    if (NULL == obj) {
        return NULL;
    }
    obj->capacity = k;
    obj->size = 0;
    obj->head = malloc(sizeof(Node));
    if (NULL == obj->head) {
        free(obj);
        return NULL;
    }
    obj->tail = NULL;
    obj->head->pre = NULL;
    obj->head->next = obj->tail;
    return obj;
}

/*
函数名：MyCircularDequeInsertFront
功能：在循环双端队列的头部插入一个元素
参数：
    obj: 循环双端队列的指针
    value: 要插入的值
返回值：
    如果插入成功返回true，否则返回false
*/
bool MyCircularDequeInsertFront(MyCircularDeque *obj, int value) {
    if (obj->size >= obj->capacity) { // 容量已满，添加失败
        return false;
    }
    // 容量未满，正常添加
    Node *node = malloc(sizeof(Node));
    if (NULL == node) {
        return false;
    }
    node->val = value;
    node->next = obj->head->next;
    node->pre = obj->head;
    obj->head->next = node;
    if (NULL == obj->tail) { // 如果添加之前列表为空，需要额外设置tail = node
        obj->tail = node;
    } else { // 如果添加之前列表非空，需要设置node->next->pre=node
        node->next->pre = node;
    }
    obj->size++;
    return true;
}

/*
函数名：MyCircularDequeInsertLast
功能：在循环双端队列的尾部插入一个元素
参数：
    obj: 循环双端队列的指针
    value: 要插入的值
返回值：
    如果插入成功返回true，否则返回false
*/
bool MyCircularDequeInsertLast(MyCircularDeque *obj, int value) {
    if (obj->size >= obj->capacity) { // 容量已满，添加失败
        return false;
    }
    // 容量未满，正常添加
    Node *node = malloc(sizeof(Node));
    if (NULL == node) {
        return false;
    }
    node->val = value;
    node->next = NULL;
    if (NULL == obj->tail) { // 如果当前队列为空
        node->pre = obj->head;
        obj->head->next = node;
    } else { // 当前队列非空
        node->pre = obj->tail;
        obj->tail->next = node;
    }
    obj->tail = node;
    obj->size++;
    return true;
}

/*
函数名：MyCircularDequeDeleteFront
功能：删除循环双端队列的头部元素
参数：
    obj: 循环双端队列的指针 
返回值：
    如果删除成功返回true，否则返回false
*/
bool MyCircularDequeDeleteFront(MyCircularDeque *obj) {
    if (NULL == obj->tail) { // 队列为空，删除失败
        return false;
    }
    // 队列不为空，正常删除
    Node *temp = obj->head->next;
    obj->head->next = temp->next;
    if (1 == obj->size) { // 删完之后队列为空
        obj->tail = NULL;
    } else {
        temp->next->pre = obj->head;
    }
    free(temp);
    obj->size--;
    return true;
}

/*
函数名：MyCircularDequeDeleteLast
功能：删除循环双端队列的尾部元素
参数：
    obj: 循环双端队列的指针
返回值：
    如果删除成功返回true，否则返回false
*/
bool MyCircularDequeDeleteLast(MyCircularDeque *obj) {
    if (NULL == obj->tail) { // 队列为空，删除失败
        return false;
    }
    // 队列非空，正常删除
    Node *temp = obj->tail;
    temp->pre->next = NULL;
    if (1 == obj->size) { // 删完之后队列为空
        obj->tail = NULL;
    } else {
        obj->tail = temp->pre;
    }
    free(temp);
    obj->size--;
    return true;
}

/*
函数名：MyCircularDequeGetFront
功能：获取循环双端队列的头部元素
参数：
    obj: 循环双端队列的指针
返回值：
    如果队列不为空，返回头部元素的值；如果队列为空，返回-1
*/
int MyCircularDequeGetFront(MyCircularDeque *obj) {
    if (NULL == obj->tail) { // 队列为空，返回-1
        return -1;
    }
    // 队列不为空，返回头元素
    return obj->head->next->val;
}

/*
函数名：MyCircularDequeGetRear
功能：获取循环双端队列的尾部元素
参数：
    obj: 循环双端队列的指针
返回值：
    如果队列不为空，返回尾部元素的值；如果队列为空，返回-1
*/
int MyCircularDequeGetRear(MyCircularDeque *obj) {
    if (NULL == obj->tail) { // 队列为空，返回-1
        return -1;
    }
    // 队列不为空，返回尾元素
    return obj->tail->val;
}

/*
函数名：MyCircularDequeIsEmpty
功能：检查循环双端队列是否为空
参数：
    obj: 循环双端队列的指针
返回值：
    如果队列为空，返回true；否则返回false
*/
bool MyCircularDequeIsEmpty(MyCircularDeque *obj) {
    if (NULL == obj->tail) { // 队列为空，返回true
        return true;
    }
    // 队列不为空，返回false
    return false;
}

/*
函数名：MyCircularDequeIsFull
功能：检查循环双端队列是否已满
参数：
    obj: 循环双端队列的指针
返回值：
    如果队列已满，返回true；否则返回false
*/
bool MyCircularDequeIsFull(MyCircularDeque *obj) {
    if (obj->size >= obj->capacity) { // 队列已满，返回true
        return true;
    }
    // 队列未满，返回false
    return false;
}

/*
函数名：MyCircularDequeFree
功能：释放循环双端队列的内存
参数：
    obj: 循环双端队列的指针
*/
void MyCircularDequeFree(MyCircularDeque *obj) {
    while (NULL != obj->head) {
        Node *node = obj->head;
        obj->head = obj->head->next;
        free(node);
    }
    free(obj);
}
