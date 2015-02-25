#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main()
{
    BinarySearchTree<int> BST(3);
    BST.print();
    cout << "Inserting 5 into BST:" << endl;
    BST.insertT(5);
    BST.insertT(7);
    BST.insertT(3);
    BST.insertT(1);
    BST.insertT(4);
    BST.insertT(8);
    BST.print();
    BST.removeT(5);
    BST.print();
    BST.removeT(3);
    BST.print();
    BST.removeT(7);
//    BST.print();
    return 0;
}

