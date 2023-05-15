/*
    Practical - 3
    Scapegoat

    1) create tree with N values and check condition
        height > log(3/2) N
        if condition is true rebalance the tree (go to step 3)

    2) Enter new key and check the condition at leaf node

    3) if the log(3/2)N condition is true at each level check below conditon
        (height-1) / height > (2/3)
        if the above condition is true rebalance the tree with inorder traversal
        if not than check for parent and again perform same condition
*/
#include<bits/stdc++.h>
using namespace std;
struct node{
    int key;
    node* left = NULL;
    node* right = NULL;
};

int log_a_to_base_b(int a, int b)
{
    return log2(a) / log2(b);
}

void find_inorder(node* root,vector<int> &inorder){
    if(root == NULL)
        return;
    find_inorder(root->left, inorder);
    inorder.push_back(root->key);
    find_inorder(root->right, inorder);
}

node* build_tree(int left, int right, vector<int> inorder){
    if(left > right)
        return NULL;

    int mid = (left+right)/2;

    node* new_node = new node();
    new_node->key = inorder[mid];
    new_node->left = build_tree(left, mid-1, inorder);
    new_node->right = build_tree(mid+1, right, inorder);
    return new_node;
}

//find right node for given key,
node* bal_node(node* cur_node, node* root, int no_of_nodes, int height, int &flag){
    //current node key(given key) is greter than root node
    if(cur_node->key > root->key){
        if(root->right == NULL){
            root->right = cur_node;
            if(height+1 > log_a_to_base_b(no_of_nodes, 3/2)){
                //if tree is inbalance than make flag=1, which find height from leaf to root
                flag = 1;
            }
        }else{
            root->right = bal_node(cur_node, root->right, no_of_nodes, height+1, flag);
            //if flag is -1 than tree is balanced otherwise check next condition
            if(flag != -1){
                flag++;
                //flag-1 height of child node, flag size is height of  current node
                //compare it with 2/3
                //if  condition is true find inorder from current and create new tree,
                //join it with parent
                if(((flag-1) / double(flag)) > 2/3){
                    vector<int> inorder;
                    find_inorder(root, inorder);
                    return build_tree(0, inorder.size()-1, inorder);

                }
            }
        }
    }else{
        //perform same thing as above
        if(root->left == NULL){
            root->left = cur_node;
            if(height+1 > log_a_to_base_b(no_of_nodes, 3/2)){
                flag = 1;
            }
        }else{
            root->left = bal_node(cur_node, root->left, no_of_nodes, height+1, flag);
            if(flag != -1){
                flag++;
                if(((flag-1) / double(flag)) > 2/3){
                    vector<int> inorder;
                    find_inorder(root, inorder);
                    return build_tree(0, inorder.size()-1, inorder);
                }
            }
        }
    }
    return root;
}
//create tree from input given in "input.txt"
node* inp(string filename, node* root, int &no_of_nodes){
    string str;
    ifstream filestream(filename);
    if (filestream.is_open())
    {
        while(getline(filestream,str))
        {
            node* new_node = new node();
            new_node->key = stoi(str);
            no_of_nodes++;
            if(root == NULL){
                root = new_node;
            }else{
                int flag = -1;
                bal_node(new_node, root, no_of_nodes, 0, flag);
            }
        }
        filestream.close();
  }
  return root;
}
// after basic building of tree, enter new key
node* insert_node(node* root, int key, int &no_of_nodes){
    //create new node
    node* new_node = new node();
    new_node->key = key;
    int flag = -1;//at leaf tree is balnced or inbalance base on that (2/3) condition is check
    no_of_nodes++;//increment it for finding log(3/2)no. of nodes
    return bal_node(new_node, root, no_of_nodes, 0, flag);
}
//show the tree
void show(node* root){
    if(root == NULL)
        return;

    show(root->left);
    cout << root->key <<" ";
    show(root->right);
}

void display(node* root, node* ptr, int level)
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
        cout<<ptr->key;
        display(root, ptr->left, level + 1);
    }
}

int main()
{
    string filename = "input.txt";
    node* root = NULL;
    int no_of_nodes = 0;

    //inital State
        root = inp(filename, root, no_of_nodes);
        cout << endl <<"Binary Search Tree :- " << endl;
        show(root);
        display(root,root,1);
        cout << endl;

        //insert node
        int choice = 1;
        int key = 10;
        while(choice == 1){
            cout << "Enter key :- " << endl;
            cin >> key;

            //create and add element in tree
            root = insert_node(root, key, no_of_nodes);
            show(root);
            display(root,root,1);
            cout << endl;

            cout << "Enter 1/0 :- ";
            cin >> choice;
        }
    return 0;
}
