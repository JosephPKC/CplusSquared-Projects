#include <iostream>
#include "BinarySearchTree.h"
#include "Heap.h"
#include "BTree.h"
using namespace std;

int main()
{
    BinarySearchTree<int> BST(3);
    BST.print();
    cout << "Inserting 5 into BST:" << endl;
    BST.insertT(5);
    cout << "Inserting 7 into BST:" << endl;
    BST.insertT(7);
    cout << "Inserting 3 into BST:" << endl;
    BST.insertT(3);
    cout << "Inserting 1 into BST:" << endl;
    BST.insertT(1);
    cout << "Inserting 4 into BST:" << endl;
    BST.insertT(4);
    cout << "Inserting 8 into BST:" << endl;
    BST.insertT(8);
    BST.print();
    cout << "Size: " << BST.sizeT() << endl;
    cout << "Removing 10" << endl;
    BST.removeT(10);
    BST.print();
    cout << "Removing 5" << endl;
    BST.removeT(5);
    BST.print();
    cout << "Removing 3" << endl;
    BST.removeT(3);
    BST.print();
    cout << "Removing 7" << endl;
    BST.removeT(7);
    BST.print();
    cout << "Removing 4" << endl;
    BST.removeT(4);
    BST.print();
    cout << "Removing 8" << endl;
    BST.removeT(8);
    BST.print();
    cout << "Removing 1" << endl;
    BST.removeT(1);
    BST.print();
    cout << "Removing 3" << endl;
    BST.removeT(3);
    BST.print();
    cout << "Removing 0" << endl;
    BST.removeT(0);
    BST.print();
    std::cout << "Size: " << BST.sizeT() << std::endl;


    Heap<int> H;
    cout << "Removing 0" << endl;
    H.remove(0);
    H.print();
    cout << "Insert 0" << endl;
    H.insert(0);
    H.print();
    cout << "Insert 5" << endl;
    H.insert(5);
    H.print();
    cout << "Insert 3" << endl;
    H.insert(3);
    H.print();
    cout << "Insert 5" << endl;
    H.insert(5);
    H.print();
    cout << "Insert 3" << endl;
    H.insert(3);
    H.print();
    cout << "Insert 4" << endl;
    H.insert(4);
    H.print();
    cout << "Insert 2" << endl;
    H.insert(2);
    H.print();
    cout << "Insert 1" << endl;
    H.insert(1);
    H.print();
    cout << "Insert 0" << endl;
    H.insert(0);
    H.print();
    cout << "Remove 0" << endl;
    H.remove(0);
    H.print();
    cout << "Remove 0" << endl;
    H.remove(0);
    H.print();
    cout << "Insert 0" << endl;
    H.insert(0);
    H.print();


    Set<int> S;
    cout << "Insert 0" << endl;
    S.insert(0);
    cout << S << endl;
    cout << "Insert 0" << endl;
    S.insert(0);
    cout << S << endl;
    cout << "Insert 1" << endl;
    S.insert(1);
    cout << S << endl;
    cout << "Insert 3" << endl;
    S.insert(3);
    cout << S << endl;
    cout << "Insert 5" << endl;
    S.insert(5);
    cout << S << endl;
    cout << "Insert 7" << endl;
    S.insert(7);
    cout << S << endl;
    cout << "Insert 9" << endl;
    S.insert(9);
    cout << S << endl;
    cout << "Insert 8" << endl;
    S.insert(8);
    cout << S << endl;
    cout << "Remove 0" << endl;
    S.erase(0);
    cout << S << endl;
    cout << "Remove 5" << endl;
    S.erase(5);
    cout << S << endl;
    cout << "Remove 8" << endl;
    S.erase(8);
    cout << S << endl;
    cout << "Remove 1" << endl;
    S.erase(1);
    cout << S << endl;
    cout << "Remove 7" << endl;
    S.erase(7);
    cout << S << endl;
    cout << "Remove 3" << endl;
    S.erase(3);
    cout << S << endl;
    cout << "Remove 9" << endl;
    S.erase(9);
    cout << S << endl;
    cout << "Remove 10" << endl;
    S.erase(10);
    cout << S << endl;
    for(int i = 0; i < 15; i++){
        S.insert(i);
        cout << S << endl;
    }
    for(int i = 0; i < 15; i++){
        S.erase(i);
        cout << "Erase: " << i << ": " << S << endl;
//        cin.get();
    }
    return 0;


}

