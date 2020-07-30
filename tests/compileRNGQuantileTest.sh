#!/bin/bash

#compilation arguments

g++ ../classes/RNGQuantile.cpp RNGQuantileTest.cpp -o testRNGQuantile `root-config --cflags --libs`


