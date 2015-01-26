#ifndef STOKENIZER_H
#define STOKENIZER_H
#include "token.h"
#include <vector>
class STokenizer{
private:
    std::string str;
    int pos;
    std::vector<std::string> charList; //our list instead of vector
public:
    STokenizer();
    STokenizer(const std::string s);
    friend STokenizer& operator >>(STokenizer& st, std::string& token);
    int tokenType(char ch);
    std::string getThisToken(std::string charSet);
    std::string setString(const std::string s);
    std::string nextString();
    Token nextToken();
    bool fail();
    bool more();
    int getPos();
};

#endif // STOKENIZER_H
