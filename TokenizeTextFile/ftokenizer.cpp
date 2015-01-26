#include "ftokenizer.h"
#include <iostream>
FTokenizer::FTokenizer(char* file):FTokenizer(){
    f.open(file);
    if(!f.is_open()) //f.std::ios::fail()
        std::cout << "HEY THE FILE FAILED TO OPEN" << std::endl;
}

Token FTokenizer::nextToken(){
    //Gets the next token
    //Load up the stokenizer with a block if its empty
    //Call the stokenizer's next token
    //return the token
}

bool FTokenizer::getNewBlock(){
    std::string block;
    f.read(block,MAX_BLOCK);

}

bool more();
int pos();
int blockPos();
