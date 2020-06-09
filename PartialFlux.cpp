#include "PartialFlux.h"
#include <cmath>
#include <string>
#include <iostream>

#define PItimes2 6.2831853
#define PIover2 1.5707963

using namespace std;


void PartialFlux::CalculateSolidAngle()
{
    double fullPhi = ( PItimes2 * (1 - cos(thetaMax)) ) - ( PItimes2 * (1 - cos(thetaMin)) );
    solidAngle = fullPhi * abs(phiMax-phiMin)/PItimes2;
    
    return;
}

void PartialFlux::CalculateNParticles()
{
    CalculateSolidAngle();
    
    particlesPerSecond= fluxValue * solidAngle * area * cos(thetaMin);// * cos(areaSlope-thetaMin); WRONG!! d^2PHI / dphi dtetha needed!
    Nofparticles=round(particlesPerSecond * time);
    
    return;
}

void PartialFlux::SetThetaRange(double theta_min, double theta_max)
{
    thetaMin=theta_min;
    thetaMax=theta_max;
    recalcNeeded=true;
    
    return;
}

void PartialFlux::SetPhiRange(double phi_min, double phi_max)
{
    phiMin=phi_min;
    phiMax=phi_max;
    recalcNeeded=true;
    
    return;
}

void PartialFlux::SetArea(double a, double aSlope)
{
    area=a;
    areaSlope=aSlope;
    recalcNeeded=true;
    
    return;
}


void PartialFlux::SetFluxValue(double flux_value)
{
    fluxValue=flux_value;
    recalcNeeded=true;
        
    return;
}

void PartialFlux::SetTimeInSec(double sec)
{
    time=sec;
    recalcNeeded=true;
    
    return;
}

void PartialFlux::SetTimeInHours(double h)
{
    time=h*3600.;
    recalcNeeded=true;
    
    return;
}

void PartialFlux::SetPID(int id)
{
    PID=id;
    
    return;
}

void PartialFlux::SetCumulDistFilename(string filename)
{
    cumulDistFilename=filename;
    
    return;
}


double PartialFlux::GetParticlesPerSecond()
{
    if (recalcNeeded) CalculateNParticles();
    
    return particlesPerSecond;
}

int PartialFlux::GetNofParticles()
{
    if (recalcNeeded) CalculateNParticles();
    
    return Nofparticles;
}


void PartialFlux::Print()
{
    if (recalcNeeded) CalculateNParticles();
    
    cout<<"----Partial Flux----"<<endl;
    cout<<"Cumulative distribution of momentum - filename: "<<cumulDistFilename<<endl;
    cout<<"Zenith angle (theta) range: ( "<<thetaMin<<" ; "<<thetaMax<<" ) [rad]"<<endl;
    cout<<"Phi range: ( "<<phiMin<<" ; "<<phiMax<<" ) [rad]"<<endl;
    cout<<"Solid angle: "<<solidAngle<<" [sr]"<<endl;
    cout<<"PID: "<<PID<<"  flux value: "<<fluxValue<<" [n / s^-1 m^-2 sr^-1]"<<endl;
    cout<<"Area: "<<area<<" [m^2], slope: "<<areaSlope<<" [rad]"<<endl;
    cout<<"time: "<<time<<" [s], particles per second: "<<particlesPerSecond<<endl;
    cout<<"N of particles in the given time period: "<<Nofparticles<<endl;
    
    return;
}

PartialFlux::PartialFlux()
{
    SetFluxValue();
    SetPhiRange();
    SetThetaRange();
    SetArea();
    SetTimeInSec();
    SetPID();
    SetCumulDistFilename();
    CalculateNParticles();
}


