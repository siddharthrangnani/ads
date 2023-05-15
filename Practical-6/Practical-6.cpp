#include <bits/stdc++.h>
using namespace std;

struct Node {
    int sum;
    int left, right;
    Node* left_child;
    Node* right_child;
};

Node* buildSegmentTree(vector<int>& nums, int left, int right) {
    Node* node = new Node();
    node->left = left;
    node->right = right;

    if (left == right) {
        node->sum = nums[left];
        node->left_child = nullptr;
        node->right_child = nullptr;
    } else {
        int mid = left + (right - left) / 2;
        node->left_child = buildSegmentTree(nums, left, mid);
        node->right_child = buildSegmentTree(nums, mid + 1, right);
        node->sum = node->left_child->sum + node->right_child->sum;
    }

    return node;
}

int queryRangeSum(Node* node, int left, int right) {

    if (left <= node->left && right >= node->right) {
        return node->sum;
    }

    if (right < node->left || left > node->right) {
        return 0;
    }

    return queryRangeSum(node->left_child, left, right) + queryRangeSum(node->right_child, left, right);
}

int main() {

    vector<int> nums = {2,3,4,5,6,7,8, 9,10, 11};
    int n = nums.size();
    Node* root = buildSegmentTree(nums, 0, n - 1);
    int left = 2;
    int right = 6;
    int rangeSum = queryRangeSum(root, left, right);
    cout << "The sum of the numbers in the range [" << left << ", " << right << "] is " << rangeSum << endl;
    return 0;
}

