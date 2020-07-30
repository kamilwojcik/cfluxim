#!/bin/bash

g++ ../classes/FluxList.cpp FluxListTest.cpp -o testFluxList `root-config --cflags --libs`
