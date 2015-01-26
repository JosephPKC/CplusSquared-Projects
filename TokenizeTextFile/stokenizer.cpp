#include "stokenizer.h"

friend STokenizer& operator >>(STokenizer& st, std::string& token);
int tokenType(char ch);
std::string getThisToken(std::string charSet);
std::string setString(const std::string s);
std::string nextString();
Token nextToken();
bool fail();
bool more();
int getPos();
