//
// Created by sxg on 2019/9/26.
//

// 二叉树的定义

#ifndef CH04_BINTREE_H
#define CH04_BINTREE_H

#include <iostream>
#include <stack>
using namespace std;

template <class Elem>
struct BinNode {
    Elem data;
    int h;
    BinNode<Elem>* left;
    BinNode<Elem>* right;
    BinNode(Elem x) {
        data = x;
        left = right = nullptr;
        h = 0;
    }
};

template <class Elem>
class BinTree {
protected:
    BinNode<Elem> *root;
    void rpreprint(BinNode<Elem> *r);
    void ipreprint(BinNode<Elem> *r);
    void rinprint(BinNode<Elem> *r);
    int countLeaves(BinNode<Elem> *r);
    BinNode<Elem>* rfindX(Elem x, BinNode<Elem> *r);
    void rprint(BinNode<Elem> *r, int depth);

public:
    BinTree() { root = nullptr; }
    BinTree(Elem r) {
        root = new BinNode<Elem>(r);
    }

    ~BinTree() { }

    // 先序遍历
    void preprint() {
        // rpreprint(root)
        ipreprint(root);
        cout << endl;
    }

    // 中序遍历
    void inprint() {
        rinprint(root);
    }

    // 打印树的信息
    void print() {
        rprint(root, 0);
    }

    // 二叉树查找
    BinNode<Elem>* findX(Elem x);
    int count() {
        return countLeaves(root);
    }

    // 二叉树插入
    bool insert(Elem p, int LorR, Elem x);
};

template <class Elem>
void BinTree<Elem>::rpreprint(BinNode<Elem> * r) {
    if (r == nullptr) return;
    cout << r->data << " ";
    rpreprint(r->left);
    rpreprint(r->right);
}

template <class Elem>
void BinTree<Elem>::ipreprint(BinNode<Elem> * r) {
    stack<BinNode<Elem>*> st;
    if (r == nullptr) return;
    while (r) {
        cout << r->data << " ";
        st.push(r);
        r = r->left;
        while (r == nullptr && !st.empty()) {
            r = st.top();
            st.pop();
            r = r->right;
        }
    }
}

template <class Elem>
void BinTree<Elem>::rinprint(BinNode<Elem> * r) {
    if (r == nullptr) return;
    rinprint(r->left);
    cout << r->data << " ";
    rinprint(r->right);
}

template <class Elem>
int BinTree<Elem>::countLeaves(BinNode<Elem> * r) {
    if (r == nullptr) return 0;
    if (r->left == nullptr && r->right == nullptr) return 1;
    return countLeaves(r->left) + countLeaves(r->right);
}

template <class Elem>
BinNode<Elem>* BinTree<Elem>::rfindX(Elem x, BinNode<Elem> *r) {
    if (!r) return nullptr;
    if (r->data == x) return r;
    BinNode<Elem> *found;
    found = rfindX(x, r->left);
    return found ? found : rfindX(x, r->right);
}

template<class Elem>
void BinTree<Elem>::rprint(BinNode<Elem> *r, int depth) {
    for (int i = 0; i < depth; i++) {
        cout << " ";
    }
    if (!r) {
        cout << "[/]" << endl;
    } else {
        cout << r->data << endl;
        rprint(r->left, depth+1);
        rprint(r->right, depth+1);
    }
}

template <class Elem>
bool insert(Elem p, int LorR, Elem x) {
    BinNode<Elem> *found;
    found = findX(p);

    if (!found) return false;
    if (LorR == 0) {
        if (found->left) return false;
        found->left = new BinNode<Elem>(x);
    } else {
        if (found->right) return false;
        found->right = new BinNode<Elem>(x);
    }
    return true;
}


#endif //CH04_BINTREE_H
