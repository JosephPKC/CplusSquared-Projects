#include "ftokenizer.h"
#include <iostream>
FTokenizer::FTokenizer(std::string file):FTokenizer(){
    fileS.open(file);
    if(!fileS.is_open()) //f.std::ios::fail()
        fail = true; //The file failed to load
    fail = false;
}
/**
 * @brief FTokenizer::getNewBlock sets the block of stk
 * @return whether the setting succeeded or not
 */
bool FTokenizer::getNewBlock(){
    if(!moreInFile()) return false; //If there is no more in file
    char* block = new char[MAX_BLOCK + 1]; //Use char* for read()
    fileS.read(block,MAX_BLOCK); //read in MAX_BLOCK chars
    block[fileS.gcount()] = NULL; //Set a null character at the end
    std::string b = block; //Convert to string
    stk.setBlock(b); //set the block into stk
    delete[] block; //delete the char*
    return true; //succeeded
}
/**
 * @brief FTokenizer::setFile sets the file
 * @param file file name
 * @return whether it failed or not
 */
bool FTokenizer::setFile(std::string file){
    fileS.close(); //Close any previous files
    fileS.open(file); //Open the new file
    if(!fileS.is_open())
        fail = true;
    else fail = false;
    return !fail;
}
/**
 * @brief FTokenizer::isFileSet checks if the file is successfully opened
 * @return whether it failed or not
 */
bool FTokenizer::isFileSet(){
    return !fail;
}
/**
 * @brief FTokenizer::setDictionary set the dictionary of stk
 * @param set the dictionary set
 */
void FTokenizer::setDictionary(std::map<Type,std::string> set){
    stk.createSets(set);
}
/**
 * @brief FTokenizer::nextToken gets the next token
 * @return a valid token or an error token
 */
Token FTokenizer::nextToken(){
    if(!stk.moreInBlock()) //If no more in block
        if(!getNewBlock()) return Token("",ERROR); //And setting the block failed
    Token T = stk.nextToken();
    //This is to continuously ignore error tokens until a valid token appears
    //This is because of the way stk ignores unknown characters or invalid ones
    while(T.getType() == ERROR){ //If stk's nexttoken gives an error token
        if(!getNewBlock()) return Token("",ERROR); //and if setting the block failed
        T = stk.nextToken(); //grab the next token
    }
    //By now the token should be valid
    //This block is to combine tokens that may end up split due to block limits
    if(!stk.moreInBlock()){ //If there is no more in the block (meaning the token may have been split
        if(!getNewBlock()) return Token("",ERROR); //If no more in file
        Token S = stk.nextToken(); //Grab the very next token
        if(T.getType() == S.getType()) return Token(T.getToken() + S.getToken(),T.getType());
        //If the token types match, then the token was split, so combine them
        else stk.setPos(0); //If not just reset the position in the block
    }
    return T;
}
/**
 * @brief FTokenizer::moreInFile checks if there is more in the file, or more in the block
 * @return if there are more potential tokens
 */
bool FTokenizer::moreInFile(){
    more = !fileS.std::ios::eof();
    if(stk.moreInBlock()) return true;
    return more;
}
/**
 * @brief FTokenizer::getPos gets the position
 * @return the position
 */
int FTokenizer::getPos(){
    return pos;
}
