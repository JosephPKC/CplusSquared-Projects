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
    bool setBlock(std::string block);
public:
    static const int MAX_BLOCK = 50; //Size of the block
    FTokenizer():stk(),pos(0),more(false){}
    FTokenizer(std::string file);
//    Token nextToken();
//    bool getNewBlock();
//    bool isMore();
//    int getPos();
//    int blockPos();
    bool setFile(char* file);
    Token nextToken();

    bool moreInFile();
    int getPos();


};

#endif // FTOKENIZER_H

/*
 * The responsibilities of FTokenizer:
 * Constructors: Default, File Argument
 * Set the File
 * Grab the next Token in the File
 * Split the file into blocks
 * Check if there are more characters in the file
 * Change the cursor pos in the file
 * Set the STokenizer for a new block
 */
