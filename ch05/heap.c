//
// Created by sxg on 2019/10/7.下午4:17
//

#include <stdio.h>
#include <stdlib.h>


typedef int Elem;

struct heap {
    Elem *data;
    int capacity;
    int size;
};

typedef struct heap* Heap;

Heap initHeap(int max) {
    Heap p;
    p = (Heap)malloc(sizeof(struct heap));
    if (p == NULL) return NULL;
    p->data = (Elem*)malloc(sizeof(Elem) * (max+1));
    if (!p->data) return NULL;
    p->capacity = max;
    p->size = 0;
    return p;
}

void printHeap(Heap h) {

    for (int i = 1; i <= h->size; i++) {
        printf("%d ", h->data[i]);
    }
    putchar('\n');
}

int isFull(Heap h) {
    return h->capacity == h->size;
}


int isEmpty(Heap h) {
    return h->size == 0;
}

// 向上过滤
void percolateUp(int k, Heap h) {
    Elem x;
    x = h->data[k];

    int i;
    for (i = k; i > 1 && h->data[i] < h->data[i/2]; i /= 2) {
        h->data[i] = h->data[i/2];
    }
    h->data[i] = x;
}
int insertHeap(Elem x, Heap h) {
    if (isFull(h)) return 0;
    h->data[++h->size] = x;

    // 向上过滤
    percolateUp(h->size, h);
    return 1;

}

void percolateDown(int k, Heap h) {
    Elem x;
    x = h->data[k];
    int i, child;
    for (i = k; i*2 <= h->size; i = child) {
        child = i * 2;
        if (child != h->size && h->data[child] > h->data[child+1]) child++;
        if (h->data[i] > h->data[child]) {
            h->data[i] = h->data[child];
        }
    }
    h->data[i] = x;
}

// 删除最小堆的根
int removeHeap(Elem *x, Heap h) {
    if (isEmpty(h)) return 0;
    *x = h->data[1];
    h->data[1] = h->data[h->size--];
    percolateDown(1, h);
    return 1;
}

// O(N)的时间
Heap buildHeap(Elem *a, int size, int max) {
    Heap h;
    h = initHeap(max);
    if (!h) return NULL;
    h->size = size;

    for (int i = 1; i <= size; i++) {
        h->data[i] = a[i-1];
    }
    for (int i = size / 2; i > 0; i--) {
        percolateDown(i, h);
    }
    return h;
}

int main() {
//    Heap h;
//    h = initHeap(10);
//    insertHeap(20, h);
//    printHeap(h);
//    insertHeap(10, h);
//    printHeap(h);
//    insertHeap(5, h);
//    printHeap(h);
//    insertHeap(15, h);
//    insertHeap(30, h);
//    insertHeap(18, h);
//    printHeap(h);
//    Elem x;
//    removeHeap(&x, h);
//    printf("%d\n", x);
//    printHeap(h);

    // 利用O(N)的时间实现一个buildHeap的操作
    Elem a[6] = {10, 50, 60, 5, 30, 20};
    Heap h;
    h = buildHeap(a, 6, 50);
    printHeap(h);

    return 0;
}