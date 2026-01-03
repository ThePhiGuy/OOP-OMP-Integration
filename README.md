# Monte Carlo Integration

The simulation repeatedly randomizes samples within a uniform range of a to b for an integral.

This Project also utilizes OpenMP, which allows it to have very efficient multithreading performance on this task.

I also wanted to make this library user friendly for simple projects, so included is sample code in main.cpp and a makefile that builds this project, utilizing the integration backend for
functions is as easy as setting up your equations in a STL Vector, and giving extra parameters if you are using optional features, and it will work within your project!

# Features

This Project Features
  - OpenMP for Local Threading
  - Monte Carlo Simulation Technique
  - Object Orented Abstraction for ease of use in other projects
  - Trigonometric functions
  - Polynomial Functions

In Future, I'd like to add
  - Exponential Functions
  - Derivation via Monte Carlo

# Usage
Use the Makefile included in this project to build the required executable.

Run the simulation with 

> mpirun -np (processes) ./Birthday (outputType) (matches) (trials) (runs) (maxGroupSize) (minGroupSize) (birthdayResolution)

The optional parameters are
  - outputType : currently supported is 0 (or no optional parameters) for default command line output, and 1 being CSV output. 
  - matches : the size of the matches you are looking for, the birthday problem generally utilizes 2, indicating two people with the same birthday.
  - trials : the number of monte carlo simulated trials, similar to a resolution for the accuracy of the answers.
  - runs : the amount of division between the minimum and maximum group size, should not exceed max-min group size.
  - maxGroupSize : the largest group size tested.
  - minGroupSize : the smallest group size tested.
  - birthdayResolution : the parameter for the number of birthday options, 365 represents once a day, but you can simulate with birth day and year, or even year day and hour.


# 📫 Contact

If you use this code for a project or classroom work, let me know — I’d love to hear about it!

