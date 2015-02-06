#include "airport.h"
#include <cassert>
BoolSource::BoolSource(double prob = 0.5){
    assert(prob >= 0);
    assert(prog <= 1);
    probability = prob;
}

bool BoolSource::generate() const{
    return (rand() < probability * RAND_MAX);
}

Averager::Averager(){
    number = 0;
    sum = 0.0;
}

void Averager::addNum(double num){
    number++;
    sum += num;
}

std::size_t Averager::countNum() const{
    return number;
}
double Averager::average() const{
    assert(countNum() > 0);
    return sum/number;
}
Runway::Runway(unsigned int steps){
    maxStep = steps;
    stepsTilVacant = 0;
}

bool Runway::isOccupied() const{
    return stepsTilVacant > 0;
}
void Runway::step(){
    if(isOccupied()) stepsTilVacant--;
}

void Runway::begin(){
    assert(!isOccupied());
    stepsTilVacant = maxStep;
}


#endif // AIRPORT_H
