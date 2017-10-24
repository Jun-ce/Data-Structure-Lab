#pragma once
#include <string>

using namespace std;

struct BSTNode  //������������ÿһ�����,�����������Ϣ
{

    int key;  // ���Ĺؼ���
    string satelliteData;  // ������������

    BSTNode* left = nullptr;  // �������ӽ��
    BSTNode* right = nullptr;  // �������ӽ��
    BSTNode* p = nullptr;  // ���ĸ����
}; 

BSTNode* nil = nullptr;  // ��㲻�����ӽ����߸����ʱָ�� nil

class BinarySearchTree {  // ����������
public:
    // BST�Ķ���
    // �����������е�ÿ��node��keyֵ������������������ʣ�
    // ������ BSTNode x ���������е� BSTNode y����y.key <= x.key
    // �������� BSTNode z, �� x.key <= z.key


    // BST�Ĳ���
    BSTNode* root = nil;     // һ�Ŷ����������ĸ�����Ψһ����

    
    // BST�����ʣ�
    int n;  // �ܽ����
    int h;  // ��


    // 1. �������
    static void inorderTreeWalk(BSTNode* x)  {
        // para x: ����T.root
        // return: void
        // �������ʼ��ӡ����������keyֵ�������ǴӸ���ʼ�ı���
        // O(n) ʱ�䣬��ÿ����㶼������һ�η���
        if (x != nil) {
            inorderTreeWalk(x->left);
            printf("%d ", x->key);  // ��ÿ����㶼������һ���������
            inorderTreeWalk(x->right);
        }
    }

    // 2.����
    
    //(�ݹ����ʽ����)
    static BSTNode* treeSearch(BSTNode* x, int k) {
        // para x: ��ʼ���ҵĸ����
        // para k: ���ҵĹؼ���ֵ
        // return: �ҵ�keyΪk�Ľ�㣬����ƥ�����򷵻� nil
        // O(h) ʱ�䣬ÿ�εݹ�һ���������һ�㣬�����γ�һ���Ӹ����׵�simple path������ײ�ض�return
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

    //(��������ʽ����)
    static BSTNode* iterativeTreeSearch(BSTNode* x, int k) {
        // para x: ��ʼ���ҵĸ����
        // para k: ���ҵĹؼ���ֵ
        // return: �ҵ�keyΪk�Ľ�㣬����ƥ�����򷵻� nil
        // O(h) ʱ�䣬ÿ�ε���һ���������һ�㣬����ײ�ض�return
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

    // 3.��Сֵ�����ֵ

    // (��Сֵ)
    static BSTNode* treeMinimum(BSTNode* x) {
        // para x: ��ʼ������Сֵ�ĸ����
        // return: �ҵ���Сֵ�Ľ��
        // O(h) ʱ�䣬�����׵� simple path
        while (x->left != nil) {
            x = x->left;
        }
        return x;
    }

    // (���ֵ)
    static BSTNode* treeMaximum(BSTNode* x) {
        // ����Сֵ�Գ�
        // O(h) ʱ��
        while (x->right != nil) {
            x = x->right;
        }
        return x;
    }

    // 4. ��̺�ǰ��

    // (���)
    static BSTNode* treeSuccessor(BSTNode* x) {
        // para x: ��ҪѰ�Һ�̵� node
        // return: x �ĺ�̣��粻������ nil
        // ���ڶ��������������ʣ�ʵ���ϲ�����Ҫ�Ƚϸ��� key ֵ������ɱ�����
        // ʱ�� O(h), ÿ�ε������ϻ���һ�㣬������ h ��

        if (x->right != nil) {  // ��� x �����ӽ��
            // x ���������е����н�㶼�� x ����
            // (1)�� x �� x.p �����ӽ�㣬�� x < x.p�������� x �������е����н�㶼�� x.p С����Ϊ������� x.p ����������
            // (2)�� x �� x.p �����ӽ�㣬�� x > x.p��x �ĺ��ֻ���� x �Լ������ӽ���д��� (�鷳������)
            return treeMinimum(x->right);  // ֱ�ӷ��� x ����������СԪ�صļ���
        }
        BSTNode* y = x->p;  // ������ݵ� x �ĸ���� y
        while (y != nil && x == y->right) {  
            // ֻҪû���ݵ�xΪ����㣬�� x ��Ϊ y ���ҽ�㣬�� x > y
            x = y;
            y = y->p; // �����б�ʾ�������ϻ���
        }
        return y; // ���ݵ���ֹΪ��
                  // (1) x ���˸���㣬y ����nil����ԭ����min���޺�̣� 
                  // (2) x ���丸�������㣬����һ�� x < y������ y
    }


    // (ǰ��)
    static BSTNode* treePredecessor(BSTNode* x) {
        // para x: ��ҪѰ��ǰ���� node
        // return: x ��ǰ�����粻������ nil
        // ���ڶ��������������ʣ�ʵ���ϲ�����Ҫ�Ƚϸ��� key ֵ������ɱ�����
        // ���̶Գ�

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


    // 5.����
    static void treeInsert(BinarySearchTree T, BSTNode* z) {
    // para T: Ҫ�������
    // para z: �������Ԫ�صĽ�㣬z.key = value, z.left = nil, z.right = nil
    // ʱ�� O(h)��ÿ�ε����½�һ�㣬����½� h ��

        BSTNode* y = nil;
        BSTNode* x = T.root;
        while (x != nil) {  // ���������ʹ�����յ� x == nil��������λ�þ��� z Ӧ���ڵ�λ��
            y = x;  // �Ᵽ֤ÿ�ε�����y ���� x �ĸ����
            if (z->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->p = y;  // z Ӧ�÷������� x ������λ�ã������� y Ϊ������ٷ������� z
        if (y == nil) {  // x ��Ϊ T.root ���� nil��T Ϊ��ʱ
            T.root = z;
        }
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
    }


    // 6.ɾ��

    // (��ֲ������ɾ�����ӳ���)
    static void transplant(BinarySearchTree T, BSTNode* u, BSTNode* v) {
        // para T: Ҫ������ֲ��������
        // para u: Ҫ��ֲ����Ŀ��λ�ý��
        // para v: Ҫ��ֲ�������ĸ���㣬������ nil (��һ�ſ���)
        // O(1) ʱ��
        // ֻ�ǰ� u �ĸ����Ķ�Ӧ�ӽ����ֲΪ v���� v �ĸ������ֲΪ u �ĸ���㣬
        // ע�� u û�о����޸ģ��丸���ָ�뻹��ԭ���ĸ����(�� v ���ڵĸ����һ��)��
        // ��������û���κν����ӽ��ָ���� u��v ԭ���ĸ�������Ӧ�ӽ��ָ�뻹�� v
        
        // ��������жϲ��� u �ĸ�����Ӧ�ӽ����ֲΪ v
        if (u->p == nil) {  // u �� T �ĸ�
            T.root = v;
        }
        else if (u == u->p->left) {
            u->p->left = v;
        }
        else {
            u->p->right = v;
        }

        if (v != nil) {  // ��������жϲ��� v �ĸ������ֲΪ u �ĸ����
            v->p = u->p;
        }

    }

    // (ɾ��)
    static void treeDelete(BinarySearchTree T, BSTNode* z) {
        // para T: Ҫɾ������
        // para z: Ҫɾ���Ľ��
        // ʱ�� O(h)�������� z �ĺ�̿��ܻ��� O(h)�����������Ϊ O(1)

        // ��� 1��z û���ӽ��,ֱ�ӽ� z.p �Ķ�Ӧ�ӽ�㻻Ϊ nil
        // ��� 2��z ֻ��һ���ӽ�㣬�� z.p �Ķ�Ӧλ�ӽ��Ϊ z ��Ψһ�ӽ��
        // ��� 3��z �������ӽ�㣬���� y �ǻ��� z �����ӽ��

        // ���������������� ��� 1 �� 2����Ϊ z ����һ���ӽ���� nil ʱ���Ա���ֲ
        if (z->left == nil) {
            transplant(T, z, z->right);
        }
        else if (z->right == nil) {
            transplant(T, z, z->left);
        } 
        // ��� 3
        else {
            BSTNode* y = treeMinimum(z->right);   // �����Ǹú�����Ψһ���� O(h) �Ĳ���
            // ��Ϊ z �����ӽ�㣬y ʵ������ z �ĺ�̣��� y û�����ӽ��
            if (y->p != z) {  // ��� y ���� z �����ӽ�㣬
                transplant(T, y, y->right);  // �� y �����ӽ����ֲ�� y ��λ�ã�֮�� y �����ӽ��ָ��͸����ָ�뻹�����
                y->right = z->right;  // �� y �����ӽ��ָ�뻻Ϊ z ���ҽ��
                y->right->p = y;  // z ��ԭ�ҽ��ĸ��ڵ�ָ��ӵ� y
                // �˲�����y �����ӽ���µ������Ѿ�����ɾ����������ֻ����ֲ y �� z ���̳� z �����ӽڵ�
                // �� y ������� z �����ӽ������һ��
            }
            transplant(T, z, y);  // ��� y ֱ�Ӿ��� z �����ӽ�㣬ֱ�ӽ� y ��ֲ�� z ԭλ��
            y->left = z->left;  // �� z ��������ֱ�ӽӵ� y �����ӽ���ϣ���Ϊ����ԭ���� nil
             y->left->p = y;  // ��ԭ z ���������ĸ�����Ϊ y
        }
        delete z;
    }
};


