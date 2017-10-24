#include "RedBlackTree.h"

void RedBlackTree::inorderTreeWalk(RBTNode* x)
{
    if (x != this->nil) {
        inorderTreeWalk(x->left);
        printf("Key:%d Color:%d P:%d L:%d R:%d\n", x->key, x->color, x->p->key, x->left->key, x->right->key);  // 对每个结点都遍历了一次这个操作
        inorderTreeWalk(x->right);
    }
}
