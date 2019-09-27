//
// Created by sxg on 2019/9/27.下午1:59
//

#ifndef CH04_BSTREE_H
#define CH04_BSTREE_H

#include <iostream>
#include "bintree.h"

using namespace std;

template <class Elem>
class BSTree : public BinTree<Elem> {
protected:
    // 递归查找最大值
    BinNode<Elem>* rfindMax(BinNode<Elem>* r) {
        if (r->right == nullptr) return r;
        return rfindMax(r->right); // 尾递归
    }

    // 递归插入
    // C++ 默认静态联编，通过使用virtual关键字，改成动态联编
    virtual BinNode<Elem>* rinsert(Elem x, BinNode<Elem>* r) {
        if (r == nullptr) {
            r = new BinNode<Elem>(x);
            if (!r) throw -1;
        } else if (x < r->data) {
            r->right = rinsert(x, r->right);
        } else if (x > r->data) {
            r->left = rinsert(x, r->left);
        } else throw -2;
        return r;
    }

    // 递归删除节点
    BinNode<Elem>* remove(Elem x, BinNode<Elem>* r) {
        BinNode<Elem>* tmp;
        if (!r) throw -1;
        else if (x < r->data) {
            r->left = remove(x, r->left);
        } else if (x > r->data) {
            r->right = remove(x, r->right);
        } else {
            if (r->left && r->right) {
                tmp = rfindMax(r->left);
                r->data = tmp->data;
                // 递归删除左二子最大节点
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
        // return rfindMax(this->root);
        if (this->root == nullptr) {
            return nullptr;
        }
        BinNode<Elem>* tmp = this->root;
        while (tmp->right) {
            tmp = tmp->right;
        }
        return tmp;
    }

    BinNode<Elem>* findMin() {
        if (this->root == nullptr) {
            return nullptr;
        }
        BinNode<Elem>* tmp = this->root;
        while (tmp->left) {
            tmp = tmp->left;
        }
        return tmp;
    }

    BinNode<Elem>* findX(Elem x) {
        BinNode<Elem>* tmp = this->root;
        while (tmp && tmp->data != x) {
            if (x < tmp->data) {
                tmp = tmp->left;
            } else {
                tmp = tmp->right;
            }
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

#endif //CH04_BSTREE_H
