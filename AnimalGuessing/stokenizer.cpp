#include "stokenizer.h"
/**
 * @brief STokenizer::nextToken gets the next token
 * @return a valid token or an error token
 */
Token STokenizer::nextToken(){
    if(!moreInBlock()) return Token("",ERROR); //If no more in block
    while(!isKnown(block[pos])){ //If its known, it will skip this while
        pos++; //This loop is to skip over unknown characters
        if(!moreInBlock()) return Token("",ERROR); //If there are no more valid characters
    } //By now the character at block[pos] should be known
    Type tType = tokenType(block[pos]); //Get the type of the character
    std::string tName = getToken(charList.at(tType)); //Grab the token of that type
    Token token(tName,tType); //Create a token
    return token;
}
/**
 * @brief STokenizer::setBlock sets the block
 * @param newBlock the new block
 */
void STokenizer::setBlock(std::string newBlock){
    pos = 0; //reset the position
    block = newBlock; //set the block
    for(int i = 0; i < block.length(); i++) //Collect all unknowns in the block
        if(!isKnown(block[i])) setUnknown(block[i]);
}
/**
 * @brief STokenizer::moreInBlock checks if there is more in the block
 * @return compares the position with the length of the block
 */
bool STokenizer::moreInBlock(){
    return pos < block.length();
}
/**
 * @brief STokenizer::getPos gets the position
 * @return the position
 */
int STokenizer::getPos(){
    return pos;
}
/**
 * @brief STokenizer::tokenType gets the token type of the character
 * @param ch the character
 * @return the type or unknown
 */
Type STokenizer::tokenType(char ch){
    for(const auto& it : charList) //Go through each item in the dictionary
        //This requires c++11 for range based for and auto var type
        if(isType(ch,it.second)) return it.first;
    return UNKNOWN;
}
/**
 * @brief STokenizer::isKnown checks if the char is known
 * @param ch the character
 * @return if its known or not (Known means it can be found in the dictionary)
 */
bool STokenizer::isKnown(char ch){
    return tokenType(ch) != UNKNOWN;
}
/**
 * @brief STokenizer::setUnknown adds the char to unknown list
 * @param ch the character
 */
void STokenizer::setUnknown(char ch){ //Assumes the character is unknown
    charList[UNKNOWN] += ch;
}
/**
 * @brief STokenizer::getToken gets the next token of charset type
 * @param charSet the set
 * @return the name of the token
 */
std::string STokenizer::getToken(std::string charSet){
    int bPos = pos; //set a temporary pos mark
    int end = block.find_first_not_of(charSet,pos+1); //grab the end pos
    if(end == -1){ //if end is -1, or if the block ended before finding a char not of set
        pos = block.length(); //then just substring to the end of the block
        return block.substr(bPos);
    }
    pos = end; //update the pos
    return block.substr(bPos,end-bPos);
}
/**
 * @brief STokenizer::createSets set the dictionary
 * @param sets the dictionary
 */
void STokenizer::createSets(std::map<Type,std::string> sets){
    charList = sets;
}
/**
 * @brief STokenizer::isType checks the typing
 * @param ch the character
 * @param set the type it may be
 * @return if ch is of set type
 */
bool STokenizer::isType(char ch, std::string set){
    return set.find(ch) != -1;
}
