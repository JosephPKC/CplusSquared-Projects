#include "token.h"

std::ostream& operator <<(std::ostream& out, const Token& T){
    out << T.token;
    return out;
}

Type &Token::getType(){
    return type;
}

std::string& Token::getToken(){
    return token;
}
