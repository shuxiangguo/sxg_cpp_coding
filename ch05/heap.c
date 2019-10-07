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

// 向上过滤
void percolateUp(int k, Heap h) {
    int x;
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

int main() {
    Heap h;
    h = initHeap(10);
    insertHeap(20, h);
    printHeap(h);
    insertHeap(10, h);
    printHeap(h);
    insertHeap(5, h);
    printHeap(h);
    insertHeap(15, h);
    printHeap(h);
    return 0;
}