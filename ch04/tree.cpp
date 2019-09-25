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

    // 非递归形式的中序遍历
    void iinprint(BinNode<T> *r) {
        stack<BinNode<T> *> st;
        if (r == nullptr) return;
        while (r) {
            st.push(r);
            r = r->left;

            while (r == nullptr && !st.empty()) {
                r = st.top();
                st.pop();
                // 和先序相比,访问次序不同
                cout << r->data << " ";
                r = r->right;
            }
        }
    }

    int countLeaves(BinNode<T> * r) {
        if (r == nullptr) return 0;
        if (r->left == nullptr && r->right == nullptr) return 1;
        return countLeaves(r->left) + countLeaves(r->right);
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

    // 中序遍历
    void inprint() {
//        rinprint(root);
        iinprint(root);
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

    // 统计叶子节点个数
    /**
     * 输入格式：
Ann
Ann Bill Chris
Bill Daisy Ellen
Chris - Flin
Daisy - -
Ellen Grace Henry
Flin --
Grace --
Henry --
-
     */

    int count() {
        return countLeaves(root);
    }


};

template<class T>
class BSTree : public BinaryTree<T> {
protected:
    // 递归形式查找最大值
    BinNode<T>* rfindMax(BinNode<T>* r) {
        if (r->right == nullptr) return r;
        return rfindMax(r->right); // 尾递归
    }

    // 递归形式插入
    BinNode<T>* rinsert(T x, BinNode<T>* r) {
        if (r == nullptr) {
            r = new BinNode<T>(x);
        } else if (x < r->data){
            r->left = rinsert(x, r->left);
        } else if (x > r->data) {
            r->right = rinsert(x, r->right);
        } else throw -2;
        return r;
    }

    // 递归形式删除
    BinNode<T>* remove(T x, BinNode<T>* r) {
        BinNode<T>* tmp;
        if (!r) throw -1;
        else if (x < r->data) {
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

    // 二叉搜索树找最大值
    BinNode<T>* findMax() {
        // 递归版本
        // return rfindMax(this->root);

        // 迭代版本
        if (this->root == nullptr) return nullptr;
        BinNode<T> *tmp = this->root;
        while (tmp->right) {
            tmp = tmp->right;
        }
        return tmp;

    }

    // 二叉搜索树找最小值
    BinNode<T>* findMin() {
        if(this->root == nullptr) return nullptr;
        BinNode<T>* tmp = this->root;
        while (tmp->left) {
            tmp = tmp->left;
        }
        return tmp;
    }

    // 二叉搜索树找特定值x
    BinNode<T>* findX(T x) {
        if (this->root == nullptr) return nullptr;
        BinNode<T>* tmp = this->root;

        while (tmp && x != tmp->data) {

            if (x < tmp->data) {
                tmp = tmp->left;
            } else {
                tmp = tmp->right;
            }
        }
        return tmp;
    }

    bool insert(T x) {
        try {
            this->root = rinsert(x, this->root);
        } catch (int e) {
            return false;
        }
        return true;
    }

    bool remove(T x) {
        try {
            this->root = remove(x, this->root);
        } catch (int e) {
            return false;
        }
        return true;
    }



};

int main() {
//    BinaryTree<int> bt(11);
//    // 在11的左儿子插入22
//    bt.insert(11, 0, 22);
//    bt.insert(11, 1, 33);
//
//    bt.insert(22, 0, 44);
//    bt.insert(33, 1, 55);
//    cout << "pre print: ";
//    bt.preprint();
//
//    cout << "in print: ";
//    bt.inprint();


//    // 测试查找叶子节点
//    string name;
//    cin >> name;
//    BinaryTree<string> bt(name);
//    cin >> name;
//    while (name != "-") {
//        string lc, rc;
//        cin >> lc >> rc;
//        if (lc != "-") {
//            bt.insert(name, 0, lc);
//        }
//        if (rc != "-") {
//            bt.insert(name, 1, rc);
//        }
//        cin >> name;
//    }
//
//    cout << "Amount: " << bt.count() << endl;

    // 测试二叉搜索树的插入和查找
    BSTree<int> bt;
    bt.insert(10);
    bt.insert(5);
    bt.insert(20);
    bt.insert(55);
    bt.preprint();
    cout << bt.findMax()->data << endl;
    cout << bt.findMin()->data << endl;

    cout << bt.findX(20)->data << endl;
    cout << bt.findX(6) << endl;

    // 测试二叉搜索树删除操作
    bt.remove(5);
    bt.remove(9);
    bt.print();

    return 0;
}

