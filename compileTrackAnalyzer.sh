#!/bin/bash


g++ classes/Coords.cpp classes/Particle.cpp classes/Momentum.cpp classes/Plane.cpp classes/Rectangle.cpp classes/Disk.cpp classes/Cylinder.cpp classes/FluxList.cpp TrackAnalyzer.cpp -o TrackAnalyzer `root-config --cflags --libs`
