//#include "stokenizer.h"

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
