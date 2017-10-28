#include "RedBlackTree.h"

void RedBlackTree::inorderTreeWalk(RBTNode* x)
{
    if (x != this->nil) {
        inorderTreeWalk(x->left);
        printf("Key:%d Color:%d P:%d L:%d R:%d\n", x->key, x->color, x->p->key, x->left->key, x->right->key);  // ��ÿ����㶼������һ���������
        inorderTreeWalk(x->right);
    }
}

RBTNode * RedBlackTree::treeMinimum(RBTNode * x)
{
    // para x: ��ʼ������Сֵ�ĸ����
    // return: �ҵ���Сֵ�Ľ��
    // O(h) ʱ�䣬�����׵� simple path
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

RBTNode * RedBlackTree::treeMaximum(RBTNode * x)
{
    // ����Сֵ�Գ�
    // O(h) ʱ��
    while (x->right != nil) {
        x = x->right;
    }
    return x;
}

RBTNode * RedBlackTree::treeSuccessor(RBTNode * x)
{
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
    RBTNode* y = x->p;  // ������ݵ� x �ĸ���� y
    while (y != nil && x == y->right) {
        // ֻҪû���ݵ�xΪ����㣬�� x ��Ϊ y ���ҽ�㣬�� x > y
        x = y;
        y = y->p; // �����б�ʾ�������ϻ���
    }
    return y; // ���ݵ���ֹΪ��
              // (1) x ���˸���㣬y ����nil����ԭ����min���޺�̣� 
              // (2) x ���丸�������㣬����һ�� x < y������ y
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
