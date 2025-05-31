#include "leetcode958.h"

/*
函数名：IsCompleteTree
功能：判断二叉树是否为完全二叉树。
参数：
    root: 二叉树的根节点
返回值：
    如果是完全二叉树，返回true；否则返回false。
*/
bool IsCompleteTree(TreeNode *root) {
    TreeNode *queue[200]; // 最大节点数为100，加上最多50个叶子结点的左右NULL，200个空间可以保证不超范围
    int front = 0, rear = 0;
    queue[rear++] = root;
    bool foundNull = false;
    
    while (front < rear) {
        struct TreeNode* node = queue[front++];
        if (node == NULL) {
            foundNull = true;
        } else {
            if (foundNull) { // 在遇到空之后不能再遇到非空
                return false;
            }
            queue[rear++] = node->left;
            queue[rear++] = node->right;
        }
    }
    return true;
}