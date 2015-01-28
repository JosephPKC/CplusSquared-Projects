#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <map>
enum Type{
    DEFAULT = -2,
    UNKNOWN = -1,
    END = 0,
    SPACE = 1,
    ALPHA = 2,
    NUM = 3,
    PUNC = 4,
    OP = 5,
    PAIR = 6, //?
    HIGHER = 7,
    LOWER = 8,
    LEFT = 9,
    RIGHT = 10
};

static const std::map<Type,std::string> tokenSet = {
    {UNKNOWN,""},
    {END,"\n"},
    {SPACE," \t"},
    {ALPHA,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {NUM,"0123456789"},
    {PUNC,"_;:\'\",./?\\!@#$%^&~`|"},
    {OP,"-+=*/<>"},
    {PAIR,"{}[]()"}
};
static const std::map<Type,std::string> expSet = {
    {UNKNOWN,""},
    {SPACE," \t"},
    {ALPHA,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {NUM,"0123456789"},
    {HIGHER,"*/"},
    {LOWER,"+-"},
    {LEFT,"("},
    {RIGHT,")"}
};


class Token{
private:
    std::string token;
    Type type;
public:
    Token():token(NULL),type(DEFAULT){}
    Token(std::string s, Type t):token(s),type(t){}
    Token(char ch, Type t):type(t){token += ch;}
    friend std::ostream& operator <<(std::ostream& out, const Token& T);
    Type& getType();
    std::string& getToken();
};

#endif // TOKEN_H
