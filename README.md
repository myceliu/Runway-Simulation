# Runway-Simulation
=---------------------Airport Runway Simulator----------------------=

The airport runway simulator is a C++ program that simulates several landings and takeoffs and an airport. It is intented to determine the efficiency of a single runway airport operating under a specific set of conditions.

These conditions are:
1. Number of turns
2. Rate of airplanes coming in for landing
3. Rate of airplanes coming in for takeoff
4. Amount of turns needed for a landing to complete
5. Amount of turns needed for a takeoff to complete

Turns can be interpreted as the amount of time the runway is open and how long a takeoff or landing takes, it is just arbitrarily referred to as turns for simplicity.

The simulator does not account for extreme weather conditions, pilot errors, and other disasters that could occur during takeoff or landing. It assumes that all ideal conditions are present.

Upon starting, the program will ask the user a series of questions. All numbers should be given as whole numbers, except for the rate of landings and takeoffs. These numbers should be a number between 0 and 1.

After the numbers are given, the program will execute and then provide a report of the simulation. It will then ask the user if they want to run another simulation. Enter 'y' to continue, or 'n' to exit the program.

--Input example: (user input is in quotations)

Enter simulator data:

Total amount of turns the simulation should last: "75"

Rate of aircraft landings: "0.2"

Rate of aircraft takeoffs: "0.6"

Amount of turns needed for a landing to finish: "10"

Amount of turns needed for a takeoff to finish: "10"

--

The program will run for 75 turns. The airport will have a landing rate of 20% and a takeoff rate of 60%. Each plane will take 10 turns to finish a landing or to finish a takeoff.
