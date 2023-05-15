#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* next;

    Node(int key) {
        this->key = key;
        this->next = nullptr;
    }
};

class HashTable {
private:
    vector<Node*> table;
    int size;
    int capacity;

    int hash(int key) {
        return key % capacity;
    }

public:

    HashTable(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->table.resize(capacity, nullptr);
    }


    void insert(int key) {
        int index = hash(key);

        Node* node = new Node(key);
        node->next = table[index];
        table[index] = node;

        size++;
    }

    void remove(int key) {
        int index = hash(key);

        Node* prev = nullptr;
        Node* curr = table[index];

        while (curr != nullptr && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) {
            return;
        }

        if (prev == nullptr) {
            table[index] = curr->next;
        } else {
            prev->next = curr->next;
        }

        delete curr;
        size--;
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << i << ": ";
            Node* curr = table[i];
            while (curr != nullptr) {
                cout << curr->key << " ";
                curr = curr->next;
            }
            cout << endl;
        }
    }

    bool contains(int key) {
        int index = hash(key);

        Node* curr = table[index];

        while (curr != nullptr) {
            if (curr->key == key) {
                return true;
            }
            curr = curr->next;
        }

        return false;
    }

    int getSize() {
        return size;
    }
};

int main() {
    HashTable table(10);

    table.insert(5);
    table.insert(15);
    table.insert(25);
    table.insert(35);
    table.insert(45);

    table.display();
    cout << endl;

    table.remove(15);

    table.display();
    cout << endl;

    cout << "Contains 25?= " << (table.contains(25) ? "Yes" : "No") << endl;
    cout << "Contains 15? " << (table.contains(15) ? "Yes" : "No") << endl;

    cout << "Size: " << table.getSize() << endl;

    return 0;
}
