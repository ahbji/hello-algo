/**
 * File: binary_tree_dfs.c
 * Created Time: 2023-01-11
 * Author: Reanon (793584285@qq.com)
 * Update by: AndreaJi (andrea.hb.ji@outlook.com)
 */

#include "../include/include.h"

static int *pre_order_internel(TreeNode *root, int *size, int *arr)
{
    /* 辅助数组，用于存储遍历序列 */
    if (arr == NULL)
        arr = (int *)malloc(sizeof(int) * MAX_NODE_SIZE);
    if (root == NULL)
        return arr;
    // 访问优先级：根节点 -> 左子树 -> 右子树
    arr[(*size)++] = root->val;
    pre_order_internel(root->left, size, arr);
    pre_order_internel(root->right, size, arr);
    return arr;
}

/* 前序遍历 */
int *preOrder(TreeNode *root, int *size)
{
    return pre_order_internel(root, size, NULL);
}

static int *in_order_internel(TreeNode *root, int *size, int *arr)
{
    /* 辅助数组，用于存储遍历序列 */
    if (arr == NULL)
        arr = (int *)malloc(sizeof(int) * MAX_NODE_SIZE);
    if (root == NULL)
        return arr;
    // 访问优先级：左子树 -> 根节点 -> 右子树
    in_order_internel(root->left, size, arr);
    arr[(*size)++] = root->val;
    in_order_internel(root->right, size, arr);
    return arr;
}

/* 中序遍历 */
int *inOrder(TreeNode *root, int *size)
{
    return in_order_internel(root, size, NULL);
}

static int *post_order_internel(TreeNode *root, int *size, int *arr)
{
    /* 辅助数组，用于存储遍历序列 */
    if (arr == NULL)
        arr = (int *)malloc(sizeof(int) * MAX_NODE_SIZE);
    if (root == NULL)
        return arr;
    // 访问优先级：左子树 -> 右子树 -> 根节点
    post_order_internel(root->left, size, arr);
    post_order_internel(root->right, size, arr);
    arr[(*size)++] = root->val;
    return arr;
}

/* 后序遍历 */
int *postOrder(TreeNode *root, int *size)
{
    return post_order_internel(root, size, NULL);
}

/* Driver Code */
int main()
{
    /* 初始化二叉树 */
    // 这里借助了一个从数组直接生成二叉树的函数
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(nums) / sizeof(int);
    TreeNode *root = arrToTree(nums, size);
    printf("初始化二叉树\n");
    printTree(root);

    int *arr;
    /* 前序遍历 */
    size = 0;
    arr = preOrder(root, &size);
    printf("前序遍历的节点打印序列 = ");
    printArray(arr, size);
    free(arr);

    /* 中序遍历 */
    size = 0;
    arr = inOrder(root, &size);
    printf("中序遍历的节点打印序列 = ");
    printArray(arr, size);
    free(arr);

    /* 后序遍历 */
    size = 0;
    arr = postOrder(root, &size);
    printf("后序遍历的节点打印序列 = ");
    printArray(arr, size);
    free(arr);

    return 0;
}
