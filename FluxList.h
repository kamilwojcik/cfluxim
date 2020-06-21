#ifndef FLUXLIST_H
#define FLUXLIST_H

#include <cmath>
#include <string>

#include "TH1D.h"
#include "TH2D.h"


using namespace std;


double SolidAngle(double thetaMin, double thetaMax, double dPhi); //radians!
    

class FluxList
{
    TH1D * fluxVsTheta; //theta in radians - given
    TH2D * NppsPhiTheta; // N particles per second
    //from solid angle (theta + dTheta, phi + dPi) 
    // - generated
    
    //area, area slope (theta), normal vec phi angle 
    double area; //[m^2]
    double areaTheta, areaPhi; //radians
    
    int thetaNbins, phiNbins;
    
    int PID;
    
    bool areaReady, fluxHistoReady, recalcNeeded;
    
    void BasicDefaultSetup();
    void CalculateNpps();
    
public:
    void SetArea(double Area=1, double AreaSlope=0, double AreaPhi=0);
    void SetPID(int id=0);
    void SetFluxVsThetaHisto(TH1D * fluxh);
    
    TH2D * GetNppsPhiTheta();
    bool IsReady();
    
    bool Recalculate();
    
    void Print();
    void Save();
    
    FluxList();
    FluxList(TH1D * fluxh, double a=1, double aTheta=0, double aPhi=0, int id=0);
};


#endif
