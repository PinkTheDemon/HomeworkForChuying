#include <stdlib.h>

#include "leetcode146.h"

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *cache = malloc(sizeof(LRUCache));
    if (NULL == cache) {
        return NULL;
    }
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->hashmap = malloc(sizeof(Node *) * capacity);
    if (NULL == cache->hashmap) {
        free(cache);
        return NULL;
    }
    for (int i = 0; i < capacity; i++) {
        cache->hashmap[i] = NULL;
    }
    return cache;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    int index = key % obj->capacity;
    Node *node = obj->hashmap[index];
    if (node == NULL) {
        return -1;
    }
    lRUCacheMoveToHead(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    int index = key % obj->capacity;
    Node *node = obj->hashmap[index];
    if (node != NULL) {
        node->value = value;
        lRUCacheMoveToHead(obj, node);
        return;
    }
    if (obj->size == obj->capacity) {
        Node *tail = obj->tail;
        obj->hashmap[tail->key % obj->capacity] = NULL;
        if (tail->prev != NULL) {
            tail->prev->next = NULL;
        }
        free(tail);
        obj->size--;
    }
    node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    obj->hashmap[index] = node;
    lRUCacheAddToHead(obj, node);
    obj->size++;
}

void lRUCacheFree(LRUCache *obj)
{
    Node *current = obj->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(obj->hashmap);
    free(obj);
}