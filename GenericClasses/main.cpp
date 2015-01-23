#include <iostream>
#include "Frequency.h"
#include "Map.h"
using namespace std;

int main()
{
//    Frequency<int> F;
//    F.insert(5);
//    cout << F << endl;
    Map<int,float> M;
    M.insert(1,1.003f);
    M.insert(2,2.203f);
    M.insert(3,3.444f);
//    cout << *M.head << endl;
//    M.head = M.head->next;
//    cout << *M.head << endl;
//    M.head = M.head->next;
//    cout << *M.head << endl;
//    M.head = M.head->next;
//    if(M.head == NULL) cout << "Done" << endl;
    cout << M << endl;

    return 0;
}

