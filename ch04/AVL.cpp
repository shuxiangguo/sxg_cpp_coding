//
// Created by sxg on 2019/9/27.下午2:14
//

#include "bstree.h"
#include <iostream>

template <class Elem>
class AVLTree : public BSTree<Elem> {
protected:
    int height(BinNode<Elem>* r) {
        if (r == nullptr) return -1;
        return r->h;
    }

    BinNode<Elem>* LLrotate(BinNode<Elem>* r) {
        BinNode<Elem>* child;
        child = r->left;

        r->left = child->right;
        child->right = r;
        r->h = max(height(r), height(r->right) + 1);
        child->h = max(height(child->left), height(child->right) + 1);
        return child; // 新树根
    }

    BinNode<Elem>* RRrotate(BinNode<Elem>* r) {
        BinNode<Elem>* child;
        child = r->right;

        r->right = child->left;
        child->left = r;
        r->h = max(height(r), height(r->right) + 1);
        child->h = max(height(child->left), height(child->right) + 1);
        return child; // 新树根
    }

    BinNode<Elem>* LRrotate(BinNode<Elem>* r) {
        r->left = RRrotate(r->left);
        return LLrotate(r);
    }

    BinNode<Elem>* RLrotate(BinNode<Elem>* r) {
        r->right = LLrotate(r->right);
        return RRrotate(r);
    }

    virtual BinNode<Elem>* rinsert(Elem x, BinNode<Elem>* r) {
        cout << "te" << endl;
        if (r == nullptr) {
            r = new BinNode<Elem>(x);
            if (!r) throw -1;
        } else if (x < r->data) {
            r->left = rinsert(x, r->left);
            if(height(r->left) - height(r->right) == 2) {
                if (x < r->left->data) {
                    r = LLrotate(r);
                } else {
                    r = LRrotate(r);
                }
            }
        } else if (x > r->data) {
            r->right = rinsert(x, r->right);
            if (height(r->right) - height(r->left) == 2) {
                if (x > r->right->data) {
                    r = RRrotate(r);
                } else {
                    r = RLrotate(r);
                }
            }
        } else throw -2;
        r->h = max(height(r->left), height(r->right)) + 1;
        return r;
    }

public:
    AVLTree() {
        this->root = nullptr;
    }
};

int main() {
    AVLTree<int> t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.print();
    return 0;
}
