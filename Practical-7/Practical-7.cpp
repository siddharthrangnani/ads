#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class MaxHeapLinkedList {
private:
    Node* head;

public:
    MaxHeapLinkedList() {
        head = nullptr;
    }

    void insert(int data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* curr = head;
            Node* prev = nullptr;

            while (curr != nullptr && curr->data > data) {
                prev = curr;
                curr = curr->next;
            }

            if (prev == nullptr) {
                newNode->next = head;
                head = newNode;
            } else {
                prev->next = newNode;
                newNode->next = curr;
            }
        }
    }

    int extractMax() {
        if (head == nullptr) {
            throw runtime_error("Heap is empty");
        }

        int max = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return max;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

int main() {
    MaxHeapLinkedList heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(15);
    heap.insert(5);

    while (!heap.isEmpty()) {
        cout << heap.extractMax() << " ";
    }
    cout << endl;

    return 0;
}
