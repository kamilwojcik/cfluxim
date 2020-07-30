#!/bin/bash


g++ classes/Coords.cpp classes/Particle.cpp classes/Momentum.cpp classes/Plane.cpp classes/Rectangle.cpp classes/FluxList.cpp FluxAnalyzer.cpp -o FluxAnalyzer `root-config --cflags --libs`

