#pragma once

#include <vector>

using namespace std;

struct BTNode {
    int n;  // node 中当前存储的 key 的数量
    vector<int> key;  // node 含有的 n 个 key, 且 从 this->key[0] 到 this->key[n-1] 是顺序排序
    bool leaf; // node 是否为叶结点

    vector<BTNode*> c;  // 内部节点有 n+1 个 指向子结点的指针，从 this->c[0] 到 this->c[n]
    // key[i] 分割了 c 的 key 取值范围
    // c[0]->key[any] <= this->key[0] <= c[1]->key[any] ... <= this->key[n-1] <= c[n]->key[any]

};

class BTree{
    // 一、定义
    // 1. 每个 node 的 key[] 中的有 n 个当前元素，且顺序排列
    // 2. 每个 node 的 c[] 子结点有 n+1 个
    // 3. key[i] 分割了子结点 c[i], c[i+1] 的 key 取值范围
    //          c[0]->key[any] <= this->key[0] <= c[1]->key[any] ... <= this->key[n-1] <= c[n]->key[any]
    // 4. 每个结点的深度一致，称为树高 h
    // 5. 树本身有一个常数 t>=2, 称为最小度数，限制了所有结点的 key 数量上下限
    //      a. 除了根结点，所有结点至少有 t-1 个 key，也就是至少 t 个子结点，如果树非空，根结点至少一个 key
    //      b. 所有结点至多有 2t-1 个 key 也就是 2t 个子结点。对于 2t-1 个 key 的结点称为满结点

    // 二、高度相关性质
    // 1. 对于非空B树，共 n>=1 个 key, h 的高度，t>=2 最小度数
    //      h <= log_t (n+1)/2
    //      证明：用 t 对每个结点 key 的数量下限, h 对每级最多结点数限制证明
    // n >= 1 + (t-1) * Sum_(i=1 to h)[2*t^(i-1)]
    //    = 1 + 2(t-1) * ( (t^h -1)/(t-1) )
    //    = 2*t^h - 1
    // =>   h <= log_t (n+1)/2

    // 三、搜索
    static BTNode* BTreeSearch(BTNode* x, int k) {
        // 时间：O(th) = O(t*log_t(n))

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