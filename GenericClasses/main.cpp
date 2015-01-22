#include <iostream>
#include "Frequency.h"
using namespace std;

int main()
{
    Frequency<int> F;
    F.insert(5);
    cout << F << endl;
    return 0;
}

