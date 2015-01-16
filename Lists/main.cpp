#include <iostream>
#include "ListTools.h"
using namespace std;

int main()
{
    Node<int> N(1);
    cout << N << endl;

    Node<int>* head = NULL;
    insertHead(head,21);
    insertHead(head,33);
    cout << *head << *(head->next) << endl;
    cout << "Hello World!" << endl;
    return 0;
}

