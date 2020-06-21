#include "FluxList.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TAxis.h"
#include "TCanvas.h"
#include <cmath>
#include <iostream>

#define PItimes2 6.2831853
#define PIover2 1.5707963
#define PI 3.1415927

using namespace std;


double SolidAngle(double thetaMin, double thetaMax, double dPhi)
{
    double fullPhi = ( PItimes2 * (1 - cos(thetaMax)) ) - ( PItimes2 * (1 - cos(thetaMin)) );
    double solidAngle = fullPhi * dPhi/PItimes2;
    
    return solidAngle;
}

void FluxList::CalculateNpps()
{
    int phiNbins;
    double phiMin, phiMax;
    
    if (areaTheta == 0 or areaTheta == PI)
    {
        phiNbins=36;
        phiMin=areaPhi-PI;
        phiMax=areaPhi+PI;
    }
    else
    {
        phiNbins=18;
        phiMin = areaPhi - PIover2;
        phiMax = areaPhi + PIover2;
    }
    double dPhi = (phiMax-phiMin) / (double)phiNbins;
    double thetaMin = fluxVsTheta->GetXaxis()->GetXmin();
    double dTheta = fluxVsTheta->GetBinWidth(1);
    
    int thetaNbins=fluxVsTheta->GetNbinsX();
    
    cout<<"PhiMin="<<phiMin<<endl;
    
    double npps_ij;
    cout<<"Mark!"<<endl;
    NppsPhiTheta = new TH2D("NppsPhiTheta", "NppsPhiTheta",phiNbins, phiMin, phiMax, thetaNbins, 0, PIover2);
    NppsPhiTheta->GetXaxis()->SetTitle("phi [rad]");
    NppsPhiTheta->GetYaxis()->SetTitle("theta [rad]");
    
    for (double phi_i=phiMin; phi_i<phiMax; phi_i+=dPhi)
        for (int j=1; j<=thetaNbins; j++)
        {
            cout<<"phi_i: "<<phi_i<<"  j: "<<j<<endl;
            npps_ij=fluxVsTheta->GetBinContent(j) * SolidAngle(thetaMin, thetaMin+dTheta, dPhi) * area * cos((thetaMin + j*dTheta) - areaTheta) * cos(phi_i - areaPhi);
            NppsPhiTheta->Fill(phi_i, thetaMin + (j-1)*dTheta , npps_ij);
        }
    recalcNeeded=false;
    
    return;
}

void FluxList::BasicDefaultSetup()
{
    area=1; //[m]
    areaTheta=0; //[rad]
    areaPhi=0; //[rad]
    PID=0;
    areaReady=true;
    recalcNeeded=true;
    
    return;
}


void FluxList::SetArea(double a, double aTheta, double aPhi)
{
    area=a;
    areaTheta=aTheta;
    areaPhi=aPhi;
    areaReady=true;
    recalcNeeded=true;
    
    return;
}


void FluxList::SetPID(int id)
{
    PID=id;
    
    return;
}

void FluxList::SetFluxVsThetaHisto(TH1D * fluxh)
{
    fluxVsTheta=fluxh;
    fluxHistoReady=true;
    recalcNeeded=true;
    
    return;
}

bool FluxList::Recalculate()
{
    if (fluxHistoReady && areaReady)
    {
        CalculateNpps();
        return true;
    }
    else return false;
}

bool FluxList::IsReady()
{
    return fluxHistoReady && areaReady && !recalcNeeded;
}

void FluxList::Print()
{
    if (fluxHistoReady && areaReady && recalcNeeded) CalculateNpps();
    
    cout<<"----Partial Flux----"<<endl;
    cout<<"Flux histogram is set: ";
    if (fluxHistoReady) cout<<"true."<<endl;
    else cout<<"false. FluxList not ready!"<<endl;
    cout<<"Area: "<<area<<" [m^2], slope (theta): "<<areaTheta<<" [rad], phi: "<<areaPhi<<" [rad]"<<endl;
    cout<<"PID: "<<PID<<endl;
    
    return;
}


void FluxList::Save()
{
    NppsPhiTheta->SaveAs("NppsPhiTheta.root");
    TCanvas *cnv = new TCanvas();
    cnv->cd();
    NppsPhiTheta->Draw("Colz");
    cnv->SaveAs("NppsPhiTheta.png");
    delete cnv;
    return;
}

FluxList::FluxList()
{
    fluxHistoReady=false;
    BasicDefaultSetup();
}

FluxList::FluxList(TH1D * fluxh, double a, double aTheta, double aPhi, int id)
{
    SetFluxVsThetaHisto(fluxh);
    SetArea(a, aTheta, aPhi);
    SetPID(id);
    
    CalculateNpps();
}


