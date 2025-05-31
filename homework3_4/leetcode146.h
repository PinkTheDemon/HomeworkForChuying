#ifndef __LEETCODE146_H__
#define __LEETCODE146_H__

typedef struct Node{
    int key;
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct LRUCache{
    int capacity;
    int size;
    Node *head;
    Node *tail;
    Node **hashmap;
} LRUCache;

LRUCache *lRUCacheCreate(int capacity);
int lRUCacheGet(LRUCache *obj, int key);
void lRUCachePut(LRUCache *obj, int key, int value);
void lRUCacheFree(LRUCache *obj);

#endif // __LEETCODE146_H__