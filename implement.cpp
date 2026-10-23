#include <cfloat>
#include <assert.h>
#include "runway.h"
#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

runway::runway()                                             // default constructor
{
    
}

runway::runway(int LT, int TT, float Lrate, float Trate)     // constructor that takes user input for sim to run
{
    LTNeeded = LT;
    TTNeeded = TT;
    LArrivalRate = Lrate;
    TArrivalRate = Trate;
    totalLT = 0;
    totalTT = 0;
    Lcount= 0;
    Tcount = 0;
    LTremaining = 0;
    TTremaining = 0;
}

bool runway::incomingL()                   // is a plane coming to land
{
    return (float)rand()/RAND_MAX < LArrivalRate;
}

bool runway::incomingT()                   // is a plane ready for takeoff
{
    return (float)rand()/RAND_MAX < TArrivalRate;
}

bool runway::isRunwayBusy()                // is the runway currently being used
{
    if(LTremaining >  0 || TTremaining > 0) { return true; }
    else { return false; }
}

void runway::startL()                      // start landing countdown
{
    assert(!isRunwayBusy());     // check if the runway is busy
    {
        LTremaining = LTNeeded;
       std::cout << "Beginning landing. . .\n";
    }
}

void runway::startT()                      // start takeoff countdown
{
    assert(!isRunwayBusy());
    {
        TTremaining = TTNeeded;
        std::cout << "Beginning takeoff. . .\n";
    }
}

bool runway::isThereL()                         // is a plane currently landing
{
    return (LTremaining > 0);    // if landing time remaining is greater than 0, return true
}

bool runway::isThereT()                         // is a plane currently taking off
{
    return (TTremaining > 0);    // if takeoff time remaining is greater than 0, return true
}

void runway::runtime()                        // passes 1 turn in the simulation
{
    if(isThereL())
    {
        LTremaining--;
        
        if(LTremaining == 0)
        {
            cout << "Landing complete. . ." << endl;
        }
    }
    else if(isThereT())
    {
        TTremaining--;
        
        if(TTremaining == 0)
        {
            cout << "Takeoff complete. . ." << endl;
        }
    }
}

int runway::Ltotal()                      // how many landings will occur
{
    return Lcount;
}

int runway::Ttotal()                      // how many takeoffs will occur
{
    return Tcount;
}

float runway::averageWaitL()               // how long the average wait for landing was
{
    if(Lcount > 0) { return (totalLT / Lcount); }
    else { return 0; }
}

float runway::averageWaitT()               // how long the average wait for takeoff was
{
    if(Tcount > 0) { return (totalTT / Tcount); }
    else { return 0; }
}

void runway::Ltimesum(int x)               // sum of landing time
{
    Lcount++;
    totalLT = totalLT + x;
}

void runway::Ttimesum(int x)               // sum of takeoff time
{
    Tcount++;
    totalTT = totalTT + x;
}

void runway::runSim()                           // the main function of the simulation
{
    queue<int> landingQ;
    queue<int> takeoffQ;
    
    int current;
    int next;
    int LTneeded;
    int TTneeded;
    int simLength;
    
    float LarriveRate;      // should be 0 < x < 1
    float TarriveRate;      // same as above
    
    char answer[2];

    do
    {
        cout << "Enter simulator data:\n";
        cout << "Total amount of turns the simuation should last: ";
            cin >> simLength;
        cout << "Rate of aircraft landings: ";
            cin >> LarriveRate;
        
        while(LarriveRate > 1 || LarriveRate < 0)
        {
            cout << "   Please enter a number less than 1 and greater than 0 for the rate of aircraft landings. (0 < x < 1)" << endl;
            cout << "Rate of aircraft landings: ";
            cin >> LarriveRate;
        }

        cout << "Rate of aircraft takeoffs: ";
            cin >> TarriveRate;

        while(TarriveRate > 1 || TarriveRate < 0)
        {
            cout << "   Please enter a number less than 1 and greater than 0 for the rate of aircraft takeoffs. (0 < x < 1)" << endl;
            cout << "Rate of aircraft takeoffs: ";
            cin >> LarriveRate;
        }

        cout << "Amount of turns needed for a landing to finish: ";
            cin >> LTneeded;
        cout << "Amount of turns needed for a takeoff to finish: ";
            cin >> TTneeded;

        runway one(LTneeded, TTneeded, LarriveRate, TarriveRate);

        cout << "----------------------------------------\n";

        srand(time(NULL));

        double landingCount = 0;
        double takeoffCount = 0;

        for(current = 1; current < simLength; current++)
        {
            if(one.incomingL())
            {
                landingQ.push(current);   // add plane to landing queue
                landingCount++;
            }
            if(one.incomingT())
            {
                takeoffQ.push(current);   // add plane to takeoff queue
                takeoffCount++;
            }

            if(!one.isRunwayBusy() && !landingQ.empty())
            {
                next = landingQ.front();
                landingQ.pop();
            
                one.Ltimesum(current - next);
                one.startL();
            }
            else if(!one.isRunwayBusy() && landingQ.empty() && !takeoffQ.empty())
            {
                next = takeoffQ.front();
                takeoffQ.pop();
            
                one.Ttimesum(current - next);
                one.startT();
            }

            one.runtime();
        }

        if(one.isThereL() == true)
        {
            cout << "Landing complete. . ." << endl;
        }

        if(one.isThereT() == true)
        {
            cout << "Takeoff complete. . ." << endl;
        }

        double deniedL = 0;
        double deniedT = 0;

        while(!landingQ.empty())
        {
            deniedL++;
            landingQ.pop();
        }

        while(!takeoffQ.empty())
        {
            deniedT++;
            takeoffQ.pop();
        }

        one.results(deniedL, deniedT, one, landingCount, takeoffCount);

        cout << "Perform another simulation?\n -->";
        cin >> answer;
        cout << endl << endl;
    }
    while( tolower(answer[0] == 'y') );
}

void runway::results(double deniedL, double deniedT, runway one, double landingCount, double takeoffCount)       // gives a report of simulation data
{
    double totalDenied = deniedL + deniedT;
    double totalAll = landingCount + takeoffCount;
    double totalAccepted = one.Ltotal() + one.Ttotal();

    cout << "------------------------------------------------------\n";
    cout << "--START OF REPORT--" << endl;
    
    cout << "Simulation data report: " << endl;
    cout << "   Average landing wait time: " << one.averageWaitL() << " turns" << endl;
    cout << "   Average takeoff wait time: " << one.averageWaitT() << " turns" <<  endl;
    cout << "   Number of landings: " << one.Ltotal() << endl;
    cout << "   Number of takeoffs: " << one.Ttotal() << endl;
    cout << "   Number of aircraft denied landing: " << deniedL << endl;
    cout << "   Number of aircraft denied takeoff: " << deniedT << endl;
    cout << "   Total number of aircraft requesting landing: " << landingCount << endl;
    cout << "   Total number of aircraft requesting takeoff: " << takeoffCount << endl;
    cout << "   Full total amount of aircraft: " << (totalAll) << endl;
    cout << endl;
    cout << "   Percentage of rejected aircraft: " << fixed << setprecision(2) << (totalDenied / totalAll) * 100 << "% " << endl;
    cout << "   Percentage of accepted aircraft: " << fixed << setprecision(2) << (totalAccepted / totalAll) * 100 << "% " << endl;
    
    cout << "--END OF REPORT--" << endl;
    cout << "-------------------------------------------------------\n";
}
