#ifndef AIRPORT_H
#define AIRPORT_H
#include <iostream>
#include <cstdlib>
class BoolSource{
private:
    double probability;
public:
    BoolSource(double prob = 0.5);
    bool generate() const;
};
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
class Runway{
private:
    unsigned int stepsTilVacant;
    unsigned int maxStep;
public:
    Runway(unsigned int steps);
    bool isOccupied() const;
    void step();
    void begin();
};

#endif // AIRPORT_H
