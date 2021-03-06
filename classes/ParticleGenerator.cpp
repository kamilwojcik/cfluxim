#include <iostream>
#include <string>

#include "TRandom3.h"

#include "Particle.h"
#include "RNGQuantile.h"

#include "ParticleGenerator.h"


using namespace std;


void ParticleGenerator::RollTheDice()
{
    if (ready)
    {
        double r = RNGQuantile::GetRandom();
        double theta = (rng->Rndm()*(thetaMax-thetaMin))+thetaMin;
        double phi = rng->Rndm()*(phiMax-phiMin)+phiMin;
        particle.SetMomentum(r, theta, phi);
    
        particle.SetPosition(rng->Rndm()*areaWidth, rng->Rndm()*areaHeight, 0);
    }
    else cout<<"\nWARNING: unable to generate particle!\nQuantile not set! Use the SetQuantileFile(\"[filename.root]\") method to fix it.\n"<<endl;
}

//////////////////////////////////////////
//setup

void ParticleGenerator::SetPID(int id)
{
    particle.SetPID(id);
    
    return;
}

//solid angle definition
void ParticleGenerator::SetThetaRange(double theta_min, double theta_max) //[radians]
{
    thetaMin=theta_min;
    thetaMax=theta_max;
    
    return;
}

void ParticleGenerator::SetPhiRange(double phi_min, double phi_max) //[radians]
{
    phiMin=phi_min;
    phiMax=phi_max;
    
    return;
}

//area dimensions definition

void ParticleGenerator::SetAreaXYSize(double x, double y) // [meters]
{
    areaWidth=x;
    areaHeight=y;
    
    return;
}

////////////////////////////////////////
//get


Particle& ParticleGenerator::GetRandomParticle()  
{
    RollTheDice();
    
    return particle;
}


Particle& ParticleGenerator::GetParticle()
{
    return particle;
}


/////////////////////////////////////////////
//Print

void ParticleGenerator::Print()
{
    cout<<"+++++++++++++++++++++++++"<<endl;
    cout<<"Particle generator status"<<endl;
    RNGQuantile::Print();
    cout<<"Area: "<<areaWidth<<" x "<<areaHeight<<endl;
    cout<<"Theta range: ( "<<thetaMin<<" ; "<<thetaMax<<" )"<<endl;
    cout<<"Phi range: ( "<<phiMin<<" ; "<<phiMax<<" )"<<endl;
    
    cout<<"\nCurrent particle:"<<endl;
    particle.Print();
    cout<<"+++++++++++++++++++++++++"<<endl;
    return;
}


////////////////////////////////////////////
//Constructor

ParticleGenerator::ParticleGenerator()
{
    RNGQuantile();
    SetAreaXYSize();
    SetThetaRange();
    SetPhiRange();
}
