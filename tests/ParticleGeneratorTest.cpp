#include "../cfluxim.h"
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TFile.h"

#define PI 3.14159265

using namespace std;

int main(void)
{
    ParticleGenerator pGen;
    pGen.Print();
    pGen.SetDescription("Test");
    pGen.Print();
    
    pGen.SetThetaRange(0.1,0.3);
    pGen.Print();
    
    pGen.GetRandomParticle();
    
    TFile * file= TFile::Open("hQuantile.root");
    cout<<"OpenQuantileFile: "<<"hQuantile.root"<<endl;
    file->Print();
    
    TH1D * quantileHisto= (TH1D*)file->Get("hMuMom");
    
    pGen.SetMomentumQuantileHisto(quantileHisto);
    pGen.Print();
    
    cout<<"\nLosowanie: \n"<<endl;
    
    pGen.GetRandomParticle();
    pGen.Print();
    pGen.GetRandomParticle();
    pGen.Print();
    
    ////////////////////////
    cout<<"A warning should appear:"<<endl;
    pGen.GetParticle().GetPosition(3);
    
    /////////////////////////////////////
    //distributions
    
    pGen.ResetDistribution();
    
    TH2D posXY("posXY","posXY",100,0,1,100,0,1);
    TH1D theta("theta","theta",100,0,PI);
    TH1D phi("phi","phi",100,0,2.*PI);
    Particle particle;
    
    
    for (int i=0; i<100000; i++)
    {
        particle=pGen.GetRandomParticle();
        posXY.Fill(particle.GetPosition(0),particle.GetPosition(1));
        theta.Fill(particle.GetMomentum().GetSpherical()[1]);
        phi.Fill(particle.GetMomentum().GetSpherical()[2]);
    }
    
    TCanvas * cn=new TCanvas;
    cn->cd();
    posXY.Draw("Colz");
    cn->SaveAs("posXY.png");
    theta.Draw();
    cn->SaveAs("theta.png");
    phi.Draw();
    cn->SaveAs("phi.png");
    delete cn;

    pGen.SaveDistributionPng("PmagTestPartGen.png");
    
    return 0;
}
