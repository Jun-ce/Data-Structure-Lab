#pragma once
#include <string>

using namespace std;

enum nodeColor {
    RED,
    BLACK
};

struct RBTNode {
    int key;
    string satelliteData;
    nodeColor color;  // RBT结点的颜色。相比BST，RBT结点只多了一个 color，其要么是 RED 要么是 BLACK

    RBTNode* p = nullptr;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;

    // 性质相关变量
    int h;  // 绝对高度，从该结点到叶结点的最长路径的边数
    int bh;  // 黑色高度，从该结点到任意叶结点路径中的黑色结点数，不含该结点
};


class RedBlackTree {
public:
    // 一、定义：RBT是一种特殊的BST，每个结点多了一个参数 color ∈ (RED, BLACK)
    // -1.继承至 BST 的性质：
    //        二叉搜索树中的每个node其key值满足二叉搜索树的性质：
    //        对任意 BSTNode x 的左子树中的 BSTNode y，有y.key <= x.key
    //        右子树的 BSTNode z, 有 x.key <= z.key
    // 0.有一个 sentinel node nil，满足以下条件，用以实现其他性质：
    //        nil.color = BLACK; 
    //        所有叶结点指向 nil; 
    //        root.p = nil;
    //        nil 的 key 无关紧要
    // 1. 任何一个结点非黑即红
    // 2. 根是黑的
    // 3. 所有叶结点均为黑(此为nil)
    // 4. 如果一个结点是红色，那么其两个孩子都是黑色
    //        4.1. 推论：在一条从根到叶(nil)的简单路径上，不会有连续红色结点
    // 5. 从任一结点出发到叶结点的所有路径，其包含相同数目的黑色结点
    
    RBTNode* root;
    RBTNode* nil = new RBTNode;  // sentinel node，黑色，root的p，所有的叶结点

    // 调试函数
    void inorderTreeWalk(RBTNode* x);

    RedBlackTree(RBTNode* r) {  // 构造函数，初始化以符合 RBT 的定义
        // para r: 作为根结点的结点指针
        root = r;

        root->color = BLACK;  // (P2)根节点必须是黑色
        nil->color = BLACK;  // (P3)叶结点必须是黑色
        root->p = nil;  // (P0)sentinel node 也是根结点的父结点
        
        root->left = nil;  
        root->right = nil;  // (P0)nil 是所有的叶结点
    }

    // 二、与高度相关的推论
    // 0.定义:
    //        RBTNode.h;  // 绝对高度，从该结点到叶结点的最长路径的边数
    //        RBTNode.bh;  // 黑色高度，从该结点到任意叶结点路径中的黑色结点数，不含该结点
    //                     // 由性质5，bh 是 well-defined
    // 1. 推论: 高度 h 的结点 node，其 bh >= h/2
    //            node.h = h => node.bh >= h/2
    //            由性质4.1易证
    // 2. 推论: 以 x 为根节点的子树，其内部结点数 >= 2^x.bh - 1
    //           数学归纳：设 x.h=h, x.hb = b
    //                     x 有俩 child.h=h-1, child.hb = b 或 b-1
    //                     x 的内结点 = 2*(2^child.hb - 1) + 1 ，其中最后那个 +1 是要算 x 自己
    //                                >= 2*(2^(b-1) - 1) + 1 
    //                                = 2^x.bh - 1 
    // 3. 引理：一棵 RB Tree 如果有 n 个内点的话，其总高度 h < 2*lg(n+1)
    //    由以上两推论联立可得
    //    ==> 最终结论 4
    // 4. 所有 O(h) 操作都变成 O(lgn) 操作

    // 三、旋转
    // 基本操作，其他字典操作需要依靠这个操作
    /*  P                 P
        |                 |
        x      向左转>    y
       / \               / \
      a   y   <向右转   x   c
         / \           / \
        b   c         a   b
    */
    static void LeftRotate(RedBlackTree T, RBTNode* x) {  // 向左转
        if (x->right == T.nil) {
            printf("x with key=%d 's right is nil. left rotation failed.\n", x->key);
            return;
        }
        RBTNode* y = x->right;  // y 是原 x->right

        // 将 y->left 连上 x->right
        x->right = y->left;
        if (y->left != T.nil) {
            y->left->p = x;
        }

        // 将 x->p 和 y 连上
        if (x->p == T.nil) { // x 是 root
            T.root = y;
        }
        else if (x == x->p->left) {
            x->p->left = y;
        }
        else {
            x->p->right = y;
        }
        y->p = x->p;

        // 将 x 放到 y->left 的位置
        y->left = x;
        x->p = y;
    }

    static void RightRotate(RedBlackTree T, RBTNode* y) {  // 向右转
        if (y->left == T.nil) {
            printf("y with key=%d 's left is nil. right rotation failed.\n", y->key);
            return;
        }
        RBTNode* x = y->left;

        y->left = x->right;
        if (x->right != T.nil) {
            x->right->p = y;
        }

        if (y->p == T.nil) {
            T.root = x;
        } 
        else if(y == y->p->left) {
            y->p->left = x;
        }
        else {
            y->p->right = x;
        }
        x->p = y->p;

        x->right = y;
        y->p = x;
    }

    // 四.插入
    static void RBInsert(RedBlackTree T, RBTNode* z) {
        // 时间: O(h) = O(lgn)，因为本身和 BSTIsert 复杂度一样，Fix 也是 O(lgn)
        // 前半部分和 BST insert 几乎一样，最后用 RBInsertFix() 来维护颜色
        // 插入的值默认颜色为红
        
        RBTNode* y = T.nil;  // 被维护为 x 的父结点
        RBTNode* x = T.root;  // 用 x 从根结点开始遍历，y 是其父结点
        while (x != T.nil) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        // 链接 z 和 y
        z->p = y;
        if (y == T.nil) {
            T.root = z;
        } 
        else if(z->key < y->key) {
            y->left = z;
        } 
        else {
            y->right = z;
        }
        z->left = T.nil;
        z->right = T.nil;
        z->color = RED;  // 初始赋予 z 红色
        T.RBInsertFix(T, z);  // 维护颜色
    }

    static void RBInsertFix(RedBlackTree T, RBTNode* z) {  // 在 z 被二叉搜索插入 T 后，维护颜色
        // para T: 更改进行过 BSTInsert z 的RBT
        // para z: 被插入的结点，初始颜色 RED
        // 时间: O(h) = O(lgn)，因为每次循环必向上两层

        // 考虑可能违反的定义规则
        // -1. z 的初始插入就是根据 BST 规则的，OK
        // 1. OK: 颜色有定义
        // 2. 可能违反: z 如为 T.root，z->color 应为黑色，会违反
        // 3. OK: 所有叶结点仍然是 T.nil ，仍是黑色
        // 4. 可能违反: z->p->color 和 z->color 都为红的时候会违反
        // 5. OK: 没有任何一条路径的黑色结点数被改变

        // 注意，维护结点颜色的一个操作就是将任意红色结点改为黑色结点可以维持4，但是可能违反5


        while (z->p->color == RED) {  // 循环条件: 当目前 z 的父结点红，违反规则 4，进行循环
            // 根据规则4 (红色结点的子结点全黑)，
            // z->p 为红说明 z->p->p 不可能为红
            // 即 z->p->p 为黑

            RBTNode* y;    // 定义 y 为 z 的叔结点（z->p 的兄弟结点）
            
            // 以下有三种 case，且并非互斥
            if (z->p == z->p->p->left) {  // 特别地，z 不会是 root ，所以 z->p 是 nil z->p->p 是 nullptr 不会存在
                y = z->p->p->right;  // 根据叔结点的位置给叔结点赋值
                // case 1: z 的叔结点为红色
                if (y->color == RED) {
                    /* 按以下方式维护，使得 z->p->p 以下结点均满足 RBT 性质， 从 z->p->p 进行下一个循环
                        B           R
                       / \         / \
                      R   R(y) -> B   B(y)
                      |           |
                      R(z)        R(z)
                      ("|"表示连在父结点左或右)
                    */
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                // case 2 和 3 的前提: z 的叔结点 y 是黑色
                else {
                    if (z == z->p->right) {
                        // case 2: y 为黑且 z 是右子结点，通过以下操作进入 case 3
                        /*     B                        B                         R->B
                        / \      case 2变3      /   \      fix case 3      /    \
                        R(f) B(y)      ->        R    B(y)      ->        R(z)   B->R
                        /  \      f上左转,f=z  /   \       z原父和爷换色         / \
                        B    R(z)             R(f=z) B       z原爷上右转         B   B(y)
                        */
                        // 对 z->p 进行向左旋转，
                        RBTNode* f = z->p;  // z 原父结点
                        T.LeftRotate(T, f);  // 这个旋转不违反 z->p->p 之下的任何规则，因为 z 无子结点，而 f 为红，其另一子结点为黑
                        z = f;  // 旋转之后 f 会处于原本 z 的 level，所以通过更改 indicator 的方式实现变为 case 3
                    }
                    // case 3: y 为黑，z 是左子结点 
                    z->p->color = BLACK;  // 更改 z 原父为黑
                    z->p->p->color = RED;  // 更改 z 原爷为红
                    T.RightRotate(T, z->p->p);  // 右转之后所有颜色维护完毕
                }
            }
            else if (z->p == z->p->p->right) {  // 和同级的 if 完全左右对称，此用 else if 以排除 z->p == T.root 的情况
                y = z->p->p->left;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                else {
                    if (z == z->p->left) {
                        z = z->p;
                        T.RightRotate(T, z);
                    }
                    if (z == T.root || z->p == T.root) {
                        break;
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    T.LeftRotate(T, z->p->p);
                }
            }
        }
        // 如果一次都不满足循环条件，z->p 为黑，只可能违反2，用下面一句话修复
        T.root->color = BLACK;
    }

    // 五.删除
};