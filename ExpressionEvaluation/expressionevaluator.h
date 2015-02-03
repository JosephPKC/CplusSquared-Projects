#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H
#include <iostream>
#include "stack.h"
#include "stokenizer.h"
#include <stdlib.h>
#include <cmath>
class ExpressionEvaluator{
private:
    std::string expression;
    std::map<Type,std::string> dictionary;

    std::string convertToPost(std::string exp);
    bool isPostFix(std::string exp); //Only way to check is to evaluate it
//    bool isValid(std::string exp); //Remove
    std::string convertInt(int i);
    std::string evaluate(std::string exp);
public:
    ExpressionEvaluator() : expression(""){}
    void setExpression(std::string exp);
    std::string getExpression();
    std::string evaluateExpression();
    void setTokenDictionary(std::map<Type,std::string> set);
};

//Things to note:
//Currently does not support expression validation
//Does not check for division by zero
//Rounds down division due to integer division

#endif // EXPRESSIONEVALUATOR_H
