#!/bin/bash

#compilation arguments

g++ ParticleGenerator.cpp RNGQuantile.cpp Particle.cpp Momentum.cpp Coords.cpp particleGenTest.cpp -o particleGenTest -std=c++14 -pthread -O2 -m64 -I/home/dane/soft/root6/build/include/ -L/home/dane/soft/root6/build/lib/ -lGui -lCore -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic

