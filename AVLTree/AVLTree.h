#ifndef AVLTREE_H
#define AVLTREE_H
#include "BinaryTreeTools.h"
template <typename Item>
class AVLTree{
private:
    TreeNode<Item>* _root; //private variable root

    /**
     * @brief rotateLeft : rotates the subtree left
     * @param problemTree : the problem subtree
     */
    void rotateLeft(TreeNode<Item>*& problemTree){
        TreeNode<Item>* hChild = heaviestChild(problemTree); //get the heaviest child
        TreeNode<Item>* p = parent(_root,problemTree); //get the parent of the problem tree
        if(p){ //If its not the root
            if(p->right() == problemTree) //Find which child the problem tree is
                p->setRight(hChild); //set the heaviest child
            else if(p->left() == problemTree)
                p->setLeft(hChild);
        }
        else //The problem tree is the root
            _root = hChild;
        problemTree->setRight(hChild->left()); //Steal the left child of heaviest
        hChild->setLeft(problemTree); //Push problem tree down
    }

    /**
     * @brief rotateRight : rotates the subtree right
     * @param problemTree : the problem subtree
     */
    void rotateRight(TreeNode<Item>*& problemTree){ //Follows the same procedure as rotateleft
        TreeNode<Item>* hChild = heaviestChild(problemTree); //except left is right, etc.
        TreeNode<Item>* p = parent(_root,problemTree);
        if(p){
            if(p->right() == problemTree)
                p->setRight(hChild);
            else if(p->left() == problemTree)
                p->setLeft(hChild);
        }
        else //The problem tree is the root
            _root = hChild;
        problemTree->setLeft(hChild->right());
        hChild->setRight(problemTree);
    }

    /**
     * @brief getWeight : Calculates the weight of a tree
     * @param tree : the tree in question
     * @return  : the weight of the tree
     */
    int getWeight(TreeNode<Item>* tree) const{ //Recursive
        if(!tree) return -1; //if its null then its weight is -1
        int leftWeight = getWeight(tree->left());
        int rightWeight = getWeight(tree->right());
        return (1 + bst::max(leftWeight,rightWeight)); //weight is 1 + weight of heaviest child
    }

    /**
     * @brief isBalanced : Checks if a tree is balaneced (the weight difference of its children is 0 or 1)
     * @param tree : the tree to check
     * @return  : True if the tree is balanced, false if the tree is not balanced
     */
    bool isBalanced(TreeNode<Item>* tree) const{
        int weight = abs(getWeight(tree->left()) - getWeight(tree->right())); //asbolute difference
        return ((weight == 1) || (weight == 0)); //The difference must be 0 or 1
    }

    /**
     * @brief problem : Gets the closest problem subtree of the tree passed in
     * @param tree : The tree to check for problems
     * @return : A problem subtree, or nullptr if there is none
     */
    TreeNode<Item>* problem(TreeNode<Item>* tree) const{ //Recursive
        if(!tree) return nullptr; //it is null
        if(!isBalanced(tree)) return tree; //if this tree is unbalanced
        TreeNode<Item>* left = problem(tree->left());
        if(left) return left; //if its at left
        TreeNode<Item>* right = problem(tree->right());
        if(right) return right; //if its at right
        return nullptr; //if not then null
    }

    /**
     * @brief heaviestChild : Gets the heaviest child of the tree
     * @param tree : the tree to get the heaviest child from
     * @return : the heaviest child, if they are both equal then it gets the right child by default
     */
    TreeNode<Item>* heaviestChild(TreeNode<Item>* tree) const{ //Note: it only gets immediate children
        if(getWeight(tree->left()) > getWeight(tree->right())) //compare the childrens' weights
            return tree->left();
        return tree->right(); //The default child
    }

    /**
     * @brief balance : balances the tree
     * @param tree : the tree to begin balancing
     */
    void balance(TreeNode<Item>* tree){
        TreeNode<Item>* pTree = problem(tree); //get the problem tree

        if(!pTree) return; //there is none
        TreeNode<Item>* hChild = heaviestChild(tree); //heaviest child
        TreeNode<Item>* hGrand = heaviestChild(hChild); //heaviest child of the heaviest child

        if(hChild == pTree->left()){//Left Case
            if(hGrand == hChild->right()) //Left-Right Case
                rotateLeft(hChild); //Straighten it out
            rotateRight(pTree); //Left-Left Case
        }
        else if(hChild == pTree->right()){ //Right Case
            if(hGrand == hChild->left()) //Right-Left Case
                rotateRight(hChild); //Straighten it out
            rotateLeft(pTree); //Right-Right Case
        }
    }

    /**
     * @brief insert : insert an entry into the given root
     * @param root : the root of the tree
     * @param entry : the entry to add
     */
    void insert(TreeNode<Item>* root, const Item& entry){ //Recursively finds the appropriate place to insert
        if(!root) return; //if root is null
        if(entry >= root->data()){ //go down to the right if its greater
            if(!root->right()) root->setRight(new TreeNode<Item>(entry)); //insert at the very end
            else insert(root->right(),entry);
        }
        else if(entry < root->data()){ //go down to the left if its less
            if(!root->left()) root->setLeft(new TreeNode<Item>(entry)); //insert at the very end
            else insert(root->left(),entry);
        }
    }

    /**
     * @brief remove : remove an entry from the given root
     * @param root : the root of the tree
     * @param element : the element to remove
     */
    void remove(TreeNode<Item>*& root, const Item& element){
        TreeNode<Item>* found = search(root,element); //Find the element
        if(!found) return; //If it didn't find the element
        if(found->isLeaf()){ //if its a leaf, simply remove the node
            TreeNode<Item>* p = parent(root,found); //Find the parent
            if(!p){ //If it has no parent, then it is the root
                delete found;
                root = nullptr;
                return;
            }
            //If it has a parent
            if(found->data() >= p->data()) p->setRight(nullptr);
            else if(found->data() < p->data()) p->setLeft(nullptr);
            delete found;
            return; //Stop here
        }
        TreeNode<Item>* leftChild = found->left(); //Get the left child
        if(!leftChild){ //if it has no left child
            TreeNode<Item>* p = parent(root,found); //Get the parent
            if(!p) { //If it has no parent, then it is the root
                root = root->right();
                delete found;
            }
            else{
                p->setRight(found->right());
                delete found;
            }
        }
        else{ //if it has a left child
            TreeNode<Item>* rightMost = getRightMost(leftChild); //right child should be null
            if(rightMost == leftChild){ //If the right most child IS the left child
                bst::swap(found->data(),rightMost->data()); //swap found with left child
                found->setLeft(rightMost->left());
                delete rightMost;
            }
            else{
                TreeNode<Item>* p = parent(root,rightMost);
                if(!p){ //Then for some reason, the rightmost child of the left child of the found node is the root WHICH SHOULD NOT BE POSSIBLE
                    std::cout << "Someone messed up" << std::endl;
                }
                else{
                    bst::swap(found->data(),rightMost->data()); //swap found with right most
                    p->setRight(rightMost->left());
                    delete rightMost;
                }
            }
        }
    }

    /**
     * @brief search : search the root for the target
     * @param root : the root of the tree
     * @param target : the target to search for
     * @return  : the pointer to the target in the tree or nullptr if it cannot be found
     */
    TreeNode<Item>* search(TreeNode<Item>* root, const Item& target) const{
        if(!root) return nullptr; //if its null
        if(target == root->data()) return root; //if its equal
        if(target > root->data()) //go right if greater
            return search(root->right(),target);
        else if(target < root->data()) //go left if less
            return search(root->left(),target);
        return nullptr;
    }

    /**
     * @brief findMax : find the node with the largest value in the tree
     * @param root : the root of the tree
     * @return : the pointer to the largest value or nullptr if the tree is empty
     */
    TreeNode<Item>* findMax(TreeNode<Item>* root) const{
        if(!root) return nullptr; //null
        TreeNode<Item>* max = root;
        TreeNode<Item>* right = findMax(root->right()); //go find the rightmost element
        if(!right) return max;//if its null, then return what was max previously
        if(right->data() > max->data()) max = right; //If its greater, then replace max
        return max;
    }

    /**
     * @brief findMin : find the smallest value
     * @param root : the root of the tree
     * @return : pointer to the smallest value or nullptr
     */
    TreeNode<Item>* findMin(TreeNode<Item>* root) const{
        if(!root) return nullptr; //Follows the same procedure as findmax
        TreeNode<Item>* min = root;
        TreeNode<Item>* left = findMin(root->left());
        if(left && (left->data() > min->data()))
            min = left;
        return min;
    }

    /**
     * @brief parent : Get the parent of the branch in the tree
     * @param tree : the tree
     * @param branch : the child
     * @return  : the pointer to the parent or nullptr if the tree is empty or if the branch is the root
     */
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

    /**
     * @brief getRightMost : Get the rightmost child
     * @param root : the root or tree
     * @return : the rightmost child or nullptr if the tree is empty
     */
    TreeNode<Item>* getRightMost(TreeNode<Item> *root){
        if(!root) return NULL; //if the root is NULL or if the recursive hits a NULL
        if(!root->right()) return root; //if the root or the recursive has no more right children, then it is the rightmost
        getRightMost(root->right()); //recursive right
    }

    /**
     * @brief insertRoot : insert an element directly to the root (initial insert)
     * @param entry : the entry
     */
    void insertRoot(const Item& entry){
        _root = new TreeNode<Item>(entry);
    }

    /**
     * @brief isUnique : checks if an item is unique
     * @param entry : the item to check
     * @return  : True if it is unique, False otherwise
     */
    bool isUnique(const Item& entry){
        return !searchT(entry); //If it cannot find the entry, then it is unique
    }

public:
    //default constructor
    AVLTree(TreeNode<Item>* root = nullptr):_root(root){}

    //copy constructor
    AVLTree(const AVLTree<Item>& Source){
        _root = copy(Source._root);
    }

    //assignment operator
    AVLTree<Item>& operator =(const AVLTree<Item>& Source){
        clearT();
        _root = copy(Source._root);
        return *this;
    }

    //destructor
    ~AVLTree(){
        clearT();
    }

    /**
     * @brief insertT : insert an entry
     * @param entry : the entry
     */
    void insertT(const Item& entry){
        if(!isUnique(entry)) return; //Only insert unique elements
        if(empty()){ //If its empty, then use the initial insert
            insertRoot(entry);
            return;
        }
        insert(_root,entry); //Inser the element
        while(!isBalanced(_root))balance(_root); //Balance the element
    }

    /**
     * @brief deleteT : delete an entry
     * @param target : the entry
     */
    void deleteT(const Item& target){
        remove(_root,target); //remove the element (Checks if the target is not found)
        while(!isBalanced(_root)) balance(_root); //Balance
    }

    /**
     * @brief searchT : search for target
     * @param target : the target
     * @return  : the pointer to the target or nullptr for not found
     */
    TreeNode<Item>* searchT(const Item& target) const{
        return search(_root,target); //Checks for empty
    }

    /**
     * @brief clearT : clear the tree
     */
    void clearT(){
        clear(_root);
    }

    template <typename Process>
    /**
     * @brief in : inorder generic traversal
     * @param P : the process
     */
    void in(Process P){
        inOrder(P,_root);
    }

    template <typename Process>
    /**
     * @brief pre : preorder generic traversal
     * @param P : the process
     */
    void pre(Process P){
        preOrder(P,_root);
    }

    template <typename Process>
    /**
     * @brief post : postorder generic traversal
     * @param P
     */
    void post(Process P){
        postOrder(P,_root);
    }

    /**
     * @brief max : get the max value
     * @return :the pointer or null
     */
    TreeNode<Item>* max() const{
        return findMax(_root);
    }

    /**
     * @brief min : get the min value
     * @return  : the pointer or null
     */
    TreeNode<Item>* min() const{
        return findMin(_root);
    }

    /**
     * @brief successor : Get the successor of here
     * @param here : the node to find the successor of
     * @return  : the successor or nullptr if here is a leaf
     */
    TreeNode<Item>* successor(TreeNode<Item>* here) const{ //smallest number that is larger than here
        if(here->isLeaf()) return nullptr;
        return findMin(here->right());
    }

    /**
     * @brief predecessor : get the predecessor of here
     * @param here : the node to find the predecessor of
     * @return  : the predecessor or nullptr if here is a leaf
     */
    TreeNode<Item>* predecessor(TreeNode<Item>* here) const{ //largest number that is smaller than here
        if(here->isLeaf()) return nullptr;
        return findMax(here->left());
    }

    /**
     * @brief empty : checks if the tree is empty
     * @return  : True if the tree is empty, False otherwise
     */
    bool empty() const{
        return (_root == nullptr);
    }

    template <typename Type>
    /**
     * @brief operator << : output
     * @param out : the output stream
     * @param Source : the object to output
     * @return : the output stream to chain
     */
    friend std::ostream& operator <<(std::ostream& out, const AVLTree<Type>& Source){
        print(Source._root,10); //Prints the root with depth multiplier of 10 (to space things out)
        return out;
    }
};

#endif // AVLTREE_H


//Below ia unfinished test code
//        if(!root) return;
//        TreeNode<Item>* p = parent(_root,root);
//        if(!p){ //is THE root
//            if(_root->isLeaf()) delete _root;
//            else if(((_root->hasLeft()) && !(_root->hasRight())) || //One child
//                    (!(_root->hasLeft()) && (_root->hasRight()))){
//                TreeNode<Item>* oC = _root->left();
//                if(!oC) oC = _root->right();
//                _root->setLeft(nullptr);
//                _root->setRight(nullptr);
//                delete _root;
//                _root = oC;
//            }
//            else if(_root->hasLeft() && _root->hasRight()){
//                TreeNode<Item>* suc = successor(_root);
//                suc->
//                _root->setLeft(nullptr);
//                _root->setRight(nullptr);
//                delete _root;
//                _root = suc;
//            }
//        }
//        if(root->isLeaf()){
//            if(p->left() == root) p->setLeft(nullptr);
//            else p->setRight(nullptr);
//            delete root;
//        }
//        else if(((root->hasLeft()) && !(root->hasRight())) || //One child
//                (!(root->hasLeft()) && (root->hasRight()))){
//            //get only child of root
//            TreeNode<Item>* oC = root->left();
//            if(!oC) oC = root->right();

//            if(p->left() == root) p->setLeft(oC);
//            else p->setRight(oC);
//            root->setLeft(nullptr);
//            root->setRight(nullptr);
//            delete root;
//        }
//        else if(root->hasLeft() && root->hasRight()){
//            TreeNode<Item>* suc = successor(root);
//            suc->setLeft(root->left());
//            if(p->left() == root) p->setLeft(suc);
//            else p->setRight(suc);
//            TreeNode<Item>* pSuc = parent(_root,suc);
//            if(pSuc->left() == suc) pSuc->setLeft(nullptr);
//            else pSuc->setRight(nullptr);
//            root->setLeft(nullptr);
//            root->setRight(nullptr);
//            delete root;
//        }
