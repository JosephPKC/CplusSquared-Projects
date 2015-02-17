#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <map>
enum Type{ //type enum for tokens
    ERROR = -1,
    DEFAULT = 0,
    UNKNOWN = -2,
    END = 1,
    SPACE = 2,
    ALPHA = 3,
    NUM = 4,
    PUNC = 5,
    OP = 6,
    PAIR = 7, //?
    HIGHER = 8,
    LOWER = 9,
    LEFT = 10,
    RIGHT = 11,
    VALID = 12
};
//General token set
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
//Expression Set
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
//Token Set ignoring white space and endlines
static const std::map<Type,std::string> noSpaceSet = {
    {UNKNOWN,""},
    {ALPHA,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {NUM,"0123456789"},
    {PUNC,"_;:\'\",./?\\!@#$%^&~`|-+=*/<>{}[]()"},
};
//Token set only for words and numbers
static const std::map<Type,std::string> wordSet = {
    {UNKNOWN,""},
    {ALPHA,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {NUM,"0123456789"}
};
//The default set or empty set
static const std::map<Type,std::string> defaultSet = {
    {UNKNOWN,""}
};
class Token{
private:
    std::string token; //the token name
    Type type; //the token type
public:
    Token():token(""),type(DEFAULT){}
    Token(std::string s, Type t):token(s),type(t){}
    Token(char ch, Type t):type(t){token += ch;}
    friend std::ostream& operator <<(std::ostream& out, const Token& T);
    Type getType(); //gets the type of token
    std::string getToken() const; //gets the name of token
    friend bool operator <(const Token& ls, const Token& rs);
    friend bool operator >(const Token& ls, const Token& rs);
    friend bool operator ==(const Token& ls, const Token& rs);
};

#endif // TOKEN_H
