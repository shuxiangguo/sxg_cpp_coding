//
// Created by sxg on 2019/9/23.
//

# include<iostream>
#include<stack>
using namespace std;

template<class T>
struct BinNode {
    T data;
    BinNode<T> *left;
    BinNode<T> *right;

    BinNode(T x) {
        data = x;
        left = right = nullptr;
    }
};

template <class T>
class BinaryTree {
protected:
    BinNode<T> *root;
    void rpreprint(BinNode<T> *r) {
        if (r == nullptr) return;
        cout << r->data << " ";
        rpreprint(r->left);
        rpreprint(r->right);
    }

    BinNode<T>* rfindX(T x, BinNode<T> *r) {
        if (r == nullptr) {
            return nullptr;
        }
        if (r->data == x) return r;
        BinNode<T> *found;
        found = rfindX(x, r->left);
        return found ? found : rfindX(x, r->right);
    }

    void rprint(BinNode<T> *r, int depth) {
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

    void rinprint(BinNode<T> *r) {
        if (r == nullptr) return;
        rinprint(r->left);
        cout << r->data << " ";
        rinprint(r->right);
    }

    // 非递归（迭代）形式的先序遍历
    void ipreprint(BinNode<T> *r) {
        stack<BinNode<T>*> st;
        if (r == nullptr) return;
        while (r) {
            cout << r->data << ' ';
            st.push(r);
            r = r->left;

            while (r == nullptr && !st.empty()) {
                r = st.top();
                st.pop();
                r = r->right;
            }
        }
    }
public:
    BinaryTree() { root = nullptr;}
    BinaryTree(T r) {
        root = new BinNode<T>(r);
    }
    ~BinaryTree() {

    }

    //先序遍历
    void preprint() {
        // rpreprint(root);
        ipreprint(root);
        cout << endl;
    }

    BinNode<T>* findX(T x) {
        return rfindX(x,root);
    }

    bool insert(T p, int LorR, T x) {
        BinNode<T> *found;
        found = findX(p);

        if (!found) return false;
        if (LorR == 0) {
            if (found->left) return false;
            found->left = new BinNode<T>(x);
        } else {
            if (found->right) return false;
            found->right = new BinNode<T>(x);
        }
        return true;
    }

    void print() {
        rprint(root, 0);
    }

    // 中序遍历
    void inprint() {
        rinprint(root);
    }

};

int main() {
    BinaryTree<int> bt(11);
    // 在11的左儿子插入22
    bt.insert(11, 0, 22);
    bt.insert(11, 1, 33);

    bt.insert(22, 0, 44);
    bt.insert(33, 1, 55);
    bt.preprint();
    return 0;
}

