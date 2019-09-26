//
// Created by sxg on 2019/9/26.
//

// 二叉搜索树的实现

#include <iostream>
#include "bintree.h"

template <class Elem>
class BSTree : public BinTree<Elem> {
protected:
    // 递归查找最大值
    BinNode<Elem>* rfindMax(BinNode<Elem>* r) {
        if (r->right = nullptr) return r;

        // 尾递归改成迭代
        return rfindMax(r->right);
    }

    // 递归插入
    BinNode<Elem>* rinsert(Elem x, BinNode<Elem>* r) {
        // 插入失败抛异常
        if (r == nullptr) {
            r = new BinNode<Elem>(x);

            // 内存分配失败
            if (!r) throw -1;
        } else if (x < r->data) {
            r->left = rinsert(x, r->left);
        } else if (x > r->data) {
            r->right = rinsert(x, r->right);
        } else {
            throw -2;
        }
        return r;
    }

    BinNode<Elem>* remove(Elem x, BinNode<Elem>* r) {
        BinNode<Elem>* tmp;
        if (!r) throw -1;
        else if (x < r->data){
            r->left = remove(x, r->left);
        } else if (x > r->data) {
            r->right = remove(x, r->right);
        } else {
            if (r->left && r->right) {
                tmp = rfindMax(r->left);
                r->data = tmp->data;
                r->left = remove(tmp->data, r->left);
            } else {
                tmp = r;
                r = r->left ? r->left : r->right;
                delete tmp;
            }
        }
        return r;
    }
public:
    BSTree() {
        this->root = nullptr;
    }

    BinNode<Elem>* findMax() {

//        return rfindMax(this->root);

        if (this->root == nullptr) return nullptr;
        BinNode<Elem>* tmp = this->root;

        while (tmp->right) {
            tmp = tmp->right;
        }
        return tmp;
    }

    BinNode<Elem>* findMin() {
        if (this->root == nullptr) return nullptr;
        BinNode<Elem>* tmp = this->root;
        while (tmp->left) tmp = tmp->left;
        return tmp;
    }

    BinNode<Elem>* findX(Elem x) {
        BinNode<Elem>* tmp = this->root;
        while (tmp && x != tmp->data) {
            if (x < tmp->data) tmp = tmp->left;
            else tmp = tmp->right;
        }
        return tmp;
    }

    bool insert(Elem x) {
        try {
            this->root = rinsert(x, this->root);
        } catch (int e) {
            return false;
        }
        return true;
    }

    // 二叉搜索树删除
    bool remove(Elem x) {
        try {
            this->root = remove(x, this->root);
        } catch (int e) {
            return false;
        }
        return true;
    }
};

int main() {
    BSTree<int> bt;
    bt.insert(10);
    bt.insert(5);
    bt.insert(20);
    bt.insert(8);
    bt.insert(15);
    bt.insert(2);
    bt.insert(6);
    bt.remove(15);
    bt.print();

    cout << bt.findMin()->data << endl;
    cout << bt.findX(5) << endl;


    return 0;
}
