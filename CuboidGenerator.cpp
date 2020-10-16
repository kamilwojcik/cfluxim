#include "classes/Coords.h"
#include "classes/Momentum.h"
#include "classes/Particle.h"
#include "classes/ParticleGenerator.h"
#include "classes/FluxList.h"
#include "classes/Plane.h"
#include "classes/Rectangle.h"
#include "classes/Disk.h"
#include "classes/Cylinder.h"

#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TRandom3.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>


//////////////////////////////////////////////////////////////////
// CuboidGenerator - cosmic ray particle generator
//
// Particles of cosmic radiation are generated on the walls
// of the cuboid regarding angular and energy distributions
// of a real cosmic ray.
//
// Cube size: a x b x h  [m]
//
// UP:
//                          Y  ^ 
//                             | wall1
// p1up(-a/2 ,b/2, h)__________|__________ p2up(a/2, b/2, h)
//                  |          |          |
//                  |          |          |
//            wall4 |  ceiling |          | wall2
//                  |          |Z         |
//               ---|----------+----------|--->
//                  |          |          |   X
//                  |          |          |
//                  |          |          |
//                  |__________|__________|
// p4up(-a/2, -b/2, h)         | wall3     p3up(a/2, -b/2, h)
//                             |
//
//
// SIDE:
//                           Z  ^      
//                              | ceiling
// p3up(a/2, -b/2, h) __________|__________ p2up(a/2, b/2, h)
//                   |          |          |
//                   |          |          |
//                   |          |          |
//             wall3 |    wall2 |          | wall1
//                   |          |          |
//                   |          |          |
//                   |          |          |
//               ____|__________|__________|_____> Y
// p3down(a/2, -b/2, 0)         X           p2down(a/2, b/2, 0)
//
//

#define PItimes2 6.2831853
#define PIover2 1.5707963
#define PI 3.1415927

#define SIM_TIME 3600 //seconds

int main (int argc, char * argv[])
{
    Coords p1up(-4,4,8);
    Coords p2up(4,4,8);
    Coords p3up(4,-4,8);
    Coords p4up(-4,-4,8);
    
    Coords p1down(-4,4,0);
    Coords p2down(4,4,0);
    Coords p3down(4,-4,0);
    Coords p4down(-4,-4,0);
    
    Rectangle *wall[5];
    wall[0] = new Rectangle(p1up, p2up, p3up, p4up);
    wall[1] = new Rectangle(p2up, p1up, p1down, p2down);
    wall[2] = new Rectangle(p3up, p2up, p2down, p3down);
    wall[3] = new Rectangle(p4up, p3up, p3down, p4down);
    wall[4] = new Rectangle(p1up, p4up, p4down, p1down);
    string wallName[5] = {"ceiling", "wall1", "wall2", "wall3", "wall4"};
    
    for (int wallID=0; wallID<5; wallID++)
    {
        cout<<"\n"<<wallName[wallID]<<endl;
        wall[wallID]->Print();
        cout<<endl;
    }
    
    /////////////////////////////////////////////////////
    //TFile and TTree setup
    
    TFile outFile("cosmicCube.root", "RECREATE");
    
    // variables as an interface to populate the tree
    int PID; 
    int wallID;
    float posX, posY, posZ;
    float px, py, pz;
    float pr, ptheta, pphi;
    Particle particle;
    
    TTree tree("CosmicCube", "CosmicCube");
    
    tree.Branch("PID",&PID);
    tree.Branch("wallID",&wallID);
    
    tree.Branch("posX",&posX);
    tree.Branch("posY",&posY);
    tree.Branch("posZ",&posZ);
    tree.Branch("px",&px);
    tree.Branch("py",&py);
    tree.Branch("pz",&pz);
    tree.Branch("pr",&pr);
    tree.Branch("ptheta",&ptheta);
    tree.Branch("pphi",&pphi);    
    
    /////////////////////////////////////////////////////
    //Loading flux and momentum distriutions
    
    TFile * file= TFile::Open("flux_config/uMomentumIntegral.root");
    file->Print();
    TF1 * uMomIntegral= (TF1*)file->Get("uMomentumIntegral");
    
    file = TFile::Open("flux_config/uFluxTheta.root");
    file->Print();
    TH1D * uFluxTheta= (TH1D*)file->Get("uFluxTheta");
    
    
    /////////////////////////////////////////////////////
    //ParticleGenerator common setup

    ParticleGenerator pgen;
    pgen.SetPID(0);
    pgen.SetAreaXYSize(8,8);
    pgen.SetMomentumQuantileFunction(uMomIntegral);
    
    /////////////////////////////////////////////////////
    //FluxList common setup
    
    FluxList flist;
    flist.SetFluxVsThetaHisto(uFluxTheta);
    
    /////////////////////////////////////////////////////
    //Other
    TRandom3 rng(time(NULL)+10);

    
    /////////////////////////////////////////////////////
    // setting up loop over walls
    
    string fluxMapName[] = {"CeilingFluxMap", "Wall1FluxMap", "Wall2FluxMap", "Wall3FluxMap", "Wall4FluxMap"};
    double flistAreaSlope[] = {0, PIover2, PIover2, PIover2, PIover2};
    double flistAreaPhi[] = {0 ,PIover2, 0, -PIover2, PI};
    double wallArea=64;
    TH2D * fluxmap;
    
    
    for (wallID=0; wallID<5; wallID++)
    {
        flist.SetArea(wallArea, flistAreaSlope[wallID], flistAreaPhi[wallID]);
        flist.Print();
        flist.Recalculate();
        flist.Save(fluxMapName[wallID]);
        fluxmap=flist.GetNppsPhiTheta();
    
        int nBinsPhi=fluxmap->GetNbinsX();
        int nBinsTheta=fluxmap->GetNbinsY();
    
        for (int i=1; i<=nBinsPhi; i++)
        {
            double phiMin = PI+fluxmap->GetXaxis()->GetBinLowEdge(i);
            double phiMax = PI+fluxmap->GetXaxis()->GetBinUpEdge(i);
            if (phiMin >= PItimes2) 
            {
                phiMax = phiMax - PItimes2;
                phiMin = phiMin - PItimes2;
            }
            
            pgen.SetPhiRange(phiMin, phiMax);
        
            for (int j=1; j<=nBinsTheta; j++)
            {
                pgen.SetThetaRange(PI -fluxmap->GetYaxis()->GetBinUpEdge(j), PI - fluxmap->GetYaxis()->GetBinLowEdge(j));
            
                //////////////////////////////////
                // randomize non-integer part of number of particles:
                // rounding up probability is proportional to the non-integer part
            
                double nparticles=fluxmap->GetBinContent(i,j)*SIM_TIME;
                double noninteger = nparticles - floor(nparticles);
            
                double rndm=rng.Rndm();
                if ( rndm < noninteger ) nparticles = floor( nparticles + 1. );
                else nparticles = floor (nparticles);
            
                for (int n=0; n<nparticles; n++)
                {
                    cout<<wallName[wallID]<<" i="<<i<<" j="<<j<<" n="<<n<<"\r"<<flush;
                
                    particle=pgen.GetRandomParticle();
                    particle.SetPosition(wall[wallID]->RelativeToAbsolute(particle.GetPosition()));
                
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
                }
            
            }
        }
    }
    
    tree.Print();
    outFile.Write();
    outFile.Close();
    
    return 0;
}
