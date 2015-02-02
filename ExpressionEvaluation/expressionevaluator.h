#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H
#include <iostream>
#include "stack.h"
#include "stokenizer.h"
#include <stdlib.h>
#include <cmath>
class ExpressionEvaluator{
private:
public:
    std::string expression;
    STokenizer stk;
    std::map<Type,std::string> dictionary;


    void convertToPost(std::string exp);

    bool isPostFix(std::string exp); //Only way to check is to evaluate it
    bool isValid(std::string exp); //Remove
    std::string convertInt(int i);

public:
    ExpressionEvaluator() : expression(""){}
    void setExpression(std::string exp);
    std::string getExpression();
    std::string evaluate();
    void setTokenDictionary(std::map<Type,std::string> set);
};

#endif // EXPRESSIONEVALUATOR_H
