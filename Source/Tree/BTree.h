#pragma once

#include <vector>

using namespace std;

struct BTNode {
    int n;  // node �е�ǰ�洢�� key ������
    vector<int> key;  // node ���е� n �� key, �� �� this->key[0] �� this->key[n-1] ��˳������
    bool leaf; // node �Ƿ�ΪҶ���

    vector<BTNode*> c;  // �ڲ��ڵ��� n+1 �� ָ���ӽ���ָ�룬�� this->c[0] �� this->c[n]
    // key[i] �ָ��� c �� key ȡֵ��Χ
    // c[0]->key[any] <= this->key[0] <= c[1]->key[any] ... <= this->key[n-1] <= c[n]->key[any]

};

class BTree{
    // һ������
    // 1. ÿ�� node �� key[] �е��� n ����ǰԪ�أ���˳������
    // 2. ÿ�� node �� c[] �ӽ���� n+1 ��
    // 3. key[i] �ָ����ӽ�� c[i], c[i+1] �� key ȡֵ��Χ
    //          c[0]->key[any] <= this->key[0] <= c[1]->key[any] ... <= this->key[n-1] <= c[n]->key[any]
    // 4. ÿ���������һ�£���Ϊ���� h
    // 5. ��������һ������ t>=2, ��Ϊ��С���������������н��� key ����������
    //      a. ���˸���㣬���н�������� t-1 �� key��Ҳ�������� t ���ӽ�㣬������ǿգ����������һ�� key
    //      b. ���н�������� 2t-1 �� key Ҳ���� 2t ���ӽ�㡣���� 2t-1 �� key �Ľ���Ϊ�����

    // �����߶��������
    // 1. ���ڷǿ�B������ n>=1 �� key, h �ĸ߶ȣ�t>=2 ��С����
    //      h <= log_t (n+1)/2
    //      ֤������ t ��ÿ����� key ����������, h ��ÿ�������������֤��
    // n >= 1 + (t-1) * Sum_(i=1 to h)[2*t^(i-1)]
    //    = 1 + 2(t-1) * ( (t^h -1)/(t-1) )
    //    = 2*t^h - 1
    // =>   h <= log_t (n+1)/2

    // ��������
    static BTNode* BTreeSearch(BTNode* x, int k) {
        // ʱ�䣺O(th) = O(t*log_t(n))

        int i = 0;
        while (i < x->n && k> x->key[i]) {
            i = i + 1;
        }
        if (i < x->n && k == x->key[i]) {
            printf("Find %d in this node's &dth position", k, i);
            return x;  // return(x,i)
        }
        else if (x->leaf) {
            return nullptr;
        }
        else {
            // DiskRead(x->c[i]);
            return BTreeSearch(x->c[i], k);
        }
    }
};