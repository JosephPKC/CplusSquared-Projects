#include <iostream>
#include "BinaryTree.h"
using namespace std;

void insert(TreeNode<int>* root, int element);
void remove(TreeNode<int> *&root, int element);
TreeNode<int>* search(TreeNode<int>* root, int element);
void print(TreeNode<int>* root);
TreeNode<int>* getRightMost(TreeNode<int> *root);
TreeNode<int>* getParent(TreeNode<int> *root, TreeNode<int>* branch);


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
//    cout << *search(root,2) << endl;
//    cout << "Right most of root: " << *getRightMost(root) << endl;
    remove(root,3);
    print(root);
    cout << endl;
    remove(root,0);
    print(root);
    cout << endl;
    remove(root,-1);
    print(root);
//    cout << "The parent: " <<  *getParent(root,search(root,2)) << endl;
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

void remove(TreeNode<int>*& root, int element){
    //Find the first instance of that element
    //case 1: If element does not exist, then do nothing
    //case 2: If element exists, proceed:
    //Find the left child of that element
    //case 1: If the leftchild does not exist, then delete the element and set its parent to null
    //case 2: If the leftchild exists, proceed:
    //Find the rightmost child of that child
    //case 1: If the rightmost child is not the same as leftchild, then swap rightmost with element and delete element
    //case 2: If the rightmost child is the same as leftchild, then delete element and set its parent to leftchild
    TreeNode<int>* found = search(root,element);
    if(!found) return;
    if(found->isLeaf()){
        TreeNode<int>* parent = getParent(root,found);
        if(!parent){ //If it has no parent, then it is the root
            delete found;
            root = NULL;
            return;
        }
        if(found->data() >= parent->data()) parent->setRight(NULL);
        else if(found->data() < parent->data()) parent->setLeft(NULL);
        delete found;
    }
    TreeNode<int>* leftChild = found->left();
    if(!leftChild){
        TreeNode<int>* parent = getParent(root,found);
        if(!parent) { //If it has no parent, then it is the root
            root = root->right();
            delete found;
        }
        else{
            parent->setLeft(found->right());
            delete found;
        }
    }
    else{
        TreeNode<int>* rightMost = getRightMost(leftChild); //right child should be null
        if(rightMost == leftChild){
            swap(found->data(),rightMost->data());
            found->setLeft(rightMost->left());
            delete rightMost;
        }
        else{
            swap(found->data(),rightMost->data());
            TreeNode<int>* parent = getParent(root,rightMost);
            if(!parent){ //Then for some reason, the rightmost child of the left child of the found node is the root WHICH SHOULD NOT BE POSSIBLE
                cout << "Someone messed up" << endl;
            }
            else{
                parent->setRight(rightMost->left());
                delete rightMost;
            }
        }
    }
    //Search for node
    //If node does not exist, nothing. If it does proceed:
    //If node has no children, delete and set parent branch to null
    //If node has only one child, then set node parent branch to child and delete node
    //If node has two children, then ???

}

TreeNode<int>* getParent(TreeNode<int>* root, TreeNode<int>* branch){
    cout << "Branch: " << *branch << endl;
    if(!root) return NULL;
    cout << "Root: " << *root << endl;
    TreeNode<int>* r = root->right();
    TreeNode<int>* l = root->left();
    if(r) cout << "RC: " << *r << endl;
    else cout << "RC: NULL" << endl;
    if(l) cout << "LC: " << *l << endl;
    else cout  << "LC: NULL" << endl;
    cout << "&B: " << &branch << endl;
    cout << "&R: " << &r << endl;
    cout << "&L: " << &l << endl;
    if(branch == root) return NULL;
    if(branch == root->right() || branch == root->left()){
        cout << "We found the parent: " << *root << endl;
        return root;
    }
    cout << "Mid" << endl;
    cout << "Branch Data: " << branch->data() << endl;
    cout << "Root Data: " << root->data() << endl;
    if(branch->data() >  root->data()){
        cout << "Right" << endl;
        return getParent(root->right(),branch);
//        if(!getParent(root->right(),branch)){
//            cout << "Root -> Right: " << *root->right() << endl;
//            cout << *root << endl;
//            return root;
//        }
    }
    else if(branch->data() < root->data()){
        cout << "Left" << endl;
        return getParent(root->left(),branch);
//        if(!getParent(root->left(),branch)) return root;
    }

}

TreeNode<int>* getRightMost(TreeNode<int>* root){
    if(!root) return NULL;
    if(!root->right()) return root;
//    cout << "Current Root: " << *root << endl;
    getRightMost(root->right());


}

TreeNode<int>* search(TreeNode<int>* root, int element){
    cout << "Search element: " << element << endl;
    if(!root) return NULL;
    if(element == root->data()) return root;
    cout << "Search root: " << *root << endl;
    if(element > root->data()){
        return search(root->right(),element);
    }
    else if(element < root->data()){
        return search(root->left(),element);
    }
    return NULL;
}

void print(TreeNode<int>* root){
    inOrder(Printer(),root);
    cout << endl;
    cout << *root << endl;
}

template <typename Val>
void swap(Val& a, Val& b){
    Val temp(a);
    a = b;
    b = temp;
}
