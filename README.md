# 🧮 Monte Carlo Integration

The simulation repeatedly randomizes samples within a uniform range of a to b for an integral.

This Project also utilizes OpenMP, which allows it to have very efficient multithreading performance on this task.

I also wanted to make this library user friendly for simple projects, so included is sample code in main.cpp and a makefile that builds this project, utilizing the integration backend for
functions is as easy as setting up your equations in a STL Vector, and giving extra parameters if you are using optional features, and it will work within your project!

# 🧰 Features

This Project Features
  - OpenMP for Threading
  - Monte Carlo Simulation Technique
  - Object Orented Abstraction for ease of use in other projects
  - Trigonometric functions
  - Polynomial Functions

In Future, I'd like to add
  - Exponential Functions
  - Derivation via Monte Carlo

# 🛠️ Usage
The Makefile included in this project builds the main into an executable with simple tests to show syntax.
This is meant to be used as a library used in other projects, it is NOT thread safe, as it uses OpenMP Internally
do to integration.


# 📫 Contact

If you use this code for a project or classroom work, let me know — I’d love to hear about it!

