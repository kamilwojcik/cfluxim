#!/bin/bash

g++ ../FluxList.cpp FluxListTest.cpp -o testFluxList -std=c++14 -pthread -O2 -m64 -I/home/dane/soft/root6/build/include/ -L/home/dane/soft/root6/build/lib/ -lGui -lCore -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic
