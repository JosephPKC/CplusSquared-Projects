#include <iostream>
#include "expressionevaluator.h"
using namespace std;


int main(){
    //Get expression input as strinbg
    //Determine if the chars are valid
    //determine whether it is infix, postfix, or neither
        //If neither, then disregard expression
        //If infix, convert to postfix
        //If postfix, move on
    //Perform expression evaluation
    //Output the answer


    ExpressionEvaluator E;
    cout << E.convertInt(12) << endl;
    E.setTokenDictionary(expSet);
//    cout << (E.isValid("(1+2)*((3*4)+4)/((1-2)+3)")?"Valid":"Not Valid") << endl;
    E.convertToPost("12+34+/2+");
    cout << E.expression << endl;
//    cout << E.evaluate() << endl;
    return 0;
}
