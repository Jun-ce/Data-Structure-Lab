// DataStructureLab.cpp: 定义控制台应用程序的入口点。
//

#include "DataStructureLab.h"
#include <random>

using namespace std;

int main()
{
    /*
    printf("Starting Binary Search Tree Test:\n");
    BinarySearchTree bst;
    BSTNode bstr;
    bstr.key = 0x7fff/2;
    bst.root = &bstr;
    for (int i = 0; i < 20; i++) {
        BSTNode* n = new BSTNode;
        n->key = (int)rand();
        bst.treeInsert(bst, n);
    }
    bst.inorderTreeWalk(bst.root);
    */
    printf("\nStarting Red-Black Tree Test:\n");
    RBTNode* rbtr = new RBTNode;
    rbtr->key = 0;
    RedBlackTree rbt(rbtr);
    srand(31);
    for (int i = 0; i < 200; i++) {
        RBTNode* n = new RBTNode;
        RBTNode* oldn = n;
        n->key = (int)rand();
        rbt.RBInsert(rbt, n);
        //printf("Key:%d Color:%d P:%d inserted.\n", oldn->key, oldn->color, oldn->p->key);  // 对每个结点都遍历了一次这个操作
    }
    rbt.inorderTreeWalk(rbt.root);
}

