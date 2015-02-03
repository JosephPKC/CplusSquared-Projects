#include "expressionevaluator.h"
/**
 * @brief ExpressionEvaluator::setTokenDictionary sets the stokenizer dictionary
 * @param set the char set
 */
void ExpressionEvaluator::setTokenDictionary(std::map<Type,std::string> set){
    dictionary = set;
}
/**
 * @brief ExpressionEvaluator::convertToPost converts an expression in infix to postfix
 * @param exp the expression
 * @return a postfix version
 */
std::string ExpressionEvaluator::convertToPost(std::string exp){
    //By now the expression is hopefully valid
    Stack<Token> R; //The result stack
    Stack<Token> O; //The temporary operator stack
    STokenizer stk(exp); //tokenizer
    stk.createSets(dictionary);
    Token Space(" ",SPACE);
    Token T;
    while(stk.moreInBlock()){ //Goes through the entire expression
        T = stk.nextToken(); //Grab a token
        if(T.getType() == NUM){ //If its a number
            R.push(Space);
            R.push(T);
        } //For operators
        else if(T.getType() == HIGHER || T.getType() == LOWER){
            if(O.empty() || (O.top().getType() != HIGHER && O.top().getType() != LOWER))
                O.push(T);
            else if(T.getType() == HIGHER && O.top().getType() == LOWER)
                O.push(T);
            else if(T.getType() == LOWER && O.top().getType() == HIGHER){
                R.push(Space);
                R.push(O.pop());
                O.push(T);
            }
            else if(T.getType() ==  O.top().getType()){
                R.push(Space);
                R.push(O.pop());
                O.push(T);
            }
        }
        else if(T.getType() == LEFT){ //For left parenthesis //For loop for adjacent multiple ones
            for(unsigned int i = 0; i < T.getToken().length(); i++)
                O.push(Token(T.getToken()[0],LEFT));
        }
        else if(T.getType() == RIGHT){ //For right //Same idea as left
            Token P;
            for(unsigned int i = 0; i < T.getToken().length(); i++){
                P = O.pop();
                while(!O.empty() && P.getType() != LEFT){
                    R.push(Space);
                    R.push(P);
                    P = O.pop();
                }
            }
            if(P.getType() != LEFT){ //Leftover operators
                R.push(Space);
                R.push(P);
            }
        }
        else{
            //NOT PART OF THE SET
        }
    }
    //Exp is done now
    while(!O.empty()){ //Pushes the rest of the operators into the result stack
        R.push(Space);
        R.push(O.pop());
    }
    while(!R.empty()) //Reverse the stack
        O.push(R.pop());
    std::string result = "";
    while(!O.empty()) //Add the elements of the stack to the string
        result += O.pop().getToken();
    return result;
}
/**
 * @brief ExpressionEvaluator::evaluateExpression evaluates the expression
 * @return the string result //Probably better as an int
 */
std::string ExpressionEvaluator::evaluateExpression(){
    //expression should be valid by now
    if(!isPostFix(expression)) expression = convertToPost(expression); //Convert to Post if necessary
    return evaluate(expression);
}
/**
 * @brief ExpressionEvaluator::isPostFix checks if exp is postfix; must find a better way to check without evaluating
 * @param exp expression
 * @return True: is post fix, False: is not
 */
bool ExpressionEvaluator::isPostFix(std::string exp){
    return evaluate(exp) != "";
}

//bool ExpressionEvaluator::isValid(std::string exp){
//    int counter = 0;
//    int pCounter = 0;
//    using namespace std;
//    STokenizer stk(exp);
//    stk.createSets(dictionary);
//    while(stk.moreInBlock()){
//        cout << "Counter: " << counter << endl;
//        cout << "PCounter: " << pCounter << endl;
//        if(counter < 0) return false;
//        if(pCounter < 0) return false;
//        Token T = stk.nextToken();
//        cout << "Token: " << T << endl;
//        cout << "Type: " << T.getType() << endl;
//        if(T.getType() == UNKNOWN) return false;
//        if(T.getType() == HIGHER || T.getType() == LOWER){
//            counter -= T.getToken().length()*2;
//            std::cout << "Counter in OP check: " << counter << std::endl;
//            if(counter < 0) return false;
//            counter += T.getToken().length();
//        }
//        else if(T.getType() == NUM){
//            counter += T.getToken().length();;
//        }
//        else if(T.getType() == LEFT){
//            pCounter += T.getToken().length();;
//        }
//        else if(T.getType() == RIGHT){
//            if(pCounter == 0) return false;
//            pCounter -= T.getToken().length();;
//        }
//    }
////    return true;
//    if(counter == 1 && pCounter == 0) return true;
//    else return false;
//}
/**
 * @brief ExpressionEvaluator::setExpression set the expression
 * @param exp expression
 */
void ExpressionEvaluator::setExpression(std::string exp){
//    if(isValid(exp)) expression = exp; //Need a better way to check for validity
    expression = exp;
}
/**
 * @brief ExpressionEvaluator::getExpression returns the expression
 * @return expression
 */
std::string ExpressionEvaluator::getExpression(){
    return expression;
}
/**
 * @brief ExpressionEvaluator::evaluate evaluates the exprsesion
 * @param exp the expression
 * @return string result or empty string if un-evaluable (is that a word?)
 */
std::string ExpressionEvaluator::evaluate(std::string exp){
    Stack<Token> S;
    STokenizer stk(exp);
    stk.createSets(dictionary);
    while(stk.moreInBlock()){
        Token T = stk.nextToken();
        if(T.getType() == NUM) //If its a number
            S.push(T);
        else if(T.getType() == HIGHER || T.getType() == LOWER){ //For operators
            if(S.empty() || S.size() < 2) return "";
            int second = atoi(S.pop().getToken().c_str()); //Convert to int
            int first = atoi(S.pop().getToken().c_str());
            int result;
            if(T.getToken() == "+") result = first + second;
            if(T.getToken() == "-") result = first - second;
            if(T.getToken() == "*") result = first * second;
            if(T.getToken() == "/") result = first / second;
            std::string str = "";
            str += (convertInt(result)); //Convert back to string
            S.push(Token(str,NUM));
        }
        else { //For spaces or invalid characters

        }
    }
    std::string s = S.pop().getToken();
    if(!S.empty()) return "";
    return s;
}
/**
 * @brief ExpressionEvaluator::convertInt converts int to string
 * @param i int
 * @return string
 */
std::string ExpressionEvaluator::convertInt(int i){
    std::string s = "";
    if(i < 0){ //Check for negative
        s += "-";
        i *= -1;
    }
    int d = 1; //Number of digits
    while(i / (int)pow(10,d) != 0)
        d++;
    for(int j = d-1; j >= 0; j--){ //Create a char version of each digits and append
        s += i/(int)pow(10,j) + '0';
        i = i%(int)pow(10,j);
    }
    return s;
}
