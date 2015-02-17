#include <iostream>
#include <cstdlib>
#include <ctime>
#include "airport.h"
//#include "Queue.h"
#include "PriorityQueue.h"
using namespace std;
template <typename T, typename U>
ostream& operator <<(ostream& out, const std::pair<T,U> P){
    out << "(" << P.first << "," << P.second << ")" ;
    return out;
}

//TODO: Change aQueue into a Priority Queue//--------------------------------
//Constants for use without input function
const int LAND_AVERAGE = 4;
const int TAKEOFF_AVERAGE = 6;
//const int LAND_TIME = 5;
//const int TAKEOFF_TIME = 4;
const int NUM_OF_TURNS = 60;
const int FUEL_MAX = 7;
const int FUEL_MIN = 2;
const int LAND_MAX = 6;
const int LAND_MIN = 2;
const int TAKE_MAX = 5;
const int TAKE_MIN = 1;
//Pre: Use for before simulation in order to set parameters
//Process: Grabs parameters from user
//Post: There are no default values for parameters so all of them must be set
void inputValues(int& aAve, int& dAve, int& aMax, int& aMin, int& tMax, int& tMin, int& maxTurns, int& fuelMax, int& fuelMin);
//Pre: Requires the values from either input or preset constants
//Process: Simulates Air Traffic
//Post: Prints out relevant statistics at the end of the simulation
void simulateAirTraffic(int aAve, int dAve, int aMax, int aMin, int tMax, int tMin, int maxTurns, int fuelMax, int fuelMin);
//Pre: Uses the maximum and minimum parameters
//Process: generates a random number
//Post: Returns the randomly generated number
int generateRandom(int max, int min);
//Pre: Requires values from the simulatio
//Process: Prints out various stats
//Post: None
void outputStats(int aPlanesTotal, int dPlanesTotal, Averager aWait, Averager dWait, Averager fuel, Averager aTime, Averager dTime, int aPlanesDone, int dPlanesDone, int crashedPlanes);

int main(){
    int aAve, dAve, maxTurns, fuelMax, fuelMin, aMax, aMin, tMax, tMin;
    srand(time(NULL));
    inputValues(aAve,dAve,aMax,aMin,tMax,tMin,maxTurns,fuelMax,fuelMin);
    simulateAirTraffic(aAve,dAve,aMax,aMin,tMax,tMin,maxTurns,fuelMax,fuelMin);
  //  simulateAirTraffic(LAND_AVERAGE,TAKEOFF_AVERAGE,LAND_MAX,LAND_MIN,TAKE_MAX,TAKE_MIN,NUM_OF_TURNS,FUEL_MAX,FUEL_MIN);
    return 0;
}

void inputValues(int& aAve, int& dAve, int& aMax, int& aMin, int& tMax, int& tMin, int& maxTurns, int& fuelMax, int& fuelMin){
    cout << "Enter Average Turns for One Arrival: ";
    cin >> aAve;
    cout << "Enter Average Turns for One Departure: ";
    cin >> dAve;
    cout << "Enter Maximum Arrival Process Time: ";
    cin >> aMax;
    cout << "Enter Minimum Arrival Process Time: ";
    cin >> aMin;
    cout << "Enter Maximum Departure Process Time: ";
    cin >> tMax;
    cout << "Enter Minimum Departure Process Time: ";
    cin >> tMin;
    cout << "Enter Maximum Fuel Capacity in Turns: ";
    cin >> fuelMax;
    cout << "Enter Minimum Fuel Capacity in Tuns: ";
    cin >> fuelMin;
    cout << "Enter Number of Turns to Simulate: ";
    cin >> maxTurns;
}

int generateRandom(int max, int min){
    return rand()% (max - min) + min + 1;
}

void simulateAirTraffic(int aAve, int dAve, int aMax, int aMin, int tMax, int tMin, int maxTurns, int fuelMax, int fuelMin){
    //NOTE: The fuel for arrival is the turn it will crash if not processed
    PriorityQueue<std::pair<int,int> > aQueue; //Arrival Queue holds a pair for the timestamp and fuel
    Queue<int> dQueue; //Departure Queue only holds the timestamp
    int nextPlane; //The next plan to be processed
    BoolSource arrival(1.0/aAve); //Arrival and Departure Generators
    BoolSource departure(1.0/dAve);
    Runway runway(0); //The runway set to zero (Will be changed according to arrival or departure)
    Averager aWait; //Averagers for arrival wait times, departure wait times, and fuel amounts
    Averager dWait;
    Averager fuel;
    Averager aTime;
    Averager dTime;
    //Value for statistics
    int crashedPlanes = 0; //Number of planes that crashed while waiting to be processed
    int aPlanesTotal = 0; //Total arrivals
    int dPlanesTotal = 0; //Total departures
    int aPlanesDone = 0; //Number of arrivals processed
    int dPlanesDone = 0; //Number of departures processed
    cout << "Turns for Arrivals to Process: " << aMin << " - " << aMax << " turns." << endl;
    cout << "Turns for Departures to Process: " << tMin << " - " << tMax << " turns." << endl;
    cout << "Average Number of Turns for 1 Arrival: " << aAve << " turns." << endl;
    cout << "Average Number of Turns for 1 Departure: " << dAve << " turns." << endl;
    cout << "Total turns: " << maxTurns << endl;

    //The main simulation loop
    for(int currentTurn = 1; currentTurn <= maxTurns; currentTurn++){
//        cout << "---------------------------------------" << endl;
//        cout << "Turn: " << currentTurn << endl;
        cout << "T: " << currentTurn << " " << endl;
        //Check for arrival/departure
        if(arrival.generate()){ //Checking for arrival
            int fuelAmount = generateRandom(fuelMax,fuelMin);
            aQueue.push(std::make_pair( fuelAmount + currentTurn,currentTurn)); //Add to queue
            cout << "New Arrival: " << currentTurn << " with fuel: " << fuelAmount + currentTurn << endl;
//            cout << "New Arrival ";
            aPlanesTotal++;
            fuel.addNum(fuelAmount);
        }
        if(departure.generate()){ //Checking for departure
            dQueue.push(currentTurn); //Add to queue
            cout << "New Departure: " << currentTurn << endl;
//            cout << "New Departure ";
            dPlanesTotal++;
        }
        cout << endl;
        cout << "Arrivals: " << aQueue << endl;
        cout << "Departures: " << dQueue << endl;
         //Do stuff if runway is not busy
        if((!runway.isOccupied()) && (!aQueue.empty())){ //Priority goes to arrivals
//            cout << "Runway is not busy: Arrival" << endl;

            while(!aQueue.empty() && aQueue.front().first <= currentTurn){ //Checking for crashes
//                cout << "Arrival plane has crashed: " << aQueue.front().first << " <= " << currentTurn << endl;
                cout << "CRASHED" << endl;
                crashedPlanes++;
                aQueue.pop();
            }
            if(aQueue.empty()){ //If every plane in queue crashed
//                cout << "No more surviving arrival planes" << endl;

            }
            else{ //As long as there is a plane in queue that has survived
                nextPlane = aQueue.front().second;
//                cout << "The next plane: " << nextPlane << endl;
                aQueue.pop();
                aWait.addNum(currentTurn - nextPlane);
                aPlanesDone++;
                int aT = generateRandom(aMax,aMin);
                aTime.addNum(aT);
                runway.set(aT);
                runway.begin();
            }
        }
        if((!runway.isOccupied() && (!dQueue.empty()))){ //Process Departures
//            cout << "Runway is not busy: Departure" << endl;
            nextPlane = dQueue.front();
//            cout << "The next plane: " << nextPlane << endl;
            dQueue.pop();
            dWait.addNum(currentTurn - nextPlane);
            dPlanesDone++;
            int dT = generateRandom(tMax,tMin);
            dTime.addNum(dT);
            runway.set(dT);
            runway.begin();
        }
//        cout << "One turn has passed" << endl;
        runway.step(); //Increment the runway
    }
    outputStats(aPlanesTotal,dPlanesTotal,aWait,dWait,fuel,aTime,dTime,aPlanesDone,dPlanesDone,crashedPlanes);
}

void outputStats(int aPlanesTotal, int dPlanesTotal, Averager aWait, Averager dWait, Averager fuel, Averager aTime, Averager dTime, int aPlanesDone, int dPlanesDone, int crashedPlanes){
    cout << "------------STATS-------------" << endl;
    if(fuel.countNum() > 0) //Average for fuel (Not really necessary)
        cout << "Average Fuel in Turns for Arrival: " << fuel.average() << " Turns." << endl;
    if(aTime.countNum() > 0) //Average for fuel (Not really necessary)
        cout << "Average Arrival Process Time: " << aTime.average() << " Turns." << endl;
    if(dTime.countNum() > 0) //Average for fuel (Not really necessary)
        cout << "Average Departure Process Time: " << dTime.average() << " Turns." << endl;
    if(aWait.countNum() > 0)
        cout << "Average Arrival Wait Time: " << aWait.average() << " Turns." << endl;
    if(dWait.countNum() > 0)
        cout << "Average Departure Wait Time: " << dWait.average() << " Turns." << endl;
    cout << "Total Planes: " << aPlanesTotal + dPlanesTotal << " Planes." << endl;
    cout << "Total Arrivals: " << aPlanesTotal << " Planes." << endl;
    cout << "Number of Arrivals processed: " << aPlanesDone << " Planes." << endl;
    cout << "Number of Arrivals still waiting: " << aPlanesTotal - aPlanesDone - crashedPlanes << " Planes." << endl;
    cout << "Number of Crashed Arrival Planes: " << crashedPlanes <<" Planes." <<  endl;
    cout << "Total Departures: " << dPlanesTotal << " Planes." << endl;
    cout << "Number of Departures processed: " << dPlanesDone << " Planes." << endl;
    cout << "Number of Departures still waiting: " << dPlanesTotal - dPlanesDone << " Planes." << endl;
    cout << "Arrival Efficiency: " << aPlanesDone / (double)aPlanesTotal * 100 << "%." << endl;
    cout << "Departure Efficiency: " << dPlanesDone / (double)dPlanesTotal * 100 << "%." << endl;
    cout << "Total Efficiency: " << (aPlanesDone + dPlanesDone) / (double)(aPlanesTotal + dPlanesTotal) * 100 << "%." << endl;
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
