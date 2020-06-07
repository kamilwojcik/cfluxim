#include "../cfluxim.h"
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

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
    
    pGen.OpenQuantileFile("hQuantile.root");
    pGen.Print();
    
    cout<<"\nLosowanie: \n"<<endl;
    
    pGen.GetRandomParticle();
    pGen.Print();
    pGen.GetRandomParticle();
    pGen.Print();
    
    ////////////////////////
    pGen.GetParticle().GetPosition(3);
    
    /////////////////////////////////////
    //distributions
    
    pGen.ResetDistribution();
    
    TH2D posXY("posXY","posXY",100,0,1,100,0,1);
    TH1D theta("theta","theta",100,0,PI);
    TH1D phi("phi","phi",100,0,2.*PI);
    Particle particle;
    
    
    for (int i=0; i<10000; i++)
    {
        particle=pGen.GetRandomParticle();
        posXY.Fill(particle.GetPosition(0),particle.GetPosition(1));
        theta.Fill(particle.GetMomentum().GetPolar()[1]);
        phi.Fill(particle.GetMomentum().GetPolar()[2]);
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
