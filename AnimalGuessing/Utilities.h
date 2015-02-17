#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <ctype.h>
using namespace std;
void eatLine(){
    char next;
    do cin.get(next);
    while(next != '\n');
}

bool inquire(const char query[]){
    char ans;
    do{
        cout << query << " Y/N" << endl;
        cin >> ans;
        ans = toupper(ans);
        eatLine();
    }while((ans != 'Y') && (ans != 'N'));
    return (ans == 'Y');
}

#endif // UTILITIES_H
