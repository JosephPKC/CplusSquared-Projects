#ifndef BINARYTREETOOLS_H
#define BINARYTREETOOLS_H
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <iostream>

template <typename Item>
class TreeNode{
private:
    Item _data;
    TreeNode* _left;
    TreeNode* _right;
public:
    TreeNode(const Item& data = Item(), TreeNode* left = NULL, TreeNode* right = NULL){
        _data = data;
        _left = left;
        _right = right;
    }

    Item& data()        {return _data;}
    TreeNode* left()    {return _left;}
    TreeNode* right()   {return _right;}

    void setData(const Item& data)      {_data = data;}
    void setLeft(TreeNode* left)        {_left = left;}
    void setRight(TreeNode* right)      {_right = right;}

    const Item& data() const        {return _data;}
    const TreeNode* left() const    {return _left;}
    const TreeNode* right() const   {return _right;}
    bool isLeaf() const             {return (_left == NULL) && (_right == NULL);}

    bool hasLeft() const            {return _left;}
    bool hasRight() const           {return _right;}
    template <typename Other>
    friend std::ostream& operator <<(std::ostream& out, const TreeNode<Other>& T){

        out << T.data() << ":(";
        if(T.left()) out << *T.left() << "),(";
        if(T.right()) out << *T.right();
        out << ")";
        return out;
    }

};

template <typename Process, typename Node>
void inOrder(Process p, Node* ptr){
    if(ptr != NULL){
        inOrder(p,ptr->left()); //Go to the left branch
        p(ptr->data()); //Perform process on the data of the node
        inOrder(p,ptr->right()); //Go to the right branch
    }
}

template <typename Process, typename Node>
void preOrder(Process p, Node* ptr){
    if(ptr != NULL){
        p(ptr->data()); //Perform process on the data of the node
        preOrder(p,ptr->left()); //Go to the left branch
        preOrder(p,ptr->right()); //Go to the right branch
    }
}

template <typename Process, typename Node>
void postOrder(Process p, Node* ptr){
    if(ptr != NULL){
        postOrder(p,ptr->left()); //Go to the left branch
        postOrder(p,ptr->right()); //Go to the right branch
        p(ptr->data()); //Perform process on the data of the node
    }
}

template <typename Item, typename Size>
void print(TreeNode<Item>* root, Size depth){
    if(root != NULL){
        print(root->right(),depth + 5);
        for(int i = 0; i < depth; i++) std::cout << " ";
        std::cout << root->data(); /*<< "-"<< std::endl;*/
        for(int i = 0; i < depth; i++) std::cout << " ";
        std::cout << std::endl;
        print(root->left(),depth + 5);
    }
}

template <typename Item>
void clear(TreeNode<Item>*& root){
    TreeNode<Item>* branch;
    if(root != NULL){
        branch = root->left(); //Clear all of the left branches
        clear(branch);
        branch = root->right(); //Clear all of the right branches
        clear(branch);
        delete root; //Clear the root
        root = NULL;
    }
}

template <typename Item>
TreeNode<Item>* copy(const TreeNode<Item>* root){
    TreeNode<Item>* tLeft;
    TreeNode<Item>* tRight;
    if(root == NULL) return NULL; //If it goes past a leaf
    else{
        tLeft = copy(root->left()); //Copy all of the left
        tRight = copy(root->right()); //Copy all of the right
        return new TreeNode<Item>(root->data(),tLeft,tRight); //Create a node with the left and right
    }
}

template <typename Item>
std::size_t size(const TreeNode<Item>* root){
    if(root == NULL) return 0;
    else return 1 + size(root->left()) + size(root->right());
}

template <typename Item>
struct Lesser{
    bool operator ()(const Item& lhs, const Item& rhs){
        return lhs < rhs;
    }
};

template <typename Item>
struct Printer{
    void operator ()(const Item& tn){
        std::cout << tn << " ";
    }
};

template <typename Item>
struct Greq{
    bool operator ()(const Item& lhs, const Item& rhs){
        return lhs >= rhs;
    }
};

namespace bst{
    template <typename Val>
    void swap(Val& a, Val& b){
        Val temp(a);
        a = b;
        b = temp;
    }

    template <typename Type>
    void copy(const Type* source, Type* dest, std::size_t size){ //Does not check for size//Make sure it is valid and theres room beforehand
        for(int i = 0; i < size; i++){
            dest[i] = source[i];
        }
    }

    template <typename Type>
    void copy(Type* source, Type* dest, std::size_t size, int sPos, int ePos){ //Does not check for size//Make sure it is valid and theres room beforehand
        for(int i = sPos; i < size && i <= ePos; i++)
            dest[i - sPos] = source[i];
    }

    template <typename Item, typename Order>
    std::size_t firstCondOf(Item* a, std::size_t size, const Item& target, Order Ord){
        for(int i = 0; i < size; i++)
            if(Ord(a[i],target)) return i;
        return -1;
    }

    template <typename Item>
    void shiftRight(Item* a, std::size_t& size, int pos){
        for(int i = size - 1; i >= pos; i--){
            a[i + 1] = a[i];
        }
        size++;
    }

    template <typename Item>
    void shiftLeft(Item* a, std::size_t& size, int pos){
        for(int i = pos; i < size - 1; i++)
            a[i] = a[i + 1];
        size--;
    }

    template <typename Item, typename Process>
    void traverse(Item* a, std::size_t size, Process P){
        for(int i = 0; i < size; i++)
            P(a[i]);
    }

    template <typename Item>
    void merge(Item* a, Item* b, std::size_t& sizeA, std::size_t sizeB){
        for(int i = sizeA; i < sizeB; i++)
            a[i] = b[i - sizeA];
        sizeA += sizeB;
    }

    template <typename Item>
    Item max(const Item& a, const Item& b){
        Item m = a;
        if(b > m) m = b;
        return m;
    }
}
#endif // BINARYTREETOOLS_H
