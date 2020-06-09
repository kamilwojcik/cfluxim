#ifndef PARTIALFLUX_H
#define PARTIALFLUX_H

#include <cmath>
#include <string>

#define PItimes2 6.2831853
#define PIover2 1.5707963

using namespace std;


class PartialFlux
{
    double thetaMin, thetaMax; //radians
    double phiMin, phiMax; //radians
    double solidAngle; //steradians
    double area; //[m^2]
    double areaSlope; //radians
    double time; //[seconds]
    string cumulDistFilename;
    
    double fluxValue; //[ n / second^-1 meter^-2 steradian^-1 ]
    double particlesPerSecond;
    int Nofparticles;
    int PID;
    
    bool recalcNeeded;
    
    void CalculateSolidAngle();
    void CalculateNParticles();
        
public:
    void SetThetaRange(double theta_min=0, double theta_max=PIover2); //0 -- Pi/2
    void SetPhiRange(double phi_min=0, double phi_max=PItimes2); //0 -- 2Pi
    void SetArea(double Area=1, double AreaSlope=0);
    void SetFluxValue(double fluxValue=1);
    void SetTimeInSec(double sec=1000);
    void SetTimeInHours(double h=1);
    void SetPID(int id=0);
    void SetCumulDistFilename(string filename="NOT_SET");
    
    double GetParticlesPerSecond();
    int GetNofParticles();
    
    void Print();
    
    PartialFlux();
};


#endif
