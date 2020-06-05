#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <iostream>
#include <string>

#include "TRandom3.h"

#include "Particle.h"
#include "RNGQuantile.h"


class ParticleGenerator
{
    Particle particle;
    RNGQuantile rngq;
    TRandom3 * rng_uniform;
    double thetaMin, thetaMax;
    double phiMin, phiMax
    
    void OpenMomentumMagnitudeQuantile()
    
    void setThetaRange(double theta_min=0, double theta_max=1.57080); // theta_max = Pi/2 [radians]
    void setPhiRange(double phi_min=0, double theta_max=6.28319); //phi_max = Pi*2 [radians]
    
    Particle GetRandomParticle();
    Particle& GetParticle();
    
    
    
private:
    
    void RollTheDice();
    
    
};

















#endif
