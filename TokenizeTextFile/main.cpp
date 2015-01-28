#include <iostream>
#include "ftokenizer.h"
#include "Frequency.h"
using namespace std;

int main()
{
//    const string FILE_NAME = "file.txt";
//    FTokenizer F(FILE_NAME);
//    Token H = F.nextToken();
//    Frequency<Token> tFreq;
//    while(F.isMore()){
//        cout << H << endl;
//        H = F.nextToken();
//        tFreq.insert(H);
//    }
//    cout << tFreq << endl;
    string s = " άλφα";
    STokenizer S(s);
    Token T;
    while(S.moreInBlock()){
        T = S.nextToken();
        if(T.getType() == VOID) cout << "None" << endl;
        else cout << T << endl;
        cin.get();
    }



    return 0;
}

