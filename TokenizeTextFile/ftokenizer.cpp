#include "ftokenizer.h"
#include <iostream>
FTokenizer::FTokenizer(std::string file):FTokenizer(){
    fileS.open(file);
    if(!fileS.is_open()) //f.std::ios::fail()
        std::cout << "HEY THE FILE FAILED TO OPEN" << std::endl;
}

//Token FTokenizer::nextToken(){
//    if(stk.more()){
//        Token T = stk.nextToken();

//    }
//    else{
//        stk.setString();
//    }
//    //Gets the next token
//    //Load up the stokenizer with a block if its empty
//    //Call the stokenizer's next token
//    //return the token
//}

//bool FTokenizer::getNewBlock(){
//    //get blockpos and get the maxblock size amount of chars after that blockpos
//    //
//}

//bool FTokenizer::more(){
//    //If the file has reached eof, then there is no more so return false
//}

//int FTokenizer::pos(){
//    return pos;
//}

//int FTokenizer::blockPos(){
//    //Position of the block?
//}
