#ifndef __STOKENIZER_H_INCLUDED__
#define __STOKENIZER_H_INCLUDED__
#include <iostream>
#include "token.h"
#include <vector>
#include <map>
class STokenizer{
private:
    std::string block; //the block
    int pos; //the position in the block
//    std::vector<std::string> charList; //our list instead of vector //List of char sets?
    std::map<Type,std::string> charList;
    void createSets(std::map<Type,std::string> sets); //sets the charList to these char sets
    bool isType(char ch, std::string set);
public:
    STokenizer():block(""),pos(0){createSets(tokenSet);}
    STokenizer(const std::string s):block(s),pos(0){createSets(tokenSet);}
//    friend STokenizer& operator >>(STokenizer& st, std::string& token);
//    Type tokenType(char ch);
//    std::string getThisToken(std::string charSet);
//    std::string setString(const std::string s);
//    std::string nextString();
//    Token nextToken();
//    bool fail();
//    bool more();
//    int getPos();
    Token nextToken(); //Grabs the next token in the block
    bool setBlock(std::string newBlock); //Sets a new block
    bool moreInBlock(); //Checks if there are more chars in the block
    int getPos(); //Gets the position of cursor in the block
    Type tokenType(char ch); //Gets the type of the char
    bool isKnown(char ch); //Checks if the char is of a known type
    void setUnknown(char ch); //Puts the char into the unknown char set
    std::string getToken(std::string charSet);  //Gets the next token of this type (i.e. will check the next char of this type
        //and will substr until the char of a different type)
};

#endif // STOKENIZER_H

/*
 * STokenizer Responsibilities:
 * Have or Take in character sets
 * Constructors: Default, Block argument
 * Get next token from block
 * Set a new block
 * Check if the block ends
 * Set the position in the block
 * Check the charset of the token
 * Check if the token is known or unknown
 * Get a specific token type from block (Like ZORG)
 */
