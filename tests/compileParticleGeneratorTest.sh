#!/bin/bash

#compilation arguments

g++ ../classes/ParticleGenerator.cpp ../classes/RNGQuantile.cpp ../classes/Particle.cpp ../classes/Momentum.cpp ../classes/Coords.cpp ParticleGeneratorTest.cpp -o testParticleGenerator `root-config --cflags --libs`
