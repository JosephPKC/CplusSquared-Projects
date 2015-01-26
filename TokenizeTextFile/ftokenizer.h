#ifndef __FTOKENIZER_H_INCLUDED__
#define __FTOKENIZER_H_INCLUDED__

class STokenizer;

#include "stokenizer.h"
#include <fstream>
class FTokenizer{
private:
    std::ifstream f;
    STokenizer stk;
    int pos;
    bool more;
public:
    static const int MAX_BLOCK = 50;
    FTokenizer():stk(),pos(0),more(false){}
    FTokenizer(char* file);
    Token nextToken();
    bool getNewBlock();
    bool isMore();
    int getPos();
    int blockPos();

};

#endif // FTOKENIZER_H
