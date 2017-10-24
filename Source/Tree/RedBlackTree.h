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
    nodeColor color;  // RBT������ɫ�����BST��RBT���ֻ����һ�� color����Ҫô�� RED Ҫô�� BLACK

    RBTNode* p = nullptr;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;

    // ������ر���
    int h;  // ���Ը߶ȣ��Ӹý�㵽Ҷ�����·���ı���
    int bh;  // ��ɫ�߶ȣ��Ӹý�㵽����Ҷ���·���еĺ�ɫ������������ý��
};


class RedBlackTree {
public:
    // һ�����壺RBT��һ�������BST��ÿ��������һ������ color �� (RED, BLACK)
    // -1.�̳��� BST �����ʣ�
    //        �����������е�ÿ��node��keyֵ������������������ʣ�
    //        ������ BSTNode x ���������е� BSTNode y����y.key <= x.key
    //        �������� BSTNode z, �� x.key <= z.key
    // 0.��һ�� sentinel node nil��������������������ʵ���������ʣ�
    //        nil.color = BLACK; 
    //        ����Ҷ���ָ�� nil; 
    //        root.p = nil;
    //        nil �� key �޹ؽ�Ҫ
    // 1. �κ�һ�����Ǻڼ���
    // 2. ���Ǻڵ�
    // 3. ����Ҷ����Ϊ��(��Ϊnil)
    // 4. ���һ������Ǻ�ɫ����ô���������Ӷ��Ǻ�ɫ
    //        4.1. ���ۣ���һ���Ӹ���Ҷ(nil)�ļ�·���ϣ�������������ɫ���
    // 5. ����һ��������Ҷ��������·�����������ͬ��Ŀ�ĺ�ɫ���
    
    RBTNode* root;
    RBTNode* nil = new RBTNode;  // sentinel node����ɫ��root��p�����е�Ҷ���

    // ���Ժ���
    void inorderTreeWalk(RBTNode* x);

    RedBlackTree(RBTNode* r) {  // ���캯������ʼ���Է��� RBT �Ķ���
        // para r: ��Ϊ�����Ľ��ָ��
        root = r;

        root->color = BLACK;  // (P2)���ڵ�����Ǻ�ɫ
        nil->color = BLACK;  // (P3)Ҷ�������Ǻ�ɫ
        root->p = nil;  // (P0)sentinel node Ҳ�Ǹ����ĸ����
        
        root->left = nil;  
        root->right = nil;  // (P0)nil �����е�Ҷ���
    }

    // ������߶���ص�����
    // 0.����:
    //        RBTNode.h;  // ���Ը߶ȣ��Ӹý�㵽Ҷ�����·���ı���
    //        RBTNode.bh;  // ��ɫ�߶ȣ��Ӹý�㵽����Ҷ���·���еĺ�ɫ������������ý��
    //                     // ������5��bh �� well-defined
    // 1. ����: �߶� h �Ľ�� node���� bh >= h/2
    //            node.h = h => node.bh >= h/2
    //            ������4.1��֤
    // 2. ����: �� x Ϊ���ڵ�����������ڲ������ >= 2^x.bh - 1
    //           ��ѧ���ɣ��� x.h=h, x.hb = b
    //                     x ���� child.h=h-1, child.hb = b �� b-1
    //                     x ���ڽ�� = 2*(2^child.hb - 1) + 1 ����������Ǹ� +1 ��Ҫ�� x �Լ�
    //                                >= 2*(2^(b-1) - 1) + 1 
    //                                = 2^x.bh - 1 
    // 3. ����һ�� RB Tree ����� n ���ڵ�Ļ������ܸ߶� h < 2*lg(n+1)
    //    �����������������ɵ�
    //    ==> ���ս��� 4
    // 4. ���� O(h) ��������� O(lgn) ����

    // ������ת
    // ���������������ֵ������Ҫ�����������
    /*  P                 P
        |                 |
        x      ����ת>    y
       / \               / \
      a   y   <����ת   x   c
         / \           / \
        b   c         a   b
    */
    static void LeftRotate(RedBlackTree T, RBTNode* x) {  // ����ת
        if (x->right == T.nil) {
            printf("x with key=%d 's right is nil. left rotation failed.\n", x->key);
            return;
        }
        RBTNode* y = x->right;  // y ��ԭ x->right

        // �� y->left ���� x->right
        x->right = y->left;
        if (y->left != T.nil) {
            y->left->p = x;
        }

        // �� x->p �� y ����
        if (x->p == T.nil) { // x �� root
            T.root = y;
        }
        else if (x == x->p->left) {
            x->p->left = y;
        }
        else {
            x->p->right = y;
        }
        y->p = x->p;

        // �� x �ŵ� y->left ��λ��
        y->left = x;
        x->p = y;
    }

    static void RightRotate(RedBlackTree T, RBTNode* y) {  // ����ת
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

    // ��.����
    static void RBInsert(RedBlackTree T, RBTNode* z) {
        // ʱ��: O(h) = O(lgn)����Ϊ����� BSTIsert ���Ӷ�һ����Fix Ҳ�� O(lgn)
        // ǰ�벿�ֺ� BST insert ����һ��������� RBInsertFix() ��ά����ɫ
        // �����ֵĬ����ɫΪ��
        
        RBTNode* y = T.nil;  // ��ά��Ϊ x �ĸ����
        RBTNode* x = T.root;  // �� x �Ӹ���㿪ʼ������y ���丸���
        while (x != T.nil) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        // ���� z �� y
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
        z->color = RED;  // ��ʼ���� z ��ɫ
        T.RBInsertFix(T, z);  // ά����ɫ
    }

    static void RBInsertFix(RedBlackTree T, RBTNode* z) {  // �� z �������������� T ��ά����ɫ
        // para T: ���Ľ��й� BSTInsert z ��RBT
        // para z: ������Ľ�㣬��ʼ��ɫ RED
        // ʱ��: O(h) = O(lgn)����Ϊÿ��ѭ������������

        // ���ǿ���Υ���Ķ������
        // -1. z �ĳ�ʼ������Ǹ��� BST ����ģ�OK
        // 1. OK: ��ɫ�ж���
        // 2. ����Υ��: z ��Ϊ T.root��z->color ӦΪ��ɫ����Υ��
        // 3. OK: ����Ҷ�����Ȼ�� T.nil �����Ǻ�ɫ
        // 4. ����Υ��: z->p->color �� z->color ��Ϊ���ʱ���Υ��
        // 5. OK: û���κ�һ��·���ĺ�ɫ��������ı�

        // ע�⣬ά�������ɫ��һ���������ǽ������ɫ����Ϊ��ɫ������ά��4�����ǿ���Υ��5


        while (z->p->color == RED) {  // ѭ������: ��Ŀǰ z �ĸ����죬Υ������ 4������ѭ��
            // ���ݹ���4 (��ɫ�����ӽ��ȫ��)��
            // z->p Ϊ��˵�� z->p->p ������Ϊ��
            // �� z->p->p Ϊ��

            RBTNode* y;    // ���� y Ϊ z �����㣨z->p ���ֵܽ�㣩
            
            // ���������� case���Ҳ��ǻ���
            if (z->p == z->p->p->left) {  // �ر�أ�z ������ root ������ z->p �� nil z->p->p �� nullptr �������
                y = z->p->p->right;  // ���������λ�ø����㸳ֵ
                // case 1: z ������Ϊ��ɫ
                if (y->color == RED) {
                    /* �����·�ʽά����ʹ�� z->p->p ���½������� RBT ���ʣ� �� z->p->p ������һ��ѭ��
                        B           R
                       / \         / \
                      R   R(y) -> B   B(y)
                      |           |
                      R(z)        R(z)
                      ("|"��ʾ���ڸ���������)
                    */
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                // case 2 �� 3 ��ǰ��: z ������ y �Ǻ�ɫ
                else {
                    if (z == z->p->right) {
                        // case 2: y Ϊ���� z �����ӽ�㣬ͨ�����²������� case 3
                        /*     B                        B                         R->B
                        / \      case 2��3      /   \      fix case 3      /    \
                        R(f) B(y)      ->        R    B(y)      ->        R(z)   B->R
                        /  \      f����ת,f=z  /   \       zԭ����ү��ɫ         / \
                        B    R(z)             R(f=z) B       zԭү����ת         B   B(y)
                        */
                        // �� z->p ����������ת��
                        RBTNode* f = z->p;  // z ԭ�����
                        T.LeftRotate(T, f);  // �����ת��Υ�� z->p->p ֮�µ��κι�����Ϊ z ���ӽ�㣬�� f Ϊ�죬����һ�ӽ��Ϊ��
                        z = f;  // ��ת֮�� f �ᴦ��ԭ�� z �� level������ͨ������ indicator �ķ�ʽʵ�ֱ�Ϊ case 3
                    }
                    // case 3: y Ϊ�ڣ�z �����ӽ�� 
                    z->p->color = BLACK;  // ���� z ԭ��Ϊ��
                    z->p->p->color = RED;  // ���� z ԭүΪ��
                    T.RightRotate(T, z->p->p);  // ��ת֮��������ɫά�����
                }
            }
            else if (z->p == z->p->p->right) {  // ��ͬ���� if ��ȫ���ҶԳƣ����� else if ���ų� z->p == T.root �����
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
        // ���һ�ζ�������ѭ��������z->p Ϊ�ڣ�ֻ����Υ��2��������һ�仰�޸�
        T.root->color = BLACK;
    }

    // ��.ɾ��
};