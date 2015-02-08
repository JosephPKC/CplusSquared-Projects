#include "airport.h"
#include <cassert>
//Constructor
BoolSource::BoolSource(double prob){
    assert(prob >= 0); //probability has to be between 0% and 100%
    assert(prob <= 1);
    probability = prob;
}
//Generators true or false randomly
bool BoolSource::generate() const{
    return (rand() < probability * RAND_MAX);
}
//Constructor
Averager::Averager(){
    number = 0;
    sum = 0.0;
}
//Adds a number into the averager
void Averager::addNum(double num){
    number++;
    sum += num;
}
//Returns the number of elements
std::size_t Averager::countNum() const{
    return number;
}
//Calculates the average
double Averager::average() const{
    assert(countNum() > 0); //Cannot have negative number of elements (It is a measure) and cannot divide by zero
    return sum/number;
}
//Constructor
Runway::Runway(unsigned int steps){
    maxStep = steps;
    stepsTilVacant = 0;
}
//Sets the time it take for the runway to process
void Runway::set(unsigned int steps){
    maxStep = steps;
}
//Checks if it is busy
bool Runway::isOccupied() const{
    return stepsTilVacant > 0;
}
//Steps up the runway (IE decreases the steps til it is not busy)
void Runway::step(){
    if(isOccupied()) stepsTilVacant--;
}
//Begins the processing (IE makes the runway busy)
void Runway::begin(){
    assert(!isOccupied());
    stepsTilVacant = maxStep;
}



