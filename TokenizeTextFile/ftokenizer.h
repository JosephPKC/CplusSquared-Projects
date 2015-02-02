#ifndef __FTOKENIZER_H_INCLUDED__
#define __FTOKENIZER_H_INCLUDED__

class STokenizer;

#include "stokenizer.h"
#include <fstream>
class FTokenizer{
private:
    std::ifstream fileS; //file stream
    STokenizer stk; //string tokenizer
    int pos; //position in the file
    bool more; //If there are more chars after the pos in the file
    bool fail; //If the file failed to open
    bool getNewBlock(); //Loads a new block into stk
public:
    static const int MAX_BLOCK = 50; //Size of the block
    FTokenizer():stk(),pos(0),more(false),fail(true){}
    FTokenizer(std::string file);
    bool setFile(std::string file); //Sets the file
    Token nextToken(); //Grabs the next token in the file
    bool moreInFile(); //Checks if there is more in the file
    int getPos(); //Gets the position
    bool isFileSet(); //Checks if the file is set
    void setDictionary(std::map<Type,std::string> set); //Sets stk's dictionary
};

#endif // FTOKENIZER_H
