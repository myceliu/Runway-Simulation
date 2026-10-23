/*
Data Structures
Program 2 Runway Simulator

This program runs a simulation of an airport runway. It will ask the user to give 5 inputs. These inputs are simulation
 length, arrival rate of landings, arrival rate of takeoffs, landing time needed, and takeoff time needed. After recieving
 this data, the program will run a simulation of a runway under these conditions. After completion, it will give the user 
 a report of the simulation. The program will then ask the user if they wish to run another simulation. If 'n' is entered, 
 the program will close.
*/

#include <iostream>
#include "runway.h"

using namespace std;
int main()
{
    runway begin;
    
    begin.runSim();

    return 0;
}
