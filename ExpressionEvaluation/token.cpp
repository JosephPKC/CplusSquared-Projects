#include "token.h"
#include <iostream>
/**
 * @brief operator << insertion operator
 * @param out ostream
 * @param T the token
 * @return  ostream
 */
std::ostream& operator <<(std::ostream& out, const Token& T){
    out << T.getToken();
    return out;
}
/**
 * @brief Token::getType gets the type
 * @return type
 */
Type Token::getType(){
    return type;
}
/**
 * @brief Token::getToken gets the token
 * @return token
 */
std::string Token::getToken() const{
    return token;
}
//Comparison operators. They compare the token name not type
bool operator <(const Token& ls, const Token& rs){
    return ls.getToken() < rs.getToken();
}

bool operator >(const Token& ls, const Token& rs){
        return ls.getToken() > rs.getToken();
}

bool operator ==(const Token& ls, const Token& rs){
        return ls.getToken() == rs.getToken();
}
