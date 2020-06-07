#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <iostream>
#include <string>

#include "TRandom3.h"

#include "Particle.h"
#include "RNGQuantile.h"


class ParticleGenerator : public RNGQuantile
{
    Particle particle;
    double thetaMin, thetaMax;
    double phiMin, phiMax;
    double areaWidth, areaHeight;
    
    void RollTheDice(); //all random generators does the thing to obtain all the needed parameters

    //using RNGQuantile::GetRandom(); //this one pethod of RNGQuantile should be hidden
    
public:
    
    void SetPID(int id=0);
    
    //solid angle definition
    void SetThetaRange(double theta_min=0, double theta_max=1.57080); // theta_max = Pi/2 [radians]
    void SetPhiRange(double phi_min=0, double phi_max=6.28319); //phi_max = Pi*2 [radians]
    
    //area dimenstions definition
    void SetAreaXYSize(double x=1, double y=1); // [meters]
    
    Particle& GetRandomParticle();
    Particle& GetParticle();
    
    void Print();
    
    ParticleGenerator();
};





#endif
