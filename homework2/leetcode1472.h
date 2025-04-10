#ifndef __LEETCODE1472_H__
#define __LEETCODE1472_H__

#include <stdio.h>

typedef struct BrowserHistory{
    char *url; // 当前网址
    struct BrowserHistory *nextPage; // 下一个页面
    struct BrowserHistory *lastPage; // 上一个页面
} BrowserHistory;

BrowserHistory* BrowserHistoryCreate(char *homepage);
void BrowserHistoryVisit(BrowserHistory *obj, char *url);
void OneStepBack(BrowserHistory *obj);
char* BrowserHistoryBack(BrowserHistory *obj, int steps);
void OneStepForward(BrowserHistory *obj);
char* BrowserHistoryForward(BrowserHistory *obj, int steps);
void BrowserHistoryFree(BrowserHistory* obj);

#endif // __LEETCODE1472_H__