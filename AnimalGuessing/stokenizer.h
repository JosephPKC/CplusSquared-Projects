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
    std::map<Type,std::string> charList; //the list of character sets
    bool isType(char ch, std::string set); //Checks if the string is of type set
    Type tokenType(char ch); //Gets the type of the char
    bool isKnown(char ch); //Checks if the char is of a known type
    void setUnknown(char ch); //Puts the char into the unknown char set
    std::string getToken(std::string charSet);  //Gets the next token of this type (i.e. will check the next char of this type
        //and will substr until the char of a different type)
public:
    STokenizer():block(""),pos(0){createSets(defaultSet);}
    STokenizer(const std::string s):block(s),pos(0){createSets(defaultSet);}
    Token nextToken(); //Grabs the next token in the block
    void setBlock(std::string newBlock); //Sets a new block
    bool moreInBlock(); //Checks if there are more chars in the block
    int getPos(); //Gets the position of cursor in the block
    void setPos(int i){pos = i;} //sets the position in the block
    std::string getBlock(){return block;} //returns the block
    void createSets(std::map<Type,std::string> sets); //sets the charList to these char sets
};
#endif // STOKENIZER_H
