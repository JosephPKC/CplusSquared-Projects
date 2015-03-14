#ifndef AVLTREE_H
#define AVLTREE_H
#include "BinaryTreeTools.h"
template <typename Item>
class AVLTree{
private:
    TreeNode<Item>* _root;

    void rotateLeft(TreeNode<Item>*& problemTree){
        TreeNode<Item>* hChild = heaviestChild(problemTree);
        TreeNode<Item>* p = parent(_root,problemTree);
        if(p){
            if(p->right() == problemTree)
                p->setRight(hChild);
            else if(p->left() == problemTree)
                p->setLeft(hChild);
            problemTree->setRight(hChild->left());
            hChild->setLeft(problemTree);
        }
        else{ //The problem tree is the root
            _root = hChild;
            problemTree->setRight(hChild->left());
            hChild->setLeft(problemTree);
        }
    }

    void rotateRight(TreeNode<Item>*& problemTree){
        TreeNode<Item>* hChild = heaviestChild(problemTree);
        TreeNode<Item>* p = parent(_root,problemTree);
        if(p){
            if(p->right() == problemTree)
                p->setRight(hChild);
            else if(p->left() == problemTree)
                p->setLeft(hChild);
            problemTree->setLeft(hChild->right());
            hChild->setRight(problemTree);
        }
        else{ //The problem tree is the root
            _root = hChild;
            problemTree->setLeft(hChild->right());
            hChild->setRight(problemTree);
        }
    }

    int getWeight(TreeNode<Item>* tree) const{
        if(!tree) return -1;
        int leftWeight = getWeight(tree->left());
        int rightWeight = getWeight(tree->right());
        return (1 + bst::max(leftWeight,rightWeight));
    }

    bool isBalanced(TreeNode<Item>* tree) const{
        int weight = abs(getWeight(tree->left()) - getWeight(tree->right()));
        return ((weight == 1) || (weight == 0));
    }

    TreeNode<Item>* problem(TreeNode<Item>* tree) const{
        if(!tree) return nullptr;
        if(!isBalanced(tree)) return tree;
        TreeNode<Item>* left = problem(tree->left());
        if(left) return left;
        TreeNode<Item>* right = problem(tree->right());
        if(right) return right;
        return nullptr;
    }

    TreeNode<Item>* heaviestChild(TreeNode<Item>* tree) const{
        if(getWeight(tree->left()) > getWeight(tree->right()))
            return tree->left();
        return tree->right();
    }

    void balance(TreeNode<Item>* tree){
        TreeNode<Item>* pTree = problem(tree);

        if(!pTree) return;
        TreeNode<Item>* hChild = heaviestChild(tree);
        TreeNode<Item>* hGrand = heaviestChild(hChild);

        if(hChild == pTree->left()){//Left Case
            if(hGrand == hChild->right()){ //Left-Right Case
                rotateLeft(hChild); //Straighten it out
            }
            rotateRight(pTree); //Left-Left Case
        }
        else if(hChild == pTree->right()){ //Right Case
            if(hGrand == hChild->left()) //Right-Left Case
                rotateRight(hChild); //Straighten it out
            rotateLeft(pTree); //Right-Right Case
        }
    }

    void insert(TreeNode<Item>* root, const Item& entry){
        if(!root) return;
        if(entry >= root->data()){
            if(!root->right()) root->setRight(new TreeNode<Item>(entry));
            else insert(root->right(),entry);
        }
        else if(entry < root->data()){
            if(!root->left()) root->setLeft(new TreeNode<Item>(entry));
            else insert(root->left(),entry);
        }
    }

    void remove(TreeNode<Item>* root){
        if(!root) return;
        TreeNode<Item>* p = parent(_root,root);
        if(!p){ //is THE root
            if(_root->isLeaf()) delete _root;
            else if(((_root->hasLeft()) && !(_root->hasRight())) || //One child
                    (!(_root->hasLeft()) && (_root->hasRight()))){
                TreeNode<Item>* oC = _root->left();
                if(!oC) oC = _root->right();
                _root->setLeft(nullptr);
                _root->setRight(nullptr);
                delete _root;
                _root = oC;
            }
            else if(_root->hasLeft() && _root->hasRight()){
                TreeNode<Item>* suc = successor(_root);
                suc->
                _root->setLeft(nullptr);
                _root->setRight(nullptr);
                delete _root;
                _root = suc;
            }
        }
        if(root->isLeaf()){
            if(p->left() == root) p->setLeft(nullptr);
            else p->setRight(nullptr);
            delete root;
        }
        else if(((root->hasLeft()) && !(root->hasRight())) || //One child
                (!(root->hasLeft()) && (root->hasRight()))){
            //get only child of root
            TreeNode<Item>* oC = root->left();
            if(!oC) oC = root->right();

            if(p->left() == root) p->setLeft(oC);
            else p->setRight(oC);
            root->setLeft(nullptr);
            root->setRight(nullptr);
            delete root;
        }
        else if(root->hasLeft() && root->hasRight()){
            TreeNode<Item>* suc = successor(root);
            suc->setLeft(root->left());
            if(p->left() == root) p->setLeft(suc);
            else p->setRight(suc);
            TreeNode<Item>* pSuc = parent(_root,suc);
            if(pSuc->left() == suc) pSuc->setLeft(nullptr);
            else pSuc->setRight(nullptr);
            root->setLeft(nullptr);
            root->setRight(nullptr);
            delete root;
        }
//        if(found->isLeaf()){ //if its a leaf
//            TreeNode<Item>* p = parent(root,found);
//            if(!p){ //If it has no parent, then it is the root
//                delete found;
//                root = nullptr;
//                return;
//            }
//            if(found->data() >= p->data()) p->setRight(nullptr);
//            else if(found->data() < p->data()) p->setLeft(nullptr);
//            delete found;
//            return;
//        }
//        TreeNode<Item>* leftChild = found->left();
//        if(!leftChild){ //if it has no left child
//            TreeNode<Item>* p = parent(root,found);
//            if(!p) { //If it has no parent, then it is the root
//                root = root->right();
//                delete found;
//            }
//            else{
//                p->setRight(found->right());
//                delete found; //causes crash
//            }
//        }
//        else{ //if it has a left child
//            TreeNode<Item>* rightMost = getRightMost(leftChild); //right child should be null
//            if(rightMost == leftChild){
//                bst::swap(found->data(),rightMost->data());
//                found->setLeft(rightMost->left());
//                delete rightMost;
//            }
//            else{
//                TreeNode<Item>* p = parent(root,rightMost);
//                if(!p){ //Then for some reason, the rightmost child of the left child of the found node is the root WHICH SHOULD NOT BE POSSIBLE
//                    std::cout << "Someone messed up" << std::endl;
//                }
//                else{
//                    bst::swap(found->data(),rightMost->data());
//                    p->setRight(rightMost->left());
//                    delete rightMost;
//                }
//            }
//        }
    }

    TreeNode<Item>* search(TreeNode<Item>* root, const Item& target) const{
        if(!root) return nullptr;
        if(target == root->data()) return root;
        if(target > root->data())
            return search(root->right(),target);
        else if(target < root->data())
            return search(root->left(),target);
        return nullptr;
    }

    TreeNode<Item>* findMax(TreeNode<Item>* root) const{
        if(!root) return nullptr;
        TreeNode<Item>* max = root;
        TreeNode<Item>* right = findMax(root->right());
        if(!right) return max;
        if(right->data() > max->data()) max = right;
        return max;
    }

    TreeNode<Item>* findMin(TreeNode<Item>* root) const{
        if(!root) return nullptr;
        TreeNode<Item>* min = root;
        TreeNode<Item>* left = findMin(root->left());
        if(left && (left->data() > min->data()))
            min = left;
        return min;
    }

    TreeNode<Item>* parent(TreeNode<Item>* tree, TreeNode<Item>* branch){
        if(!tree) return nullptr; //If the root is NULL or if recursive hits NULL
        if(branch == tree) return nullptr; //If the branch is the root, then it has no parent
        if(branch == tree->right() || branch == tree->left()) //If the branch is the child of the 'root' then the 'root' is the parent
            return tree;
        if(branch->data() >  tree->data()){ //If the branch is greater than the root, dig into the right
             TreeNode<Item>* p = parent(tree->right(),branch);
             return p;
        }
        else if(branch->data() < tree->data()) //else dig into the left
            return parent(tree->left(),branch);
    }

    TreeNode<Item>* getRightMost(TreeNode<Item> *root){
        if(!root) return NULL; //if the root is NULL or if the recursive hits a NULL
        if(!root->right()) return root; //if the root or the recursive has no more right children, then it is the rightmost
        getRightMost(root->right()); //recursive right
    }

    void insertRoot(const Item& entry){
        _root = new TreeNode<Item>(entry);
    }

    bool isUnique(const Item& entry){
        return !searchT(entry);
    }

public:
    AVLTree(TreeNode<Item>* root = nullptr):_root(root){}

    AVLTree(const AVLTree<Item>& Source){
        _root = copy(Source._root);
    }

    AVLTree<Item>& operator =(const AVLTree<Item>& Source){
        clearT();
        _root = copy(Source._root);
        return *this;
    }

    ~AVLTree(){
        clearT();
    }

    void insertT(const Item& entry){
        if(!isUnique(entry)) return;
        if(empty()){
            insertRoot(entry);
            return;
        }
        insert(_root,entry);
        balance(_root);
    }

    void deleteT(const Item& target){
        TreeNode<Item>* found = search(_root,target);
        if(!found) return;
        remove(found,target);
        balance(_root);
    }

    TreeNode<Item>* searchT(const Item& target) const{
        return search(_root,target);
    }

    void clearT(){
        clear(_root);
    }


    template <typename Process>
    void in(Process P){
        inOrder(P,_root);
    }

    template <typename Process>
    void pre(Process P){
        preOrder(P,_root);
    }

    template <typename Process>
    void post(Process P){
        postOrder(P,_root);
    }

    TreeNode<Item>* max() const{
        return findMax(_root);
    }

    TreeNode<Item>* min() const{
        return findMin(_root);
    }

    TreeNode<Item>* successor(TreeNode<Item>* here) const{ //smallest number that is larger than here
        if(here->isLeaf()) return nullptr;
        return findMin(here->right());
    }

    TreeNode<Item>* predecessor(TreeNode<Item>* here) const{ //largest number that is smaller than here
        if(here->isLeaf()) return nullptr;
        return findMax(here->left());
    }

    bool empty() const{
        return (_root == nullptr);
    }

    template <typename Type>
    friend std::ostream& operator <<(std::ostream& out, const AVLTree<Type>& Source){
        print(Source._root,10);
        return out;
    }
};

#endif // AVLTREE_H
