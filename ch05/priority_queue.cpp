//
// Created by sxg on 2019/10/8.上午12:35
//

#include <iostream>
#include <queue>

using namespace std;
int main() {
    // C++里面的堆默认是大根堆
//    priority_queue<int> q;
    priority_queue<int, vector<int>, greater<int>> q;
    q.push(111);
    q.push(222);
    q.push(333);
    q.push(11);
    q.push(22);
    cout << q.top() << endl;
    q.pop();
    cout << q.top() << endl;
    q.pop();
    return 0;
}