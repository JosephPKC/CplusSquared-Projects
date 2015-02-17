#include <iostream>
#include <binarytree.h>
using namespace std;

int main()
{
    BinaryTree<int> BT;
    cout << "The size of the tree: " << BT.size() << endl;
    cout << "Adding to left and right" << endl;
    BT.addLeft(1);
    cout << BT << endl;
    BT.shiftLeft();
    cout << BT << endl;
    BT.addLeft(3);
    cout << BT << endl;
    BT.addRight(4);
    cout << BT << endl;
    BT.shiftLeft();
    cout << BT << endl;
    BT.addRight(17);
    cout << BT << endl;
    BT.shiftToRoot();
    cout << BT << endl;
    BT.addRight(3);
    cout << BT << endl;
    cout << "Retrieving ROot: " << BT.retrive() << endl;

    return 0;
}


