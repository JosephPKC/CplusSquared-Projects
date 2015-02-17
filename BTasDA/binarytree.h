#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <cstdlib>
#include <iostream>
#include "TreeNode.h"
#include "Utilities.h"
using namespace std;
template <typename Item>
class BinaryTree{
private:
    static const int DEFAULT_SIZE = 1;
    size_t currentSize;
    bool* isPresent; //Last Resort use a map <int,bool> to hold the indices and true/false
    TreeNode<Item>* treeArray;
    int current;
    size_t actual;

    int leftIndex(int parentIndex) const;
    int rightIndex(int parentIndex) const;
    int parent(int childIndex) const;
    void createFirstNode(const Item& entry);
public:
    BinaryTree();
    BinaryTree(TreeNode<Item>* root);
    BinaryTree(const Item& rootEntry);
    BinaryTree(const BinaryTree<Item>& Source);
    BinaryTree<Item>& operator =(const BinaryTree<Item>& Source);
    ~BinaryTree();

    void shiftToRoot();
    void shiftUp();
    void shiftLeft();
    void shiftRight();
    void change(const Item& newEntry);
    void addLeft(const Item& entry);
    void addRight(const Item& entry);
    size_t size() const;
    Item retrive() const;
    bool hasParent() const;
    bool hasLeft() const;
    bool hasRight() const;

    friend std::ostream& operator <<(std::ostream& out, const BinaryTree<Item>& Source){
        for(int i = 0; i < Source.actual; i++){
            if(Source.isPresent[i]){
                if(i == Source.current) out << "[" << Source.treeArray[i] << "]";
                else out << Source.treeArray[i];
            }
            else
                out << "NULL";
            out  << " | ";
        }
        return out;
    }

};
//[Root,Left(0),Right(0),Left(1),Right(1),Left(1),Right(1)
//To get parent from child:
    //If even then Cindex - 2 / 2
    //If ood then Cindex - 1 / 2
//To get children from parent:
    //For left: Pindex * 2 + 1
    //For right: Pindex * 2 + 2

/* The responsibilities of Binary Tree
 * Constructors
 * Accessors for Root, Data, Left, and Right
 * Mutators for Root, Data, Left, and Right
 * Move the currentpointer
 * Know the root
 *
 * What the Binary Tree should know
 * size of the tree
 * Root
 * the entries (array of nodes)
 * the current node
 * if its complete or not
 *
 * What Node should know
 * Its content
 * the left and right
 * if its a leaf
 */
template <typename Item>
BinaryTree<Item>::BinaryTree(){
    createFirstNode(Item());
    shiftToRoot();
}

template <typename Item>
BinaryTree<Item>::BinaryTree(TreeNode<Item>* root) : BinaryTree(){
    isPresent[0] = true;
    treeArray[0] = *root;
}

template <typename Item>
BinaryTree<Item>::BinaryTree(const Item& rootEntry) : BinaryTree(){
    isPresent[0] = true;
    treeArray[0] = TreeNode<Item>(rootEntry);
}

template <typename Item>
BinaryTree<Item>::BinaryTree(const BinaryTree<Item>& Source) : BinaryTree(){
    if(isPresent) delete isPresent;
    if(treeArray) delete treeArray;
    isPresent = new bool[Source.actual];
    treeArray = new TreeNode<Item>[Source.actual];
    currentSize = Source.size();
    actual = Source.actual;
    for(int i = 0; i < Source.actual; i++){
        treeArray[i] = Source.treeArray[i];
        isPresent[i] = Source.isPresent[i];
    }
}

template <typename Item>
BinaryTree<Item>& BinaryTree<Item>::operator =(const BinaryTree<Item>& Source){
    if(isPresent) delete isPresent;
    if(treeArray) delete treeArray;
    isPresent = new bool[Source.actual];
    treeArray = new TreeNode<Item>[Source.actual];
    currentSize = Source.size();
    actual = Source.actual;
    for(int i = 0; i < Source.actual; i++){
        treeArray[i] = Source.treeArray[i];
        isPresent[i] = Source.isPresent[i];
    }
    return *this;
}
template <typename Item>
BinaryTree<Item>::~BinaryTree(){
    delete isPresent;
    delete treeArray;
}

template <typename Item>
void BinaryTree<Item>::createFirstNode(const Item& entry){
    isPresent = new bool[3];
    isPresent[0] = true;
    isPresent[1] = false;
    isPresent[2] = false;
    treeArray = new TreeNode<Item>[3];
    treeArray[0] = TreeNode<Item>(entry);
    treeArray[1] = Item();
    treeArray[2] = Item();
    currentSize = 1;
    actual = 3;
}

template <typename Item>
void BinaryTree<Item>::shiftToRoot(){
    current = 0;
}

template <typename Item>
void BinaryTree<Item>::shiftUp(){
    if((size() > 0) && (hasParent()))
        current = parent(current);
}

template <typename Item>
void BinaryTree<Item>::shiftLeft(){
    if((size() > 0) && (hasLeft()))
        current = leftIndex(current);
}

template <typename Item>
void BinaryTree<Item>::shiftRight(){
    if((size() > 0) && (hasRight()))
        current = rightIndex(current);
}

template <typename Item>
void BinaryTree<Item>::change(const Item& newEntry){
    treeArray[current] = newEntry;
}

//From the parent (current) find the location of left/right child, then set that to true
//Then set its children to false by extending the array
template <typename Item> //Assumes it is complete (As in it at least has a complete depth)
void BinaryTree<Item>::addLeft(const Item& entry){
    if((size() <= 0) || (hasLeft())) return;
    int index = leftIndex(current);
    if(index >= actual){ //If not in actual, then create new depth
        int numOfShifts = actual + 1;
            TreeNode<Item>* hold = createSpace(treeArray,actual,actual,numOfShifts);
            delete treeArray;
            treeArray = hold;
            actual -= numOfShifts + 1;
            bool* holdB = createSpace(isPresent,actual,actual,numOfShifts);
            delete isPresent;
            isPresent = holdB;
            for(int i = index; i < actual; i++)
                isPresent[i] = false;
    }
    treeArray[index] = TreeNode<Item>(entry);
    isPresent[index] = true;
    currentSize++;
}

template <typename Item>
void BinaryTree<Item>::addRight(const Item& entry){
    if((size() <= 0) || (hasRight())) return;
    int index = rightIndex(current);
    if(index >= actual){
        int numOfShifts = actual + 1;
            TreeNode<Item>* hold = createSpace(treeArray,actual,actual,numOfShifts);
            delete treeArray;
            treeArray = hold;
            actual -= numOfShifts + 1;
            bool* holdB = createSpace(isPresent,actual,actual,numOfShifts);
            delete isPresent;
            isPresent = holdB;
            for(int i = index; i < actual; i++)
                isPresent[i] = false;
    }
    treeArray[index] = TreeNode<Item>(entry);
    isPresent[index] = true;
    currentSize++;
}

template <typename Item>
size_t BinaryTree<Item>::size() const{
    return currentSize;
}

template <typename Item>
Item BinaryTree<Item>::retrive() const{
    return treeArray[current].data();
}

template <typename Item>
bool BinaryTree<Item>::hasParent() const{
    if(size() <= 0) return false;
    int index = parent(current);
    return ((index >= 0) && (index <actual) && (isPresent[index]));
}

template <typename Item>
bool BinaryTree<Item>::hasLeft() const{
    if(size() <= 0) return false;
    int index = leftIndex(current);
    return ((index >= 0) && (index < actual) && (isPresent[index]));
}

template <typename Item>
bool BinaryTree<Item>::hasRight() const{
    if(size() <= 0) return false;
    int index = rightIndex(current);
    return ((index >= 0) && (index < actual) && (isPresent[index]));
}

template <typename Item>
int BinaryTree<Item>::leftIndex(int parentIndex) const{
    return parentIndex * 2 + 1;
}

template <typename Item>
int BinaryTree<Item>::rightIndex(int parentIndex) const{
    return parentIndex * 2 + 2;
}

template <typename Item>
int BinaryTree<Item>::parent(int childIndex) const{
    return ((childIndex % 2 == 0) ?
                ((childIndex - 2) / 2) :
                ((childIndex - 1) / 2));
}



#endif // BINARYTREE_H
