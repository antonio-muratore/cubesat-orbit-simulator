# CubeSat Orbit Simulator

A simple 3D orbital mechanics simulator I wrote for the PoliSpace 6S-CubeSat project application.

![Simulation](3Dsimulation.png)

## Implementation details

The project is split into two parts: a C backend for the physics engine and a Python script for the visualization.

For the physics engine, I calculated the orbital state vectors over time using Newton's law of universal gravitation. I decided to implement the semi-implicit Euler-Cromer method for numerical integration instead of a standard forward Euler. This was a necessary choice because Euler-Cromer conserves orbital energy much better, keeping the circular orbit stable without spiraling out over time. The C code then exports the computed trajectory to a raw .csv file.

To visualize the results, I wrote a quick Python script. It uses Pandas to read the csv data and Matplotlib (with mplot3d) to plot the 3D trajectory of the CubeSat around Earth.
