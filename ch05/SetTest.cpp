//
// Created by sxg on 2019/10/8.上午11:17
//

#include <iostream>
#include <set>

using namespace std;

int main() {
    set<int> s;
    s.insert(123);
    s.insert(23);
    s.insert(11);
    s.insert(-5);
    s.insert(666);

    for (auto x : s) {
        cout << x << " ";
    }
    cout << endl;

    set<int> s2;
    s2.insert(11);
    s2.insert(99);
    s.insert(s2.begin(), s2.end());
    for (auto x : s) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}