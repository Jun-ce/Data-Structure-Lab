#pragma once
#include <string>

using namespace std;

struct BSTNode  //二叉搜索树的每一个结点,其包含以下信息
{

    int key;  // 结点的关键字
    string satelliteData;  // 结点的卫星数据

    BSTNode* left = nullptr;  // 结点的左子结点
    BSTNode* right = nullptr;  // 结点的右子结点
    BSTNode* p = nullptr;  // 结点的父结点
}; 

BSTNode* nil = nullptr;  // 结点不存在子结点或者父结点时指向 nil

class BinarySearchTree {  // 二叉搜索树
public:
    // BST的定义
    // 二叉搜索树中的每个node其key值满足二叉搜索树的性质：
    // 对任意 BSTNode x 的左子树中的 BSTNode y，有y.key <= x.key
    // 右子树的 BSTNode z, 有 x.key <= z.key


    // BST的参数
    BSTNode* root = nil;     // 一颗二叉搜索树的根是其唯一参数

    
    // BST的性质：
    int n;  // 总结点数
    int h;  // 高


    // 1. 中序遍历
    static void inorderTreeWalk(BSTNode* x)  {
        // para x: 输入T.root
        // return: void
        // 会从最左开始打印出本树所有key值，但是是从根开始的便利
        // O(n) 时间，对每个结点都遍历了一次访问
        if (x != nil) {
            inorderTreeWalk(x->left);
            printf("%d ", x->key);  // 对每个结点都遍历了一次这个操作
            inorderTreeWalk(x->right);
        }
    }

    // 2.查找
    
    //(递归遍历式查找)
    static BSTNode* treeSearch(BSTNode* x, int k) {
        // para x: 开始查找的根结点
        // para k: 查找的关键字值
        // return: 找到key为k的结点，若无匹配项则返回 nil
        // O(h) 时间，每次递归一定会进入下一层，最终形成一条从根到底的simple path，到最底层必定return
        if (x == nil || k == x->key) {
            return x;
        }
        if (k < x->key) {
            return treeSearch(x->left, k);
        }
        else {
            return treeSearch(x->right, k);
        }
    }

    //(迭代遍历式查找)
    static BSTNode* iterativeTreeSearch(BSTNode* x, int k) {
        // para x: 开始查找的根结点
        // para k: 查找的关键字值
        // return: 找到key为k的结点，若无匹配项则返回 nil
        // O(h) 时间，每次迭代一定会进入下一层，到最底层必定return
        while (x != nil && k != x->key) {
            if (k < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        return x;
    }

    // 3.最小值和最大值

    // (最小值)
    static BSTNode* treeMinimum(BSTNode* x) {
        // para x: 开始查找最小值的根结点
        // return: 找到最小值的结点
        // O(h) 时间，根到底的 simple path
        while (x->left != nil) {
            x = x->left;
        }
        return x;
    }

    // (最大值)
    static BSTNode* treeMaximum(BSTNode* x) {
        // 与最小值对称
        // O(h) 时间
        while (x->right != nil) {
            x = x->right;
        }
        return x;
    }

    // 4. 后继和前驱

    // (后继)
    static BSTNode* treeSuccessor(BSTNode* x) {
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
        BSTNode* y = x->p;  // 否则回溯到 x 的父结点 y
        while (y != nil && x == y->right) {  
            // 只要没回溯到x为根结点，且 x 作为 y 的右结点，即 x > y
            x = y;
            y = y->p; // 这两行表示继续向上回溯
        }
        return y; // 回溯的终止为：
                  // (1) x 到了根结点，y 到了nil，则原本是min，无后继； 
                  // (2) x 是其父结点的左结点，即第一次 x < y，返回 y
    }


    // (前驱)
    static BSTNode* treePredecessor(BSTNode* x) {
        // para x: 需要寻找前驱的 node
        // return: x 的前驱，如不存在则 nil
        // 由于二叉搜索树的性质，实际上并不需要比较各个 key 值即可完成本操作
        // 与后继对称

        if (x->left != nil) {
            return treeMaximum(x->left);
        }
        BSTNode* y = x->p;
        while (y != nil && x == y->left) {
            x = y;
            y = y->p;
        }
        return y;
    }


    // 5.插入
    static void treeInsert(BinarySearchTree T, BSTNode* z) {
    // para T: 要插入的树
    // para z: 插入的新元素的结点，z.key = value, z.left = nil, z.right = nil
    // 时间 O(h)，每次迭代下降一层，最多下降 h 层

        BSTNode* y = nil;
        BSTNode* x = T.root;
        while (x != nil) {  // 这个迭代会使得最终的 x == nil，并且其位置就是 z 应该在的位置
            y = x;  // 这保证每次迭代后，y 都是 x 的父结点
            if (z->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->p = y;  // z 应该放在现在 x 的所在位置，先连接 y 为父结点再分类链接 z
        if (y == nil) {  // x 作为 T.root 就是 nil，T 为空时
            T.root = z;
        }
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
    }


    // 6.删除

    // (移植，用于删除的子程序)
    static void transplant(BinarySearchTree T, BSTNode* u, BSTNode* v) {
        // para T: 要进行移植操作的树
        // para u: 要移植到的目标位置结点
        // para v: 要移植的子树的根结点，允许是 nil (即一颗空树)
        // O(1) 时间
        // 只是把 u 的父结点的对应子结点移植为 v，把 v 的父结点移植为 u 的父结点，
        // 注意 u 没有经过修改，其父结点指针还是原来的父结点(和 v 现在的父结点一致)，
        // 但是现在没有任何结点的子结点指针是 u，v 原来的父结点其对应子结点指针还是 v
        
        // 这个条件判断操作 u 的父结点对应子结点移植为 v
        if (u->p == nil) {  // u 是 T 的根
            T.root = v;
        }
        else if (u == u->p->left) {
            u->p->left = v;
        }
        else {
            u->p->right = v;
        }

        if (v != nil) {  // 这个条件判断操作 v 的父结点移植为 u 的父结点
            v->p = u->p;
        }

    }

    // (删除)
    static void treeDelete(BinarySearchTree T, BSTNode* z) {
        // para T: 要删结点的树
        // para z: 要删除的结点
        // 时间 O(h)，除定义 z 的后继可能花费 O(h)，其余操作均为 O(1)

        // 情况 1：z 没有子结点,直接将 z.p 的对应子结点换为 nil
        // 情况 2：z 只有一个子结点，将 z.p 的对应位子结点为 z 的唯一子结点
        // 情况 3：z 有两个子结点，其后继 y 是或不是 z 的右子结点

        // 以下两个条件包含 情况 1 和 2，因为 z 的另一个子结点是 nil 时可以被移植
        if (z->left == nil) {
            transplant(T, z, z->right);
        }
        else if (z->right == nil) {
            transplant(T, z, z->left);
        } 
        // 情况 3
        else {
            BSTNode* y = treeMinimum(z->right);   // 此行是该函数中唯一可能 O(h) 的操作
            // 因为 z 有右子结点，y 实际上是 z 的后继，且 y 没有左子结点
            if (y->p != z) {  // 如果 y 不是 z 的右子结点，
                transplant(T, y, y->right);  // 把 y 的右子结点移植到 y 的位置，之后 y 的右子结点指针和父结点指针还需操作
                y->right = z->right;  // 把 y 的右子结点指针换为 z 的右结点
                y->right->p = y;  // z 的原右结点的父节点指针接到 y
                // 此操作后，y 的右子结点下的右树已经满足删除后的情况，只需移植 y 到 z 并继承 z 的左子节点
                // 和 y 本身就是 z 的右子结点的情况一致
            }
            transplant(T, z, y);  // 如果 y 直接就是 z 的右子结点，直接将 y 移植到 z 原位置
            y->left = z->left;  // 将 z 的左子树直接接到 y 的左子结点上，因为那里原来是 nil
             y->left->p = y;  // 把原 z 的左子树的父结点接为 y
        }
        delete z;
    }
};


