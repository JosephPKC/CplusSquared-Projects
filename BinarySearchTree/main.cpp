#include <iostream>
#include "BinaryTree.h"
using namespace std;

void insert(TreeNode<int>* root, int element);
void remove(TreeNode<int>* root, int element);
TreeNode<int>* search(TreeNode<int>* root, int element);
void print(TreeNode<int>* root);

struct Printer{
    void operator ()(TreeNode<int> tn){
        cout << tn << " ";
    }
};

//If its greater than root, go right
//If its less than root, go left
int main()
{
    TreeNode<int>* root = new TreeNode<int>;
    insert(root,1);
    insert(root,2);
    insert(root,-1);
    insert(root,0);
    cout << "The tree: " << endl;
    print(root);
    cout << endl;
//    remove(root,0);
//    print(root,0);
    cout << *search(root,2) << endl;
    return 0;
}

void insert(TreeNode<int>* root, int element){
//    if(root->isLeaf()){
//        if(element >= root->data())
//            root->setRight(new TreeNode<int>(element));
//        else if(element < root->data())
//            root->setLeft(new TreeNode<int>(element));
//    }
    if(element >= root->data()){
        if(!root->right()) root->setRight(new TreeNode<int>(element));
        else insert(root->right(),element);
    }
    else if(element < root->data()){
        if(!root->left()) root->setLeft(new TreeNode<int>(element));
        else insert(root->left(),element);
    }

}

void remove(TreeNode<int>* root, int element){
    //Find the first instance of that element
    //Find the left child of that element
    //Find the rightmost child of that child
    //swap the child with the element
    //delete the element (post-swap)
}

TreeNode<int>* search(TreeNode<int>* root, int element){
    if(element == root->data()) return root;
    if(!root) return NULL;
    if(element > root->data()){
        return search(root->right(),element);
    }
    else if(element < root->data()){
        return search(root->left(),element);
    }
}

void print(TreeNode<int>* root){
    inOrder(Printer(),root);
}
