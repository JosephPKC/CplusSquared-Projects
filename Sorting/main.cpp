#include <iostream>
#include <InsertionSorter.h>
#include <MergeSorter.h>
using namespace std;

void testInsertion(){
    InsertionSorter<int> I;
    I.insert(5);
    I.insert(2);
    I.insert(7);
    I.insert(6);
    I.insert(3);
    I.insert(10);
    I.insert(8);
    I.insert(1);
    I.insert(5);
    I.insert(5);
    I.insert(5);
    I.insert(5);
    cout << "This is the list now: " << endl;
    cout << I << endl;
    I.sort();
    cout << "Just sorted: " << endl;
    cout << I << endl;
}
void testMerge(){
    MergeSorter<int> I;
    I.insert(5);
    I.insert(2);
    I.insert(7);
    I.insert(6);
    I.insert(3);
    I.insert(10);
    I.insert(8);
    I.insert(1);
    I.insert(5);
    I.insert(5);
    I.insert(5);
    I.insert(5);
    cout << "This is the list now: " << endl;
    cout << I << endl;
    I.sort();
    cout << "Just sorted: " << endl;
    cout << I << endl;
}

int main()
{
    testInsertion();
    testMerge();
    return 0;
}

