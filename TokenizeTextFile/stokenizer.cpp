#include "stokenizer.h"

//friend STokenizer& operator >>(STokenizer& st, std::string& token){
//    token = st.nextToken();

//}

//Type STokenizer::tokenType(char ch){
//    //check what type of token ch is and return the integer value associated with that token
//}

//std::string STokenizer::getThisToken(std::string charSet){
//    //In the string, starting at pos: get a char that belongs to the charSet.
//    //Then keep going until you get a char that does not belong to the charSet.
//    //Substring between those two points and you get the token of the charSet
//    //return that substring
//}

//std::string STokenizer::setString(const std::string s){
//    block = s;
//}

//std::string STokenizer::nextString(){
//    //Gets the next string?
//}

//Token STokenizer::nextToken(){ //The bread and butter of Stokenizer
//    //In the string, starting at pos, get the very first char.
//    //Then determine which set the char belongs to
//    //Then keep going until you get a char that does not belong to the set
//    //Then substring and create a token between the two points
//    //return the token, setting the type to the charset
//}

//bool STokenizer::fail(){
//    //If it finds a char that does not belong to any of the known charsets, then create a new charset called UNKNOWNS
//    //Place that char in it, and then move on- This operation should be in nextToken
//    //It fails if it hits a char that is not known
//}

//bool STokenizer::more(){
//    //If the string hits the end, i.e. if the position is at the end of the string(or the length - 1) then there is no more
//    //That means it needs a new string, i.e. block before it can continue
//}

//int STokenizer::getPos(){
//    return pos;
//}

//GOTTA TEST THIS FUNCTION
Token STokenizer::nextToken(){
    //Check if there is more in the block
    //If so then grab the first char in the block at pos
    //Find the type of that char
    //Save that pos, and move the pos until you find a char not of that type
    //Substring those two positions and create a token
    //return that token
    //If there is no more in the block, ask for more?
    //Throw an invalid token, if possible?
    //Or perhaps throw an exception
    std::cout << "Pos: " << pos << std::endl;
    if(moreInBlock()){
        std::cout << "There is more in the block." << std::endl;
        Type tType = tokenType(block[pos]);
        //What do to with unknowns:
        //Ignore them and keep looking for a valid token
        //Ignore them and throw a null
        //Spit out that unknown token
//        while(!isKnown(block[pos])){
//            setUnknown(block[pos]);
//            pos++;
//            std::cout << "CHecking for unknown: " << tokenType(block[pos]) << std::endl;
//        }
        while(!isKnown(block[pos])){
//            setUnknown(block[pos]);
            pos++;
            if(!moreInBlock()) return Token("",VOID);
        }
        tType = tokenType(block[pos]);
        std::cout << "After Unknown Check Pos: " << pos << std::endl;
        std::cout << "Token type: " << tType << std::endl;
        std::cout << "Token set: " << tokenSet.at(tType) << std::endl;
        std::string tName = getToken(tokenSet.at(tType));
        if(tName == "") tName = block.substr(pos,block.length());
        std::cout << "Token name: " << tName << std::endl;
        Token tNew(tName,tType);
        return tNew;
    }
    else{ //No more in the string
        std::cout << "Nothing" << std::endl;
//        return NULL;
    }
}

bool STokenizer::setBlock(std::string newBlock){
    block = newBlock;
}

bool STokenizer::moreInBlock(){
//    std::cout << "Pos: " << pos << std::endl;
//    std::cout << "Block: " << block << std::endl;
//    std::cout << "Block length: " << block.length() << std::endl;
    return pos < block.length();
}

int STokenizer::getPos(){
    return pos;
}

Type STokenizer::tokenType(char ch){
    for(const auto& it : charList){
        if(isType(ch,it.second)) return it.first;
    }
    return DEFAULT;
}

bool STokenizer::isKnown(char ch){
    return tokenType(ch) != DEFAULT;
}

void STokenizer::setUnknown(char ch){ //Assumes the character is unknown
    charList[UNKNOWN] += ch;
}

std::string STokenizer::getToken(std::string charSet){
    int bPos = block.find_first_of(charSet,pos);
    int ePos = block.find_first_not_of(charSet,pos+1);
    std::cout << "Begin: " << bPos << " End: " << ePos << std::endl;
    if(bPos == -1) return "";
    if(ePos == -1){
        pos = block.length();
        return block.substr(bPos);
    }
    pos = ePos;
    std::cout << "The substring: " << block.substr(bPos,abs(bPos-ePos)) << std::endl;
    return block.substr(bPos,abs(bPos-ePos));
}

void STokenizer::createSets(std::map<Type,std::string> sets){
    charList = sets;
}

bool STokenizer::isType(char ch, std::string set){
    return set.find(ch) != -1;
}
