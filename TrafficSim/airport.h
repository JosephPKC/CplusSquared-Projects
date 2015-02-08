#ifndef AIRPORT_H
#define AIRPORT_H
#include <iostream>
#include <cstdlib>
//Bool Generator with a Probability Modifier
class BoolSource{
private:
    double probability;
public:
    BoolSource(double prob = 0.5);
    bool generate() const;
};
//Averager that holds the total and number of elements
class Averager{
private:
    double sum;
    std::size_t number;
public:
    Averager();
    void addNum(double num);
    std::size_t countNum() const;
    double average() const;
};
//Runway that processes planes; More generally, it is just a resource that is to be used be elements in basic simulations
class Runway{
private:
    unsigned int stepsTilVacant;
    unsigned int maxStep;
public:
    Runway(unsigned int steps);
    bool isOccupied() const;
    void step();
    void begin();
    void set(unsigned int steps);
};

#endif // AIRPORT_H
