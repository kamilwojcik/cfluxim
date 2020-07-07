#!/bin/bash


g++ Coords.cpp Particle.cpp Momentum.cpp Plane.cpp Rectangle.cpp Disk.cpp Cylinder.cpp FluxList.cpp RNGQuantile.cpp ParticleGenerator.cpp cfluxim.cpp -o cfluxim -std=c++11 -pthread -O2 -m64 -I/home/dane/soft/root6/build/include/ -L/home/dane/soft/root6/build/lib/ -lGui -lCore -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic

