#include <iostream>
#include "AVLTree.h"
using namespace std;

int main(){
    AVLTree<int> A;
    char input;
    int num;
    while(true){
        cout << "Enter: (I)nsert, (D)elete, or (S)earch" << endl;
        cin >> input;
        switch(input){
        case'i':
        case 'I':{
            cin >> num;
            A.insertT(num);
            break;
        }
        case'd':
        case 'D':{
            cin >> num;
            A.deleteT(num);
            break;
        }
        case's':
        case 'S':{
            cin >> num;
            if(A.searchT(num)) cout << "Found it" << endl;
            break;
        }
        case'x':
        case 'X':{
            exit(1);
            break;
        }
        default: break;
        }
        cout << A << endl;
    }

    return 0;
}

