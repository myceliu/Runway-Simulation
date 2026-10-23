#ifndef RUNWAY_H
#define RUNWAY_H

#include <cstdlib>
#include <cfloat>
#include <queue>

class runway
{
    // For the sake of convenience:
    // Landing time == LT, Landing == L
    // Takeoff time == TT, Takeoff == T
    private:
        int LTNeeded;       // provided by the user, how long it takes for a plane to land. Must be positive
        int TTNeeded;       // provided by the user, how long it takes for a plane to takeoff. Must be positive
        float LArrivalRate; // 0 - 1 chance of landing, provided by user
        float TArrivalRate; // 0 - 1 chance of takeoff, provided by user
        int totalLT;        // total landing time
        int totalTT;        // total takeoff time
        int Lcount;         // number of landings
        int Tcount;         // number of takeoffs
        int LTremaining;    // amount of time left for a specific landing. When 0, runway is not busy
        int TTremaining;    // amount of time left for a specific takeoff. When 0, runway is not busy

    public:
        runway();                            // default constructor
        runway(int, int, float, float);     // constructor that takes user input for sim to run
        bool incomingL();                   // is a plane coming to land
        bool incomingT();                   // is a plane ready for takeoff
        bool isRunwayBusy();                // is the runway currently being used

        void startL();                      // start landing countdown
        void startT();                      // start takeoff countdown
        bool isThereL();                    // is a plane currently landing
        bool isThereT();                    // is a plane currently taking off

        void runtime();                     // passes 1 turn in the simulation
        int Ltotal();                       // how many landings will occur
        int Ttotal();                       // how many takeoffs will occur

        float averageWaitL();               // how long the average wait for landing was
        float averageWaitT();               // how long the average wait for takeoff was

        void Ltimesum(int);                 // sum of landing time
        void Ttimesum(int);                 // sum of takeoff time

        void runSim();                      // the main function of the simulation
        void results(double, double, runway, double, double);     // gives a report of simulation data
};

//#include "implement.cpp"
#endif
