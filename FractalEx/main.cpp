#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "useful.h"
using namespace std;
void random_fractal(double left_height, double right_height, double width, double epsilon, int level);
int main(){
    random_fractal(0, 0, 16, 1, 1);
    return EXIT_SUCCESS;
}
void random_fractal(double left_height, double right_height, double width, double epsilon, int level){
    double mid_height; // Height of the midpoint of the line segment
    assert(width > 0);
    assert(epsilon > 0);
    if (width <= epsilon){
        cout << setw(level*5) << level << " STOP";
        display(right_height);
    }
    else{
        cout << setw(level*5) << level << " Going Deeper >>>  ";
        mid_height = (left_height + right_height) / 2;
        mid_height += random_real(-width, width);
        cout << "Left: " << left_height << " , Right: " << right_height << " , Mid: " << mid_height << endl;
        random_fractal(left_height, mid_height, width/2, epsilon, level + 1);
        random_fractal(mid_height, right_height, width/2, epsilon, level + 1);
        cout << setw(level*5) << level << " Digging Back UP <<<" << endl;
    }
}
