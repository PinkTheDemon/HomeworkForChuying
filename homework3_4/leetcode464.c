#include <stdlib.h>
#include "uthash.h"

#include "leetcode464.h"

/*
结构体名：HashItem
功能：用于存储哈希表中的键值对。
元素：
    key：整数键，用于标识状态
    val：布尔值，表示当前状态是否可以获胜
    hh：用于哈希表的句柄，包含哈希表相关信息
*/
typedef struct HashItem{
    int key;
    bool val;
    UT_hash_handle hh;
} HashItem;

/*
函数名：Dfs
功能：深度优先搜索，用于判断当前状态是否可以获胜
参数：
    maxChoosableInteger：最大可选择的整数
    usedNumbers：已使用的数字的位掩码
    desiredTotal：目标总和
    currentTotal：当前总和
    memo：哈希表，用于存储已计算的状态
返回值：
    如果当前状态可以获胜，返回true；否则返回false
*/
bool Dfs(int maxChoosableInteger, int usedNumbers, int desiredTotal, int currentTotal, HashItem **memo)
{
    HashItem *pEntry = NULL;
    // 检查当前状态是否已经计算过
    HASH_FIND_INT(*memo, &usedNumbers, pEntry);
    // 如果没有缓存，则进行递归计算
    if (NULL == pEntry) {
        bool res = false;
        // 遍历所有可选的数字
        for (int i = 0; i < maxChoosableInteger; i++) {
            // 如果数字i未被使用
            if (((usedNumbers >> i) & 1) == 0) {
                // 如果当前总和加上数字i+1已经达到或超过目标总和，则可以获胜
                if (i + 1 + currentTotal >= desiredTotal) {
                    res = true;
                    break;
                }
                // 否则递归判断对手是否会输
                if (!Dfs(maxChoosableInteger, usedNumbers | (1 << i), desiredTotal, currentTotal + i + 1, memo)) {
                    res = true;
                    break;
                }
            }
        }
        // 缓存当前状态的结果
        pEntry = malloc(sizeof(HashItem));
        if (NULL == pEntry) { // 内存分配失败
            return false;
        }
        pEntry->key = usedNumbers;
        pEntry->val = res;
        HASH_ADD_INT(*memo, key, pEntry);
    }
    // 返回当前状态的结果（是否能赢）
    return pEntry->val;
}

/*
函数名：CanIWin
功能：判断是否可以获胜
参数：
    maxChoosableInteger：最大可选择的整数
    desiredTotal：目标总和
返回值：
    如果先手一定能获胜，返回true；否则返回false
*/
bool CanIWin(int maxChoosableInteger, int desiredTotal)
{
    HashItem *memo = NULL;
    if ((1 + maxChoosableInteger) * (maxChoosableInteger) / 2 < desiredTotal) {
        return false;
    }
    return Dfs(maxChoosableInteger, 0, desiredTotal, 0, &memo);
}