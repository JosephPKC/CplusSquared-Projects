#include "expressionevaluator.h"

void ExpressionEvaluator::setTokenDictionary(std::map<Type,std::string> set){
    dictionary = set;
    stk.createSets(dictionary);
}

void ExpressionEvaluator::convertToPost(std::string exp){
    using namespace std;
    //Given: We have a string expression in infix
    //To convert to postfix, we first check char:
        //If it is a number, place into R stack
        //If it is an operator:
            //If there is no operator at the top of O stack, place in O
            //If the operator at top is lower, place in O
            //If the operator atop is higher, pop that operator into R, place operator into O
            //If the operator at top is equal, pop operator into R, place other into O
        //If it is a L.P., place into O
        //If it is a R.P., pop from O until a L.P., place the operators into R in order
            //Disregard the P
        //If there is a null, pop everything in O into R
    Stack<Token> R; //The result stack
    Stack<Token> O; //The temporary operator stack
    stk.setBlock(exp);
    Token Space(" ",SPACE);
    cout << "This is the expression: " << exp << endl;
    for(int i = 0; i < exp.length(); i++){
        cout << "Stacks R and O at the beginning of the loop:\n" << R << endl << O << endl;
        Token T = stk.nextToken();
        cout << "The token stk grabbed in the expression: " << T << endl;
        cout << "The token type: " << T.getType() << endl;
        if(T.getType() == NUM){
            R.push(Space);
            R.push(T);
        }
        else if(T.getType() == HIGHER || T.getType() == LOWER){
            if(O.empty() || O.top().getType() != HIGHER && O.top().getType() != LOWER){
                O.push(T);
            }
            else if(T.getType() == HIGHER && O.top().getType() == LOWER){
                O.push(T);
            }
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
        else if(T.getType() == LEFT){
            O.push(T);
        }
        else if(T.getType() == RIGHT){
            Token P = O.pop();
            while(!O.empty() && P.getType() != LEFT){
                cout << "In RIGHT, the token P is: " << P << endl;
                R.push(Space);
                R.push(P);
                P = O.pop();
            }
            if(P.getType() != LEFT){
                R.push(Space);
                R.push(P);
            }
        }
        else{
            //NOT PART OF THE SET
        }
    }
    while(!O.empty()){
        R.push(Space);
        R.push(O.pop());
    }
    while(!R.empty()){
        O.push(R.pop());
    }
    while(!O.empty()){
        expression += O.pop().getToken();
    }


}

bool ExpressionEvaluator::isPostFix(std::string exp){

}

bool ExpressionEvaluator::isValid(std::string exp){
    int counter = 0;
    int pCounter = 0;
    using namespace std;
    stk.setBlock(exp);
    while(stk.moreInBlock()){
        cout << "Counter: " << counter << endl;
        cout << "PCounter: " << pCounter << endl;
        if(counter < 0) return false;
        if(pCounter < 0) return false;
        Token T = stk.nextToken();
        cout << "Token: " << T << endl;
        cout << "Type: " << T.getType() << endl;
        if(T.getType() == UNKNOWN) return false;
        if(T.getType() == HIGHER || T.getType() == LOWER){
            counter -= T.getToken().length();
        }
        else if(T.getType() == NUM){
            counter += T.getToken().length();;
        }
        else if(T.getType() == LEFT){
            pCounter += T.getToken().length();;
        }
        else if(T.getType() == RIGHT){
            if(pCounter == 0) return false;
            pCounter -= T.getToken().length();;
        }
    }
    if(counter == 1 && pCounter == 0) return true;
    else return false;
}

void ExpressionEvaluator::setExpression(std::string exp){
    if(isValid(exp)) expression = exp;
}

std::string ExpressionEvaluator::getExpression(){
    return expression;
}

std::string ExpressionEvaluator::evaluate(){
    using namespace std;
    Stack<Token> S;
    stk.setBlock(expression);
    cout << "This is the expression: " << expression << endl;
    while(stk.moreInBlock()){
        Token T = stk.nextToken();
        cout << "Token: " << T << endl;
        cout << "Type: " << T.getType() << endl;
        if(T.getType() == NUM){
            S.push(T);
        }
        else if(T.getType() == HIGHER || T.getType() == LOWER){
            int second = atoi(S.pop().getToken().c_str());
            int first = atoi(S.pop().getToken().c_str());
            cout << "This is second: " << second << endl;
            cout << "This is first: " << first << endl;
            int result;
            if(T.getToken() == "+") result = first + second;
            if(T.getToken() == "-") result = first - second;
            if(T.getToken() == "*") result = first * second;
            if(T.getToken() == "/") result = first / second;
            std::string str = "";
            str += (convertInt(result));
            cout << "THis is result: " << result << endl;
            cout << "THis is result: " << str << endl;
            S.push(Token(str,NUM));
        }
        else if(T.getType() == SPACE){

        }
    }
    std::string s = "";
    while(!S.empty()){
        s += S.pop().getToken() + " ";
    }
    return s;
}

std::string ExpressionEvaluator::convertInt(int i){
    bool negative = (i < 0);
    std::string s = "";
    if(negative){
        s += "-";
        i *= -1;
    }

    int d = 1;
    int temp = i;
    while(temp / 10 != 0){
        d++;
        temp -= 10 * (temp/10);
    }
//    std::cout << d << std::endl;
    for(int j = d-1; j >= 0; j--){
//        std::cout << i/(int)pow(10,j) << std::endl;
        s += i/(int)pow(10,j) + '0';
//        std::cout << s << std::endl;
//        std::cout << i/(int)pow(10,j) << std::endl;
        i = i%(int)pow(10,j);

    }
    return s;
}
