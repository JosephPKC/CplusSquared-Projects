#include <iostream>
#include "ftokenizer.h"
#include "Frequency.h"
#include <vector>
#include <iomanip>
using namespace std;
const int TOP = 200;
//Test stokenizer
void testSTokenizer();
void testSTfunction();
//program that will parse text file and print out the top 200 tokens
void frequencyOfText(map<Type,string> m);
int main(){
//    testSTokenizer();
//    testSTfunction();
    frequencyOfText(wordSet);//replace argument with tokenSet, expSet, noSpaceSet, wordSet
    return 0;
}

void testSTokenizer(){
    STokenizer S;
    string sa = "These are words: Hello World!; Thesre are numbers: 012345.";
    cout << "This is the string: \n" << sa << endl;
    S.setBlock(sa);
    S.createSets(tokenSet);
    cout << "Grabbing tokens using standard token set:" << endl;
    while(S.moreInBlock()) cout << S.nextToken() << "|";
    cout << endl;
    sa = " abc def 123! \n \t ab77 2;3;; f> \n";
    S.setBlock(sa);
    cout << "This is the next string:\n" << sa << endl;
    cout << "Grabbing tokens using standard token set:" << endl;
    while(S.moreInBlock()) cout << S.nextToken() << "|";
    cout << endl;
}

void testSTfunction(){
    STokenizer S;
    string s = "Deliverables: For every project, submit ALL SOURCE FILES (main.cpp, all header files, and other .cpp files) and a test file in text format. Projects with no test file will earn a score of zero. ";
    cout << "This is the string: \n" << s << endl;
    S.setBlock(s);
    S.createSets(tokenSet);
    cout << "This the block of S: \n" << S.getBlock() << endl;
    cout << (S.moreInBlock()?"There is more":"There is no more") << endl;
    cout << "Grabbing tokens using standard token set:" << endl;
    while(S.moreInBlock()) cout << S.nextToken() << "|";
    cout << endl;
}

void frequencyOfText(map<Type, string> m){
    Frequency<Token> tokenFreq;
    FTokenizer F("test.txt");
    F.setDictionary(m);

    Token T;
    if(!F.isFileSet()){
        cout << "File not Set!" << endl;
        exit(-1);
    }
    while(F.moreInFile()){
        T = F.nextToken();
        cout << T << "|";
        tokenFreq.insert(T);
//        cin.get();
    }
    cout << endl << endl;
    Frequency<Token> sorted = tokenFreq.sortByFreq();
    for(int i = 0; i < TOP && i < sorted.size(); i++){
        cout << setw(2) << i+1  << ": Type- " << sorted[i].getType() << setw(11) << " Freq- " << sorted.getFreqAt(sorted[i]) << setw(5) << " " << sorted[i].getToken() << endl;
    }
}
