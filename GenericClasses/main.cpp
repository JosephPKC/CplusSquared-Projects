#include <iostream>
#include "Frequency.h"
#include "Map.h"
using namespace std;

void testFrequency();
void testMap();

int main()
{
    testFrequency();
    testMap();
    return 0;
}

void testFrequency(){
    Frequency<char> Fs;
    string tester = "aababcabcdabcdeabcdef"; //6 a's, 1 f;
    for(int i = 0; i < tester.size(); i++) Fs.insert(tester[i]);
    cout << "Fs: " << Fs << endl;

    Frequency<char> Ft(Fs);
    Ft.insert('a');
    cout << "Ft: " << Ft << endl;

    cout << (Ft.empty()?"Ft is empty.WHICH IS WRONG.":"Ft is not empty.") << endl;
    cout << "Size of Ft: " << Ft.size() << endl;
    Ft.erase('e');
    cout << "Ft: " << Ft << endl;

    cout << "Ft[2]: " << Ft[2] << endl;
}

void testMap(){
    Map<char,int> Ms;
    string tester = "aababcabcdabcdeabcdef"; //a @ 0, b @ 2, c @ 5, d @ 9, e @ 14, f @ 20
    for(int i = 0; i < tester.size(); i++) Ms.insert(tester[i],i);
    cout << "Ms: " << Ms << endl;

    Map<char,int> Mt(Ms);
    Mt.insert('a',33333);
    cout << "Mt: " << Mt << endl;

    cout << (Mt.empty()?"Nt is empty.WHICH IS WRONG.":"Mt is not empty.") << endl;
    cout << "Size of Mt: " << Mt.size() << endl;
    Mt.erase('e');
    cout << "Mt: " << Mt << endl;

    cout << "Mt['a']: " << Mt['a'] << endl;
}
