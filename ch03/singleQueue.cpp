//
// Created by sxg on 2019/9/21.
//
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    explicit Node(int x) {
        data = x;
        next = nullptr;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = rear = nullptr;
    }

    ~Queue() {
        Node *tmp;
        while (front) {
            tmp = front;
            front = front->next;
            delete tmp;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int x) {
        Node* tmp;
        tmp = new Node(x);

        // 空队列
        if (isEmpty()) {
            front = rear = tmp;
        } else { // 不空
            rear->next = tmp;
            rear = tmp;
        }
    }

    bool dequeue(int *px) {
        if (isEmpty()) return false;
        else {
            *px = front->data;
            Node* tmp;
            tmp = front;
            front = front->next;
            delete tmp;

            if (isEmpty()) {
                rear = nullptr;
            }
            return true;
        }
    }
};

int main() {
    Queue q;
    q.enqueue(11);
    q.enqueue(22);
    q.enqueue(33);
    q.enqueue(44);
    q.enqueue(55);

    int x = 0;
    q.dequeue(&x);
    cout << x << endl;

    q.dequeue(&x);
    cout << x << endl;

    q.dequeue(&x);
    cout << x << endl;

    q.dequeue(&x);
    cout << x << endl;

    q.dequeue(&x);
    cout << x << endl;

    q.dequeue(&x);
    cout << x << endl;
    return 0;

}
