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

    // BST �̳к������㷨һ�£����ڴ�ʵ��
    void inorderTreeWalk(RBTNode* x);
    RBTNode* treeMinimum(RBTNode* x);
    RBTNode* treeMaximum(RBTNode* x);
    RBTNode* treeSuccessor(RBTNode* x);
    RBTNode* treePredecessor(RBTNode* x);


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
    static void LeftRotate(RedBlackTree & T, RBTNode* x) {  // ����ת
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

    static void RightRotate(RedBlackTree & T, RBTNode* y) {  // ����ת
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
    static void RBInsert(RedBlackTree & T, RBTNode* z) {
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

    static void RBInsertFix(RedBlackTree & T, RBTNode* z) {  // �� z �������������� T ��ά����ɫ
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
                    T.RightRotate(T, z->p->p);  // ��ת֮��������ɫά�����, ��һ��ѭ�����ٽ���
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
    static RBTNode* RBDelete(RedBlackTree & T, RBTNode* z) {
        // ɾ���ı���ʵ�����ǽ� z �ĺ��ֵ���� z��Ȼ��ɾ�� z �ĺ��
        // return y: ������ɾ���Ľ��
        // ʱ�� O(h) = O(logn)

        RBTNode* y;  // ����������ɾ���Ľ�� y
        if (z->left == T.nil || z->right == T.nil) {
            y = z;  // ��� z ֻ�е��ӣ�����ɾ��̣�ɾ z �Լ�����
        }
        else {
            y = T.treeSuccessor(z);
        }
        RBTNode* x;  // ���弴������ y λ�õ��ӽ�� x������������ң������� nil
        if (y->left != T.nil) {
            x = y->left;
        }
        else {
            x = y->right;
        }
        x->p = y->p;  // ������ y ���ӽ�� x ���� y->p
        // ���������� y->p ���� x
        if (y->p == T.nil) {
            T.root = x;
        }
        else if (y == y->p->left) {
            y->p->left = x;
        }
        else {
            y->p->right = x;
        }
        // ���ɾ�Ĳ��� z �����ǰ�ɾǰ�ĺ�� y �����ݸ��� z
        if (y != z) {
            z->key = y->key;
            z->satelliteData = y->satelliteData;
        }
        // ��ɾ���� y �Ǻ�ɫʱ���п������ì�ܣ���Ҫ�޸���ɫ
        // ɾ����ɫ����Υ���κ�һ�����ʣ��ʲ���
        if (y->color == BLACK) {
            T.RBDeleteFixup(T, x);
        }
        return y;
    }

    static void RBDeleteFixup(RedBlackTree T, RBTNode* x){
        // para x: ��ɾ���Ľڵ� y ��ԭ�ӽ�㣬�� x �Ѿ��滻 y ��ԭλ��
        // ��ɾ����һ����ɫ��� x->p ʱ���������ɾ������������ĸ���㣩
        // �п���Υ�������ʣ�
        // 1. OK: ��ɫ��Ȼ�ж��壬û��Υ��
        // 2. (y ����x ��) ��� y �Ǹ���㣬�� x �Ǻ�ɫ�ģ��ǻ�Υ�����Ǻ�ɫ�Ķ���
        // 3. OK: ����Ҷ�����ȻΪ nil��Ϊ�ڣ�����Υ��
        // 4. (y->p �죬x ��) y->p �� x �Ѿ����ӣ�������������Ǻ�ɫ������Υ����ɫ�ڵ����ȫ�ڵĶ���
        // 5. y һ���Ǻ�ɫ��������·���ϵĺ�ɫ������ض���һ��Υ������·���ڸ�һ��
        //  ��� x ����Ϊ�죬ֱ�ӽ����޸�Ϊ��ɫ����ά�������������
        //  ���濼�ǵ� x Ϊ��ɫʱ��ά��
        //  ˼·���� x ����ɫһ��"����ĺ�ɫ"��
        //       ��� x ����Ϊ�ڣ������ɫ���˫�ڣ������ɺ��
        //       �øı� x ��ָ��� node ʵ��
        //       ��x �����ķ���ά��������ָ�룬���;�аѺ�ڵĵ��ʾ�ɺ�ɫ��������Ⱦɫ����ת���޸�����
        //       ÿ�ε�������ֹʱ x ����һ�����ֱ���������ڵ�
        //       �������������ĺ�ɫ��ά���������� Case 4 �ĳ����������ڵ�ʱ��
        //       ����·������ʵ�ڸ�(�����Ƕ����ɫ�ĺڸ�)��ȣ�ֱ��ɾ������ĺ�ɫ��ά������ 5
        // Fixup ��ʱ���� O(h) = O(logn)
        
        // Case ALL ��ǰ��: �� x Ϊ��ɫʱ��ά��
        while (x != T.root && x->color == BLACK) {
            RBTNode* w; // w �� x ���ֵܽ�� (sibling)
            if (x == x->p->left) {  // w �ֵܽ�����Ҳ�
                w = x->p->right; 
            // Case 1: ���ֵܽ���Ǻ�ɫʱ����˫�Ӻ͸���� x->p һ��ȫ��
                if (w->color == RED) {  
                    w->color = BLACK;  
                    x->p->color = RED;  // �����������ֵܽ�����ɫ
                    T.LeftRotate(T, x->p);  // �Ӹ������ת�����ֵܽ��ת��ȥ
                    w = x->p->right;  // ת��֮��� x �����ֵ���ԭ�ֵܵ��ӽ�㣬�ض��Ǻ�
                }  // ==> ���� Case 2,3,4 
            //  Case 2,3,4 �Ĵ�ǰ�᣺�ֵܽڵ��Ǻ�ɫ
                //  �� x �� w ��һ��ĺ�����һ��(˫�ڱ�ڣ���ڱ��)��x �� w �ĸ��������һ����
                //  ��Ϊ x һ����˫�ڣ����ƺ�ɫ���䣬���Ը��� w ���ӽ����ɫ�����з���
                
                // Case 2: ���ֵܽڵ�����Ϊ�ڣ�����˫��ȫ�� 
                if (w->left->color == BLACK &&  
                    w->right->color == BLACK) {
                    w->color = RED;  // w ��ɺ�ɫû���κ�����
                    x = x->p;  // x �������ĺ�ɫ��ָ������һ��
                    // �˴���ѭ�����������x->p�Ǻ�ɫ����һ��ֱ���޸���ɣ�����Ǻ�ɫ�������޸�
                }
                else { 
                // Case 3,4 ��ǰ��: w �к�ɫ�ӽ��ʱ
                    // Case 3: �ֵܽ��Ϊ�ڣ������Ӻ죬���Ӻ�
                    if (w->right->color == BLACK) {  
                        w->color = RED;
                        w->left->color = BLACK;  // ���� w �����ӽ����ɫ
                        T.RightRotate(T, w);  // �� w ����ת���������ӽڵ�ת�� w ��ԭλ��
                        w = x->p->right;  // x �µ��ֵܽ��Ϊ������ȥ�ĺ�ɫ�������ֵܽڵ����ӽ����ԭ�ֵܽڵ㣬������Ϊ��ɫ
                    }  // ==> Case 4
                    // Case 4: �ֵܽڵ����ӽ��Ϊ��ɫʱ
                    w->color = x->p->color;
                    x->p->color = BLACK;  // �����ֵܽڵ�(��)�͸����(��ɫδ֪)����ɫ
                    w->right->color = BLACK;  // ���ֵܽڵ����ӽ��ĺ�ɫ��Ϊ��ɫ
                    T.LeftRotate(T, x->p);  // ��x->p��ת���ѻ�����ɫ�� w ת����
                    // ��ʱԭ x->p λ����ԭ w, ��˫���Ǳ���Ϊ��ɫ��ԭ x->p ��ԭ w->right����Ϊ��ɫ
                    // ԭ w ����Ϊ��ԭ x->p ����ɫ�������ɫ��˫��Ϊ��ʱһ����������
                    // ��ԭ x ����һ�㣬����һ������Ϊ��ɫ�ĸ����ԭ x ->p
                    // ԭ w ���ӽ�������˱���Ϊ��ɫ��ԭ x->p �ϣ��㼶���䣬��ԭ��Ϊԭ w ҲΪ�ڣ��ڸ߲���
                    // �����������������
                    x = T.root; // ֱ�ӽ���ѭ�����ڣ�������һԭ x->p ����ɫΪ��ɫ���ڸ��ϣ�ѭ�������ά����ɫ
                }
            }

            // ���¶Գƣ��� x ���ֵܽ������һ������ʱ
            else {
                w = x->p->left;
                // Case 1
                if (w->color == RED) {
                    x->p->color = RED;
                    w->color = BLACK;
                    T.RightRotate(T, x->p);
                    w = x->p->left;
                }
                // Case 2
                if (w->left->color == BLACK &&
                    w->right->color == BLACK) {
                    w->color = RED;
                    x = x->p;
                }
                else {
                    // Case 3
                    if (w->left->color == BLACK) {
                        w->color = RED;
                        w->right->color = BLACK;
                        T.LeftRotate(T, w);
                        w = x->p->left;
                    }
                    // Case 4
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->left->color = BLACK;
                    T.RightRotate(T, x->p);
                    x = T.root;
                }
            }
        }
        // ���գ���ԭ��Ϊ��ɫ�� x �����߿���Ϊ��ɫ�ĸ�Ⱦ�ɺ�ɫ��ά������
        x->color = BLACK;
    }

};