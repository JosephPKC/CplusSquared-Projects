#include <iostream>
#include <cstdlib>
#include <ctime>
#include "airport.h"
using namespace std;
///all inputs
const int LAND_AVERAGE = 7;
const int TAKEOFF_AVERAGE = 3;
const int LAND_TIME = 3;
const int TAKEOFF_TIME = 2;
//Priority to land planes
const int NUM_OF_TURNS = 500;
const int FUEL_MAX = 20;
const int FUEL_MIN = 4;
//void inputValues(int& aAve, int& dAve, int& aT, int& dT, int& maxTurns, int& fuelMax, int& fuelMin);
void simulateAirTraffic(int aAve, int dAve, int aT, int dT, int maxTurns, int fuelMax, int fuelMin);

int main(){

    return 0;
}

void simulateAirTraffic(int aAve, int dAve, int aT, int dT, int maxTurns, int fuelMax, int fuelMin){
    //Queue<std::pair<unsigned int, unsigned int> > aQueue;
    //Queue<unsigned int> dQueue;
    unsigned int nextPlane;
    BoolSource arrival(1.0/aAve);
    BoolSource departure(1.0/dAve);
    Runway runway(); //Which time to load
    Averager aWait;
    Averager dWait;
    unsigned int currentTurn;
    for(currentTurn = 1; currentTurn <= maxTurns; currentTurn++){
        //Check for arrival/departure
        //Do stuff if runway is not busy
        runway.step();
    }
}

//NOTE:
//Land Queue holds at what turn they crash & when they got into queue
//grab inputs
//Set values
//run the simulation
//-Every minute, check if a plane lands or takes off
//-If either of those are true, place that plane in appropriate queue
//-Check if runway is busy
//-If it is not busy, grab a plane from landing
//-If the plane from landing ran out of fuel, record as crashed and rid of it
//-If there are no planes in landing, grab a plane from takeoff
//-Set runway to busy until plane finishes action
//Record if:
//-Plane took off
//-Plane landed
//-Plane crashed
//-Each Plane's wait time
//Output each record and the averages of the wait times
//Once simulation ends:
//-Record all crashed planes in landing
//-Record all planes still waiting
//-Calculate TOTAL planes
//Efficiency- Number of planes successful/Number of planes total * 100
