#include "leetcode1472.h"

/*
函数名：BrowserHistoryCreate
功能：  创建网页类
输入：  homepage: 首页网址
输出：  obj: 指向创建的网页类的指针
*/
BrowserHistory* BrowserHistoryCreate(char *homepage)
{
    BrowserHistory *obj = malloc(sizeof(BrowserHistory));
    obj->url = homepage;
    obj->nextPage = NULL;
    obj->lastPage = NULL;

    return obj;
}

/*
函数名：BrowserHistoryVisit
功能：  访问新网页
输入：  obj: 指向当前网页的指针
        url: 新网页网址
输出：  无
*/
void BrowserHistoryVisit(BrowserHistory *obj, char *url)
{
    // 后向free
    while (obj->nextPage != NULL) {
        BrowserHistory *tmp = obj->nextPage;
        obj->nextPage = obj->nextPage->nextPage;
        free(tmp->url);
        free(tmp);
    }
    // 创建一个新的网页类，并将其链接到当前网页的上一个网页
    BrowserHistory *last = BrowserHistoryCreate(obj->url);
    last->lastPage = obj->lastPage;
    last->nextPage = obj;
    obj->lastPage = last;
    obj->url = url;

    return;
}

/*
函数名：OneStepBack
功能：  网页后退一次
输入：  obj: 指向当前网页的指针
输出：  无
备注：  1.无输出，执行完后，obj变为指向上一个网页的指针
        2.该函数不检查上一个页面是否为空，在调用前请自行检查
*/
void OneStepBack(BrowserHistory *obj)
{
    // 临时保存上一个页面及其网址
    BrowserHistory *tmp = obj->lastPage;
    char *tmpUrl = obj->lastPage->url;
    // 修改当前页面和上一个页面的前后页面指针
    obj->lastPage = obj->lastPage->lastPage;
    tmp->nextPage = obj->nextPage;
    obj->nextPage = tmp;
    tmp->lastPage = obj;
    // 修改当前当前页面的网址
    tmp->url = obj->url;
    obj->url = tmpUrl;

    return;
}

/*
函数名：BrowserHistoryBack
功能：  网页后退指定步数
输入：  obj: 指向当前网页的指针
        steps: 后退步数
输出：  后退之后所在网页的网址
*/
char* BrowserHistoryBack(BrowserHistory *obj, int steps)
{
    for (int i = 0; i < steps; i++) {
        if (obj->lastPage != NULL) {
            OneStepBack(obj);
        } else {
            break;
        }
    }

    return obj->url;
}

/*
函数名：OneStepForward
功能：  网页前进一次
输入：  obj: 指向当前网页的指针
输出：  无
备注：  1.无输出，执行完后，obj变为指向下一个网页的指针
        2.该函数不检查下一个页面是否为空，在调用前请自行检查
*/
void OneStepForward(BrowserHistory *obj)
{
    // 临时保存下一个页面及其网址
    BrowserHistory *tmp = obj->nextPage;
    char *tmpUrl = obj->nextPage->url;
    // 修改当前页面和下一个页面的前后页面指针
    obj->nextPage = obj->nextPage->nextPage;
    tmp->lastPage = obj->lastPage;
    obj->lastPage = tmp;
    tmp->nextPage = obj;
    // 修改当前页面的网址
    tmp->url = obj->url;
    obj->url = tmpUrl;

    return;
}

/*
函数名：BrowserHistoryForward
功能：  网页前进指定步数
输入：  obj: 指向当前网页的指针
        steps: 前进步数
输出：  前进之后所在网页的网址
*/
char* BrowserHistoryForward(BrowserHistory *obj, int steps)
{
    for (int i = 0; i < steps; i++) {
        if (obj->nextPage != NULL) {
            OneStepForward(obj);
        } else {
            break;
        }
    }

    return obj->url;
}

/*
函数名：BrowserHistoryFree
功能：  释放网页类
输入：  obj: 指向当前网页的指针
输出：  无
*/
void BrowserHistoryFree(BrowserHistory *obj)
{
    // 前向free
    while (obj->lastPage != NULL) {
        BrowserHistory *tmp = obj->lastPage;
        obj->lastPage = obj->lastPage->lastPage;
        free(tmp->url);
        free(tmp);
    }
    // 后向free
    while (obj->nextPage != NULL) {
        BrowserHistory *tmp = obj->nextPage;
        obj->nextPage = obj->nextPage->nextPage;
        free(tmp->url);
        free(tmp);
    }
    // 自身free
    free(obj->url);
    free(obj);

    return;
}