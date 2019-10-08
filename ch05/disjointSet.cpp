//
// Created by sxg on 2019/10/8.上午11:42
//
// 不相交集（并查集）

#include <iostream>
#include <set>
#include <map>

using namespace std;

template <class T>
struct DisjointSet {
    int *parent;
    T *data;
    map<T, int> m;
    int capacity;
    int size;

    DisjointSet(int max=10) {
        capacity = max;
        size = 0;
        parent = new int[max+1];
        data = new T[max+1];
    }

    ~DisjointSet() {
        delete [] parent;
        delete [] data;
    }

    bool insert(T x) {
        if (size == capacity) return false;
        size++;
        data[size] = x;
        parent[size] = 0;
        m[x] = size; // 方便查找
        return true;
    }

    void print() {
        for (int i = 1; i <= size; i++) {
            cout << i << "\t";
        }
        cout << endl;

        for (int i = 1; i <= size; i++) {
            cout << parent[i] << '\t';
        }
        cout << endl;

        for (int i = 1; i <= size; i++) {
            cout << data[i] << "\t";
        }
        cout << endl;
    }

    int find(T x) {
        typename map<T, int>::iterator it;
        it = m.find(x);
        if (it == m.end()) return -1;
        int i = it->second;
        while (parent[i] > 0) {
            i = parent[i];
        }
        return i;

    }
};

int main() {
    DisjointSet<int> s;
    s.insert(11);
    s.insert(22);
    s.insert(66);
    s.insert(-5);
    s.insert(123);
    s.print();
    cout << s.find(66);
    return 0;
}
