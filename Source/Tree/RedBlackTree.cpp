#include "RedBlackTree.h"

void RedBlackTree::inorderTreeWalk(RBTNode* x)
{
    if (x != this->nil) {
        inorderTreeWalk(x->left);
        printf("Key:%d Color:%d P:%d L:%d R:%d\n", x->key, x->color, x->p->key, x->left->key, x->right->key);  // 对每个结点都遍历了一次这个操作
        inorderTreeWalk(x->right);
    }
}

RBTNode * RedBlackTree::treeMinimum(RBTNode * x)
{
    // para x: 开始查找最小值的根结点
    // return: 找到最小值的结点
    // O(h) 时间，根到底的 simple path
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

RBTNode * RedBlackTree::treeMaximum(RBTNode * x)
{
    // 与最小值对称
    // O(h) 时间
    while (x->right != nil) {
        x = x->right;
    }
    return x;
}

RBTNode * RedBlackTree::treeSuccessor(RBTNode * x)
{
    // para x: 需要寻找后继的 node
    // return: x 的后继，如不存在则 nil
    // 由于二叉搜索树的性质，实际上并不需要比较各个 key 值即可完成本操作
    // 时间 O(h), 每次迭代向上回溯一层，最多迭代 h 层

    if (x->right != nil) {  // 如果 x 有右子结点
                            // x 的右子树中的所有结点都比 x 大，且
                            // (1)若 x 是 x.p 的左子结点，则 x < x.p，但所有 x 右子树中的所有结点都比 x.p 小，因为其存在于 x.p 的左子树中
                            // (2)若 x 是 x.p 的右子结点，则 x > x.p，x 的后继只能在 x 自己的右子结点中存在 (麻烦但易正)
        return treeMinimum(x->right);  // 直接返回 x 右子树中最小元素的即可
    }
    RBTNode* y = x->p;  // 否则回溯到 x 的父结点 y
    while (y != nil && x == y->right) {
        // 只要没回溯到x为根结点，且 x 作为 y 的右结点，即 x > y
        x = y;
        y = y->p; // 这两行表示继续向上回溯
    }
    return y; // 回溯的终止为：
              // (1) x 到了根结点，y 到了nil，则原本是min，无后继； 
              // (2) x 是其父结点的左结点，即第一次 x < y，返回 y
}

RBTNode * RedBlackTree::treePredecessor(RBTNode * x)
{
    if (x->left != nil) {
        return treeMaximum(x->left);
    }
    RBTNode* y = x->p;
    while (y != nil && x == y->left) {
        x = y;
        y = y->p;
    }
    return y;
}
