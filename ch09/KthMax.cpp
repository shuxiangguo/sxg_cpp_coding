//
// Created by sxguoli on 2019/12/24.
//

// 寻找第k大的值

#include<iostream>
using namespace std;

#define maxsize 100

void  findKMax(int a[], int left, int right, int k) {
    int i = left, j = right;
    int partition = a[i];
    while (i != j) {
        while (i < j && a[j] > partition) {
            j--;
        }
        swap(a[i], a[j]);
        while (i < j && a[i] < partition) {
            i++;
        }
        swap(a[i], a[j]);
        if (right-i+1 == k) return;
        else if (right-i+1 > k) {
            findKMax(a, i+1, right, k);
        } else if (right-i+1 < k) {
            findKMax(a, left, i-1, k-(right-i+1));
        }
    }
}
int main() {
    int a[maxsize];
    int n;
    int k;
    cout << "input the length of arr:";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << "input K:";
    cin >> k;

    findKMax(a, 0, n-1, k);
    cout << "the k-th max number is " << a[n-k] << endl;
    return 0;
}

// 8 3 4 1 9 7 10 6
