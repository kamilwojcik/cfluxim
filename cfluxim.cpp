#include "Coords.h"
#include "Momentum.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "FluxList.h"
#include "Plane.h"
#include "Rectangle.h"

#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"

#include <iostream>
#include <string>


/////////////////////////////////////////////
// CUBE particle generator
//
// Cube size: 4x4x4 m
//
// UP:
//                      Y  ^ 
//                         | wall2
//  p2up(-2,2,4) __________|__________ p1up(2,2,4)
//              |          |          |
//              |          |          |
//        wall3 |  ceiling |          | wall1
//              |          |Z         |
//           ---|----------+----------|--->
//              |          |          |   X
//              |          |          |
//              |          |          |
//              |__________|__________|
// p3up(-2,-2,4)           | wall4     p4up(2,-2,4)
//                         |
//
//
// SIDE:
//                      Z  ^      
//                         | ceiling
//  p4up(2,-2,4) __________|__________ p1up(2,2,4)
//              |          |          |
//              |          |          |
//              |          |          |
//        wall4 |    wall1 |          | wall2
//              |          |          |
//              |          |          |
//              |          |          |
//          ____|__________|__________|_____> Y
//  p4down(2,-2,0)         X           p1down(2,2,0)
//
//

#define PI 3.1415927
#define SIM_TIME 1000 //seconds

int main (int argc, char * argv[])
{
    Coords p1up(2,2,4);
    Coords p2up(-2,2,4);
    Coords p3up(-2,-2,4);
    Coords p4up(2,-2,4);
    
    Coords p1down(2,2,0);
    Coords p2down(-2,2,0);
    Coords p3down(-2,-2,0);
    Coords p4down(2,-2,0);
    
    Rectangle ceiling(p2up, p4up);
    Rectangle wall1(p4up, p1down);
    Rectangle wall2(p1up, p2down);
    Rectangle wall3(p2up, p3down);
    Rectangle wall4(p3up, p4down);
    
    wall3.SetNormalVecDirection(false);
    wall4.SetNormalVecDirection(false);
    
    p1up.Print();
    p2up.Print();
    p3up.Print();
    p4up.Print();
    
    cout<<"\nCeiling:"<<endl;
    ceiling.Print();
    cout<<"\nWall1:"<<endl;
    wall1.Print();
    cout<<"\nWall2:"<<endl;
    wall2.Print();
    cout<<"\nWall3:"<<endl;
    wall3.Print();
    cout<<"\nWall3:"<<endl;
    wall4.Print();
    
    /////////////////////////////////////////////////////
    // TTree setup
    
    // variables as an interface to populate the tree
    int PID;
    double posX, posY, posZ;
    double px, py, pz;
    double pr, ptheta, pphi;
    Particle particle;
    
    TTree tree("CosmicCube", "CosmicCube");
    tree.Branch("PID",&PID);
    tree.Branch("posX",&posX);
    tree.Branch("posY",&posY);
    tree.Branch("posZ",&posZ);
    tree.Branch("px",&px);
    tree.Branch("py",&py);
    tree.Branch("pz",&pz);
    tree.Branch("pr",&pr);
    tree.Branch("ptheta",&ptheta);
    tree.Branch("pphi",&pphi);
    
    //tree.Fill();
    
    
    /////////////////////////////////////////////////////
    //Loading flux and momentum distriutions
    
    TFile * file= TFile::Open("hMuMom.root");
    file->Print();
    TH1D * hMuMom= (TH1D*)file->Get("hMuMom");
    
    file = TFile::Open("uFluxTheta.root");
    file->Print();
    TH1D * uFluxTheta= (TH1D*)file->Get("uFluxTheta");
    
    
    /////////////////////////////////////////////////////
    //ParticleGenerator common setup

    ParticleGenerator pgen;
    pgen.SetPID(0);
    pgen.SetAreaXYSize(4,4);
    pgen.SetMomentumQuantileHisto(hMuMom);
    
    /////////////////////////////////////////////////////
    //FluxList common setup
    
    FluxList flist;
    flist.SetFluxVsThetaHisto(uFluxTheta);
    
    /////////////////////////////////////////////////////
    // Ceiling
    
    TH2D * fluxmap;
    
    flist.SetArea(16,0,0);
    flist.Print();
    flist.Recalculate();
    flist.Save("CeilingFluxMap");
    fluxmap=flist.GetNppsPhiTheta();
    
    int nBinsPhi=fluxmap->GetNbinsX();
    int nBinsTheta=fluxmap->GetNbinsY();
    
    for (int i=1; i<=nBinsPhi; i++)
    {
        pgen.SetPhiRange(fluxmap->GetXaxis()->GetBinLowEdge(i), fluxmap->GetXaxis()->GetBinUpEdge(i));
        
        for (int j=1; j<=nBinsTheta; j++)
        {
            pgen.SetThetaRange(PI -fluxmap->GetYaxis()->GetBinUpEdge(j), PI - fluxmap->GetYaxis()->GetBinLowEdge(j));
            
            for (int n=0; n<(fluxmap->GetBinContent(i,j)*SIM_TIME); n++)
            {
                particle=pgen.GetRandomParticle();
                particle.SetPosition(ceiling.RelativeToAbsolute(particle.GetPosition()));
                
                posX=particle.GetPosition()[0];
                posY=particle.GetPosition()[1];
                posZ=particle.GetPosition()[2];
                
                px=particle.GetMomentum().GetCarthesian()[0];
                py=particle.GetMomentum().GetCarthesian()[1];
                pz=particle.GetMomentum().GetCarthesian()[2];
                
                pr=particle.GetMomentum().GetSpherical()[0];
                ptheta=particle.GetMomentum().GetSpherical()[1];
                pphi=particle.GetMomentum().GetSpherical()[2];
                
                PID=particle.GetPID();
                
                tree.Fill();
                cout<<"Ceiling: i="<<i<<" j="<<j<<" n="<<n<<"\r"<<flush;
            }
            
        }
    }
    TFile outFile("cosmicCube.root", "RECREATE");
    tree.Print();
    tree.Write();
    outFile.Close();
    
    return 0;
}
