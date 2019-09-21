//
// Created by sxg on 2019/9/20.
//
#include<stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void init(struct Node** phead){
    *phead = NULL;
}

int getLength(struct Node* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

void printList(struct Node* head) {
    while (head) {
        printf("%d->", head->data);
        head = head->next;
    }
    putchar('\n');
}

struct Node* findKth(struct Node* head, int k) {
    int cnt = 1;
    struct Node* p;

    p = head;
    while (p && cnt < k) {
        p = p->next;
        cnt++;
    }
    return p;
}

struct Node* createNode(int x) {
    struct Node* t;
    t = (struct Node*)malloc(sizeof(struct Node));
    t->next = NULL;
    t->data = x;
    return t;
}

int insert(struct Node** phead, int k, int x) {
    if (k < 1) return 0;
    if (k == 1) {
        struct Node* t;
        t = createNode(x);
        t->next = *phead;
        *phead = t;
        return 1;
    } else {
        struct Node* p;
        p = findKth(*phead, k-1);
        if (p) {
            struct Node* t;
            t = createNode(x);
            t->next = p->next;
            p->next = t;
            return 1;
        } else {
            return 0;
        }
    }
}



int removeNode(struct Node** phead, int k, int *px) {
    if (k < 1) return  0;
    else if (k == 1) {
        if (*phead) {
            *px = (*phead)->data;
            *phead = (*phead)->next;
            return 1;
        } else {
            return 0;
        }
    } else {
        struct Node* p;
        p = findKth(*phead, k-1);
        if (p == NULL || p->next == NULL) {
            return 0;
        } else {
            struct Node* t;
            t = p->next;
            p->next = t->next;
            *px = t->data;
            free(t);
            return 1;
        }
    }
}

int main() {
    struct Node* head;

    init(&head);
    int k = getLength(head);
    insert(&head, 1, 11);
    insert(&head, 2, 22);
    insert(&head, 2, 33);
    insert(&head, 6, 44);
    printList(head);
    int x = 0;
    removeNode(&head, 4, &x);
    printf("%d\n", x);
    printList(head);

    return 0;
}

