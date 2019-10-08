//
// Created by sxg on 2019/10/8.下午4:25
//

#include <cstdio>
#include <cstdlib>

enum GridStatus {Active, Removed, Empty};;
typedef enum GridStatus Status;

struct HashTable {
    int *key;
    Status *status;
    int size;
    int remains;
};

typedef struct HashTable* HT;;

HT initHashTable(int size) {
    HT h;
    h = (HT)malloc(sizeof(struct HashTable));
    if (!h) { return NULL;}
    h->size = h->remains = size;
    h->key = (int*)malloc(sizeof(int) * size);
    if (!h->key) {
        free(h);
        return NULL;
    }
    h->status = (Status*)malloc(sizeof(Status)*size);
    if (!h->status) {
        free(h->key);
        free(h);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        h->status[i] = Empty;
    }
    return h;
}

int hash(int x, int p) {
    return x % p;
}

int isFull(HT h) {
    return h->remains == 0;
}

int insertX(int x, HT h) {
    if (isFull(h)) return 0;
    int pos = hash(x, h->size);
    while (h->status[pos] == Active) {
        pos = (pos+1)%h->size;
    }

    h->key[pos] = x;
    h->status[pos] = Active;
    h->remains--;
    return 1;
}

void printHT(const HT h) {
    for (int i = 0; i < h->size; i++) {
        printf("%4d", i);
    }
    putchar('\n');

    for (int i = 0; i < h->size; i++) {
        if (h->status[i] == Active) {
            printf("%4d", h->key[i]);
        } else if (h->status[i] == Removed) {
            printf("   X");;
        } else {
            printf("   -");
        }
    }
    putchar('\n');
}

int main() {
    HT h = initHashTable(11);
    insertX(5, h);
    insertX(16, h);
    insertX(10, h);
    insertX(21, h);
    insertX(33, h);
    printHT(h);
    return 0;
}
