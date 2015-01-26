#ifndef TOKEN_H
#define TOKEN_H
#include <string>
enum Type{
    SPACE = 0,
    END = 1,
    ALPHA = 2,
    NUM = 3,
    OP = 4,
    PUNC = 5,
    PAIR = 6,
    DEFAULT = -1

};

class Token{
private:
    std::string token;
    int type;
public:
    Token():token(NULL),type(0){}
    Token(std::string s, int t):token(s),type(t){}
    Token(char ch, int t):type(t){token += ch;}
    friend std::ostream& operator <<(std::ostream& out, const Token& T);
    int& getType();
    std::string& getToken();
};

#endif // TOKEN_H
