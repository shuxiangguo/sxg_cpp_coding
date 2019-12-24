//
// Created by sxguoli on 2019/12/24.
//

#include<iostream>
#include <vector>
#include <queue>

using namespace std;

// 贪心法构建霍夫曼树
struct Node {
    int data;
    Node* left;
    Node* right;

    Node() {
        left = right = nullptr;
    }

    Node(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

struct HuffmanTree {
    Node* root;
    HuffmanTree() {
        root = nullptr;
    }

    HuffmanTree(int weight) {
        root = new Node(weight);
    }

    HuffmanTree(vector<HuffmanTree> &nodes) {
        priority_queue<HuffmanTree, vector<HuffmanTree>, greater<HuffmanTree>> q(nodes.begin(), nodes.end());
        HuffmanTree tmp;
        for (int i = 1; i < nodes.size(); i++) {
            tmp.root = new Node;
            tmp.root->left = q.top().root;
            q.pop();
            tmp.root->right = q.top().root;
            q.pop();
            tmp.root->data = tmp.root->left->data + tmp.root->right->data;
            q.push(tmp);
        }
        root = q.top().root;
    }

    bool operator > (const HuffmanTree &t) const {
        return this->root->data > t.root->data;
    }

    void print() {
        rprint(root, 0);
    }

    void rprint(Node *r, int depth) {
        for (int i = 0; i < depth; i++) cout << " ";
        if (!r) cout << "[/]" << endl;
        else {
            cout << r->data << endl;
            rprint(r->left, depth+1);
            rprint(r->right, depth+1);
        }
    }
};

int main() {
    int nv, weight;
    cin >> nv;
    vector<HuffmanTree> nodes;
    for (int i = 0; i < nv; i++) {
        cin >> weight;
        nodes.emplace_back(weight);// 自动调用HuffmanTree的构造函数
    }

    HuffmanTree ht(nodes);
    ht.print();
    return 0;
}

/*
7
10 15 12 3 4 13 1
 */
