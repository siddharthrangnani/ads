#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val){
        this->data = val;
        this->right = NULL;
        this->left = NULL;
    }
};
//
////Node* createNode(int data){
////    Node *node = new Node();
////    node->height = 1;
////    node->left = node->right = NULL;
////    node->val = data;
////
////    return node;
////}
//

int height(Node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int diff(Node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}


Node* rr_rotation(Node *parent)
{
    Node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

Node* ll_rotation(Node *parent)
{
    Node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

Node* lr_rotation(Node *parent)
{
    Node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}

Node* rl_rotation(Node *parent)
{
    Node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}

Node* balance(Node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}

Node* insertNode(Node *root, int value)
{
    if (root == NULL)
    {
        root = new Node(value);
        return root;
    }
    else if (value < root->data)
    {
        root->left = insertNode(root->left, value);
        root = balance (root);
    }
    else if (value >= root->data)
    {
        root->right = insertNode(root->right, value);
        root = balance (root);
    }
    return root;
}



Node* minVal(Node* node){
    Node* temp = node;
    if(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

Node* deleteNode(Node* root, int data){
    if(root == NULL){
        return root;
    }

    if(root->data == data){

        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        }

        if(root->left == NULL && root->right != NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        }

        if(root->left != NULL && root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }

        if(root->left!= NULL && root->right != NULL){
            int mini = minVal(root->right)->data;
            root->data = mini;

            root->right = deleteNode(root->right,mini);
            return root;
        }

    }
    else if(root->data > data){
        root->left = deleteNode(root->left, data);
        return root;
    }
    else{
        root->right = deleteNode(root->right,data);
        return root;
    }

}

void traverse(Node *root){
    if(root != NULL){
        traverse(root->left);
        cout<< root->data << " ";
        traverse(root->right);
    }
}

void display(Node* root, Node* ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(root, ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
            cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<"["<<ptr->data<<", "<<height(ptr)<<"]";
        display(root, ptr->left, level + 1);
    }
}


int main(){
    freopen("input.txt", "r", stdin);


    Node *root = NULL;
    int x;
    for (int i = 1; i < 11;++i){
        cin >> x;
        root = insertNode(root,x);
    }
    cout<<"Before: \n";
    traverse(root);
    display(root, root,1);

    cout<<"\nAfter: \n";
    deleteNode(root,1);

    traverse(root);
    display(root, root,1);

    return 0;
}
