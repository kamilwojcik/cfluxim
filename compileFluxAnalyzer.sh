#!/bin/bash


g++ classes/Coords.cpp classes/Particle.cpp classes/Momentum.cpp classes/Plane.cpp classes/Rectangle.cpp classes/Disk.cpp classes/Cylinder.cpp classes/FluxList.cpp classes/RNGQuantile.cpp classes/ParticleGenerator.cpp classes/FluxAnalyzer.cpp -o FluxAnalyzer -std=c++11 -pthread -O2 -m64 -I/home/dane/soft/root6/build/include/ -L/home/dane/soft/root6/build/lib/ -lGui -lCore -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic

