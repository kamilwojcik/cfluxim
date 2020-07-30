#!/bin/bash


g++ classes/Coords.cpp classes/Particle.cpp classes/Momentum.cpp classes/Plane.cpp classes/Rectangle.cpp classes/FluxList.cpp classes/RNGQuantile.cpp classes/ParticleGenerator.cpp CuboidGenerator.cpp -o CuboidGenerator `root-config --cflags --libs`

