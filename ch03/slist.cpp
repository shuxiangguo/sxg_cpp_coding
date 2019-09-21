//
// Created by sxg on 2019/9/20.
//


#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v;
    v.push_back(11);
    v.push_back(22);
    v.push_back(33);
    v.insert(v.begin(), 44);
    v.erase(v.begin()+1);
    for (int i : v) {
        cout << i << ", ";
    }
    cout << endl;
    return 0;
}
