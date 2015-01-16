#include <iostream>
#include "ListTools.h"
using namespace std;
int main()
{
    srand(time(NULL));
    Node<int>* head = NULL;
    for(int i = 0; i <= 10; i++) insertHead(head,i);
    selectionSort(head);
    print(head);
    insertSorted(head,6);
    print(head);
    insertSorted(head,0);
    print(head);
    insertSorted(head,-1);
    print(head);
    insertSorted(head,150);
    print(head);

    return 0;
}

