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

template <typename A>
A* createSpace(A* a, size_t& size, int pos, int space){
    int newSize = size + space + 1;
    A* newA = new A[newSize];
    for(int i = 0; i < pos; i++)
        newA[i] = a[i];
    for(int i = pos; i < size; i++)
        newA[i + space] = a[i];
    for(int i = pos; i < pos + space; i++)
        newA[i] = A();
    size = newSize;
    return newA;
}

#endif // UTILITIES_H
