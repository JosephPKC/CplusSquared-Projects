#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "BinaryTreeTools.h"
//The only difference between a binary search tree and a regular binary tree is how we insert and delete
//So perhaps we may be able to just create a generic binary tree and have a template condition for how we insert
//Ex: for BST, the condition is if less than root, then left; else right
template <typename Item, typename OrderC = Lesser<Item> >
class BinarySearchTree{
    //Add GetSmallest and GetLargest Functions
    //Add Successor Function
private:
    TreeNode<Item>* _root;
    OrderC _Order;
    TreeNode<Item>* getRightMost(TreeNode<Item> *root);
    TreeNode<Item>* getParent(TreeNode<Item> *root, TreeNode<Item>* branch);
    void insert(TreeNode<Item>* root, const Item& element);
    void remove(TreeNode<Item> *&root, const Item& element);
    TreeNode<Item>* search(TreeNode<Item>* root, const Item& element);
public:
    //Constructors & The Big Three
    BinarySearchTree();
    BinarySearchTree(const Item& rootItem);
    BinarySearchTree(TreeNode<Item>* root);
    BinarySearchTree(const BinarySearchTree<Item,OrderC>& Other);
    BinarySearchTree<Item,OrderC>& operator =(const BinarySearchTree<Item,OrderC>& Other);
    ~BinarySearchTree();

    //Important Functions: Insert, Delete, Search, Print
    void insertT(const Item& element);
    void removeT(const Item& element);
    TreeNode<Item>* searchT(const Item& element);
    void print();
//    //Inorder, Postorder, Preorder Traversals
//    template <typename Process>
//    void BinarySearchTree<Item,OrderC>::traverseIn(Process P){
//        inOrder(P,_root);
//    }

//    template <typename Process>
//    voidBinarySearchTree<Item,OrderC>::traversePre(Process P){
//        preOrder(P,_root);
//    }

//    template <typename Process>
//    void BinarySearchTree<Item,OrderC>::traversePost(Process P){
//        postOrder(P,_root);
//    }
    //Misc Functions
    std::size_t sizeT() const;

};
template <typename Item, typename OrderC>
TreeNode<Item>* BinarySearchTree<Item,OrderC>::getRightMost(TreeNode<Item> *root){
    if(!root) return NULL; //if the root is NULL or if the recursive hits a NULL
    if(!root->right()) return root; //if the root or the recursive has no more right children, then it is the rightmost
    getRightMost(root->right()); //recursive right
}

template <typename Item, typename OrderC> //Add OrderC argument and change the less/greater ifs to OrderC //TODO find a way to implement this
TreeNode<Item>* BinarySearchTree<Item,OrderC>::getParent(TreeNode<Item> *root, TreeNode<Item>* branch){
    if(root) std::cout << "Root in gp: " << *root << std::endl;
    else std::cout << "Root in gp: NULL" << std::endl;
    if(branch) std::cout << "Branch in gp: " << *branch << std::endl;
    else std::cout << "Branch in gp: NULL" << std::endl;
    if(root->right()) std::cout << "Root->Right in gp: " << *root->right() << std::endl;
    else std::cout << "Root->Right in gp: NULL" << std::endl;
    if(root->left()) std::cout << "Root->Left in gp: " << *root->left() << std::endl;
    else std::cout << "Root->Left in gp: NULL" << std::endl;
    std::cout << "Branch == Root->Child: " << (branch == root->right()?"Yes":"No") << std::endl;
    std::cout << "Branch == Root: " << (branch == root?"Yes":"No") << std::endl;
    if(!root) return NULL; //If the root is NULL or if recursive hits NULL
    if(branch == root) return NULL; //If the branch is the root, then it has no parent
    if(branch == root->right() || branch == root->left()){ //If the branch is the child of the 'root' then the 'root' is the parent
        std::cout << "FOUND PARENT" << std::endl;
        return root;
    }
    std::cout << "In between" << std::endl;
    if(branch->data() >  root->data()){ //If the branch is greater than the root, dig into the right

         TreeNode<Item>* p = getParent(root->right(),branch);
         if(p) std::cout << "Parent in gp: " << *p << std::endl;
         else std::cout << "Parent in gp: NULL" << std::endl;
         return p;
    }
    else if(branch->data() < root->data()) //else dig into the left
        return getParent(root->left(),branch);
}
template <typename Item, typename OrderC>
void BinarySearchTree<Item,OrderC>::insert(TreeNode<Item>* root, const Item& element){
    std::cout << "In insert" << std::endl;
    std::cout << (root != NULL?"Not Null":"Null") << std::endl;
    if(!root) return;
    if(element >= root->data()){
        std::cout << "Right" << std::endl;
        if(!root->right()) root->setRight(new TreeNode<Item>(element));
        else insert(root->right(),element);
    }
    else if(element < root->data()){
        std::cout << "Left" << std::endl;
        if(!root->left()) root->setLeft(new TreeNode<Item>(element));
        else insert(root->left(),element);
    }

}
template <typename Item, typename OrderC>
void BinarySearchTree<Item,OrderC>::remove(TreeNode<Item>*& root, const Item& element){
    TreeNode<Item>* found = search(root,element);
    if(!found) return;
    if(found->isLeaf()){
        std::cout << "In is leaf" << std::endl;
        TreeNode<Item>* parent = getParent(root,found);
        if(!parent){ //If it has no parent, then it is the root
            std::cout << "Parent is nULL as leaf" << std::endl;
            delete found;
            std::cout << "after delete found" << std::endl;
            root = NULL;
            std::cout << "after root = NULL" << std::endl;
            return;
        }
        if(found->data() >= parent->data()) parent->setRight(NULL);
        else if(found->data() < parent->data()) parent->setLeft(NULL);
        delete found;
        return;
    }
    std::cout << "after isleaf" << std::endl;
    TreeNode<Item>* leftChild = found->left();
    if(!leftChild){
        TreeNode<Item>* parent = getParent(root,found);
//        std::cout << "Left Child: " << *leftChild << std::endl;
//        std::cout << "Right Most Child: " << *rightMost << std::endl;
        if(found) std::cout << "Found: " << *found << std::endl;
        else std::cout << "Found: NULL" << std::endl;
        if(parent) std::cout << "Parent: " << *parent << std::endl;
        else std::cout << "Parent: NULL" << std::endl;
        if(!parent) { //If it has no parent, then it is the root
            root = root->right();
            delete found;
        }
        else{
            std::cout << "Found Right: " << *found->right() << std::endl;
            std::cout << "FOund: " << *found << std::endl;
            parent->setRight(found->right());
            std::cout << "The parent linking: " << *parent << std::endl;
            delete found; //causes crash
        }
    }
    else{
        TreeNode<Item>* rightMost = getRightMost(leftChild); //right child should be null
        if(rightMost == leftChild){
            swap(found->data(),rightMost->data());
            found->setLeft(rightMost->left());
            delete rightMost;
        }
        else{
            std::cout << "Left Child: " << *leftChild << std::endl;
            std::cout << "Right Most Child: " << *rightMost << std::endl;
            std::cout << "Found: " << *found << std::endl;
            TreeNode<Item>* parent = getParent(root,rightMost);
            if(!parent){ //Then for some reason, the rightmost child of the left child of the found node is the root WHICH SHOULD NOT BE POSSIBLE
                std::cout << "Someone messed up" << std::endl;
            }
            else{
                swap(found->data(),rightMost->data());
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

template <typename Item, typename OrderC>
TreeNode<Item>* BinarySearchTree<Item,OrderC>::search(TreeNode<Item>* root, const Item& element){
    if(!root) return NULL;
    if(element == root->data()) return root;
    if(element > root->data()){
        return search(root->right(),element);
    }
    else if(element < root->data()){
        return search(root->left(),element);
    }
    return NULL;
}
//Constructors & The Big Three
template <typename Item, typename OrderC>
BinarySearchTree<Item,OrderC>::BinarySearchTree(){
    _root = NULL; //Here just set all private variables to a default state
    _Order = OrderC();
}

template <typename Item, typename OrderC>
BinarySearchTree<Item,OrderC>::BinarySearchTree(const Item& rootItem):BinarySearchTree(){
    _root = new TreeNode<Item>(rootItem);
}

template <typename Item, typename OrderC>
BinarySearchTree<Item,OrderC>::BinarySearchTree(TreeNode<Item>* root):BinarySearchTree(){
    _root = root;
}

template <typename Item, typename OrderC>
BinarySearchTree<Item,OrderC>::BinarySearchTree(const BinarySearchTree<Item,OrderC>& Other){
    _root = copy(Other._root);
    _Order = Other._Order;
}

template <typename Item, typename OrderC>
BinarySearchTree<Item,OrderC>& BinarySearchTree<Item,OrderC>::operator =(const BinarySearchTree<Item,OrderC>& Other){
    clear(_root);
    _root = copy(Other._root);
    _Order = Other._Order;
    return *this;
}

template <typename Item, typename OrderC>
BinarySearchTree<Item,OrderC>::~BinarySearchTree(){
    clear(_root);
}

//Important Functions: Insert, Delete, Search, Print
template <typename Item, typename OrderC>
void BinarySearchTree<Item,OrderC>::insertT(const Item& element){
    insert(_root,element);
}

template <typename Item, typename OrderC>
void BinarySearchTree<Item,OrderC>::removeT(const Item& element){
    remove(_root,element);
}

template <typename Item, typename OrderC>
TreeNode<Item>* BinarySearchTree<Item,OrderC>::searchT(const Item& element){
    return search(_root,element);
}

template <typename Item, typename OrderC>
void BinarySearchTree<Item,OrderC>::print(){
//    inOrder(Printer<Item>(),_root);
    if(!_root){
        std::cout << "Empty" << std::endl;
        return;
    }
    std::cout << *_root << std::endl;
}

//Misc Functions
template <typename Item, typename OrderC>
std::size_t BinarySearchTree<Item,OrderC>::sizeT() const{
    return size(_root);
}

#endif // BINARYSEARCHTREE_H
