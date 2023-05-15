// split at any point

#include <bits/stdc++.h>
using namespace std;

struct node {
    int key;
    int size;
    node *left, *right;
};

int getSize(node* n) {
    return n ? n->size : 0;
}

void updateSize(node* n) {
    if (n) {
        n->size = 1 + getSize(n->left) + getSize(n->right);
    }
}

pair<node*, node*> split(node* root, int i) {
    if (!root) return {nullptr, nullptr};
    int rootIndex = getSize(root->left) + 1;
    if (rootIndex <= i) {
        auto [left, right] = split(root->right, i - rootIndex);
        root->right = left;
        updateSize(root);
        return {root, right};
    } else {
        auto [left, right] = split(root->left, i);
        root->left = right;
        updateSize(root);
        return {left, root};
    }
}

pair<node*, node*> split(node* root, node* splitNode) {
    if (!root) return {nullptr, nullptr};
    if (root == splitNode) {
        node* right = root->right;
        root->right = nullptr;
        updateSize(root);
        return {root, right};
    } else if (splitNode->key < root->key) {
        auto [left, right] = split(root->left, splitNode);
        root->left = right;
        updateSize(root);
        return {left, root};
    } else {
        auto [left, right] = split(root->right, splitNode);
        root->right = left;
        updateSize(root);
        return {root, right};
    }
}

node* insert(node* root, int key) {
    if (!root) return new node({key, 1, nullptr, nullptr});
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    updateSize(root);
    return root;
}

void printInOrder(node* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->key << " ";
    printInOrder(root->right);
}

int main() {
    node* root = nullptr;

    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 30);
    root = insert(root, 35);

    cout << "Original tree: ";
    printInOrder(root);
    cout << endl;

    auto [left, right] = split(root, 1);

    cout << "Original tree: ";
    printInOrder(left);

    cout << endl;

    printInOrder(right);

    cout << endl;
    return 0;
}
