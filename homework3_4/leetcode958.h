#ifndef __LEETCODE958_H__
#define __LEETCODE958_H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

bool IsCompleteTree(TreeNode *root);

#endif // __LEETCODE958_H__