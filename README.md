# Simple Particle System
This is a Particle System Demo I made for OpenGL. This code was also used for the laboratory lessons of Computer Graphics in University of Patras while I was teaching there and was created to enrich the course.

This particle system can accept any geometry as the basis for the particle emitter, supports complete 6-DOF control of each particle, as well as transparency (although at a big performance hit).

The architecture consists of an interface class which is intended to be used as a basis for creation of a concrete particle emitter class. The interface completely encapsulates all the ugly OpenGL code and makes the manipulation of particles completely OpenGL-code free. 

The source code in the lab08 folder also serves as a demo for demonstrating two example emitters (a FountainEmitter and an OrbitEmitter) and for comparing performances with a non-instance based rendering to showcase its advantages for particle rendering.

## Dependencies
The project is completely protable, so only the absolute basics are needed:
1. CMake
2. C++ Compiler (preferably supporting C++17 for some features to be enabled)
3. OpenGL support (barely worth mentioning)

![plot](https://media.giphy.com/media/cjZIzDNstBUcD9mxpc/giphy-downsized.gif)


[source_gif with slightly higher quality](https://media.giphy.com/media/cjZIzDNstBUcD9mxpc/giphy.gif)
