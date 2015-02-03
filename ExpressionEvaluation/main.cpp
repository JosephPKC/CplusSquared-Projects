#include <iostream>
#include "expressionevaluator.h"
using namespace std;

void testExpressionEvaluator();
void evalAndPrint(string exp,ExpressionEvaluator E);
int main(){
    testExpressionEvaluator();
    std::string exp = "";
    ExpressionEvaluator E;
    E.setTokenDictionary(expSet);
    while(true){
        cout << ":";
        cin >> exp;
        if(exp == "END") exit(0);
        cout << endl;
        E.setExpression(exp);
        cout << E.evaluateExpression() << endl;
    }
    return 0;
}

void testExpressionEvaluator(){
    ExpressionEvaluator E;
    E.setTokenDictionary(expSet);
    evalAndPrint("3*(9+43/7+(421+216/3))/2",E); //762
    evalAndPrint("1 2 + 3 4 * 4 + * 1 2 - 3 + /",E); //24
    evalAndPrint("2*(5+6*(7*3+8-1*3)*5)",E); //1570
}

void evalAndPrint(string exp, ExpressionEvaluator E){
    E.setExpression(exp);
    cout << E.getExpression() << endl;
    cout << E.evaluateExpression() << endl;
}
