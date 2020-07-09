#include "Coords.h"
#include "Momentum.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "FluxList.h"
#include "Plane.h"
#include "Rectangle.h"
#include "Disk.h"
#include "Cylinder.h"

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

#define SIM_TIME 3600 //seconds, =1/2 hour

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
    
    Rectangle ceiling(p1up, p2up, p3up, p4up);
    Rectangle wall1(p2up, p1up, p1down, p2down);
    Rectangle wall2(p3up, p2up, p2down, p3down);
    Rectangle wall3(p4up, p3up, p3down, p4down);
    Rectangle wall4(p1up, p4up, p4down, p1down);
    
    cout<<"\nCeiling:"<<endl;
    ceiling.Print();
    
    cout<<"\nWall1:"<<endl;
    wall1.Print();
    cout<<"\nWall2:"<<endl;
    wall2.Print();
    cout<<"\nWall3:"<<endl;
    wall3.Print();
    cout<<"\nWall4:"<<endl;
    wall4.Print();
    
    
    /////////////////////////////////////////////////////
    TFile outFile("cosmicCube.root", "RECREATE");
    
    /////////////////////////////////////////////////////
    // TTree setup
    
    // variables as an interface to populate the tree
    int PID; 
    int wallID;
    float posX, posY, posZ;
    float px, py, pz;
    float pr, ptheta, pphi;
    Particle particle;
    
    TTree tree("CosmicCube", "CosmicCube");
    //tree.Branch("particle",&particle);
    
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
    pgen.SetAreaXYSize(8,8);
    pgen.SetMomentumQuantileHisto(hMuMom);
    
    /////////////////////////////////////////////////////
    //FluxList common setup
    
    FluxList flist;
    flist.SetFluxVsThetaHisto(uFluxTheta);
    
    /////////////////////////////////////////////////////
    //Other
    TRandom3 rng(time(NULL)+10);

    /////////////////////////////////////////////////////
    // Ceiling - wallID=0
    
    wallID=0;
    
    TH2D * fluxmap;
    
    flist.SetArea(64.0,0,0);
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
            
            
            //////////////////////////////////
            // randomize non-integer part of number of particles:
            // rounding up probability is proportional to the non-integer part
            
            double nparticles=fluxmap->GetBinContent(i,j)*SIM_TIME;
            double noninteger = nparticles - floor(nparticles);
            
            //cout<<"Nparticles="<<nparticles;
            double rndm=rng.Rndm();
            //cout<<" rndm="<<rndm;
            
            if ( rndm < noninteger )
            {
                nparticles = floor( nparticles + 1. );
                //cout<<"  rounded up: "<<nparticles<<endl;
            }
            else
            {
                nparticles = floor (nparticles);
                //cout<<"  rounded down: "<<nparticles<<endl;
            }
            
            for (int n=0; n<nparticles; n++)
            {
                cout<<"Ceiling: i="<<i<<" j="<<j<<" n="<<n<<"\r"<<flush;
                
                
                particle=pgen.GetRandomParticle();
                particle.SetPosition(ceiling.RelativeToAbsolute(particle.GetPosition()));
                
                posX=particle.GetPosition()[0];
                posY=particle.GetPosition()[1];
                posZ=particle.GetPosition()[2];
                
                //cout<<"pozX="<<posX<<" posY="<<posY<<" posZ="<<posZ<<endl;
                
                px=particle.GetMomentum().GetCarthesian()[0];
                py=particle.GetMomentum().GetCarthesian()[1];
                pz=particle.GetMomentum().GetCarthesian()[2];
                
                //cout<<"px="<<px<<" py="<<py<<" pz="<<pz<<endl;
                               
                pr=particle.GetMomentum().GetSpherical()[0];
                ptheta=particle.GetMomentum().GetSpherical()[1];
                pphi=particle.GetMomentum().GetSpherical()[2];
                
                PID=particle.GetPID();

                tree.Fill();
            }
            
        }
    }
    
    /////////////////////////////////////////////////////
    // Wall 1 - wallID=1
    
    wallID=1;
        
    flist.SetArea(64.0,PIover2,PIover2);
    flist.Print();
    flist.Recalculate();
    flist.Save("Wall1FluxMap");
    fluxmap=flist.GetNppsPhiTheta();
    
    nBinsPhi=fluxmap->GetNbinsX();
    nBinsTheta=fluxmap->GetNbinsY();
        
    for (int i=1; i<=nBinsPhi; i++)
    {
        pgen.SetPhiRange(fluxmap->GetXaxis()->GetBinLowEdge(i),fluxmap->GetXaxis()->GetBinUpEdge(i));
        
        for (int j=1; j<=nBinsTheta; j++)
        {
            pgen.SetThetaRange(PI -fluxmap->GetYaxis()->GetBinUpEdge(j), PI - fluxmap->GetYaxis()->GetBinLowEdge(j));
            
            //////////////////////////////////
            // randomize non-integer part of number of particles:
            // rounding up probability is proportional to the non-integer part
            
            double nparticles=fluxmap->GetBinContent(i,j)*SIM_TIME;
            double noninteger = nparticles - floor(nparticles);
            
            //cout<<"Nparticles="<<nparticles;
            double rndm=rng.Rndm();
            //cout<<" rndm="<<rndm;
            
            if ( rndm < noninteger )
            {
                nparticles = floor( nparticles + 1. );
                //cout<<"  rounded up: "<<nparticles<<endl;
            }
            else
            {
                nparticles = floor (nparticles);
                //cout<<"  rounded down: "<<nparticles<<endl;
            }
            
            
            for (int n=0; n<nparticles; n++)
            {
                cout<<"Wall 1: i="<<i<<" j="<<j<<" n="<<n<<"\r"<<flush;
                
                
                particle=pgen.GetRandomParticle();
                particle.SetPosition(wall1.RelativeToAbsolute(particle.GetPosition()));
                
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
    
    /////////////////////////////////////////////////////
    // Wall 2 - wallID=2
    
    wallID=2;
        
    flist.SetArea(64.0,PIover2,0.);
    flist.Print();
    flist.Recalculate();
    flist.Save("Wall2FluxMap");
    fluxmap=flist.GetNppsPhiTheta();
    
    nBinsPhi=fluxmap->GetNbinsX();
    nBinsTheta=fluxmap->GetNbinsY();
    
    for (int i=1; i<=nBinsPhi; i++)
    {
        pgen.SetPhiRange(fluxmap->GetXaxis()->GetBinLowEdge(i),fluxmap->GetXaxis()->GetBinUpEdge(i));
        
        for (int j=1; j<=nBinsTheta; j++)
        {
            pgen.SetThetaRange(PI -fluxmap->GetYaxis()->GetBinUpEdge(j), PI - fluxmap->GetYaxis()->GetBinLowEdge(j));
            
            //////////////////////////////////
            // randomize non-integer part of number of particles:
            // rounding up probability is proportional to the non-integer part
            
            double nparticles=fluxmap->GetBinContent(i,j)*SIM_TIME;
            double noninteger = nparticles - floor(nparticles);
            
            //cout<<"Nparticles="<<nparticles;
            double rndm=rng.Rndm();
            //cout<<" rndm="<<rndm;
            
            if ( rndm < noninteger )
            {
                nparticles = floor( nparticles + 1. );
                //cout<<"  rounded up: "<<nparticles<<endl;
            }
            else
            {
                nparticles = floor (nparticles);
                //cout<<"  rounded down: "<<nparticles<<endl;
            }
            
            
            for (int n=0; n<nparticles; n++)
            {
                cout<<"Wall 2: i="<<i<<" j="<<j<<" n="<<n<<"\r"<<flush;
                
                particle=pgen.GetRandomParticle();
                particle.SetPosition(wall2.RelativeToAbsolute(particle.GetPosition()));
                
                posX=particle.GetPosition()[0];
                posY=particle.GetPosition()[1];
                posZ=particle.GetPosition()[2];
                
                px=particle.GetMomentum().GetCarthesian()[0];
                py=particle.GetMomentum().GetCarthesian()[1];
                pz=particle.GetMomentum().GetCarthesian()[2];
                
                pr=particle.GetMomentum().GetSpherical()[0];
                ptheta=particle.GetMomentum().GetSpherical()[1];
                pphi=particle.GetMomentum().GetSpherical()[2];
                
                //PID=particle.GetPID();
                
                tree.Fill();
            }
            
        }
    }
    
    /////////////////////////////////////////////////////
    // Wall 3 - wallID=3
    
    wallID=3;
        
    flist.SetArea(64.0,PIover2,-PIover2);
    flist.Print();
    flist.Recalculate();
    flist.Save("Wall3FluxMap");
    fluxmap=flist.GetNppsPhiTheta();
    
    nBinsPhi=fluxmap->GetNbinsX();
    nBinsTheta=fluxmap->GetNbinsY();
    
    for (int i=1; i<=nBinsPhi; i++)
    {
        pgen.SetPhiRange(fluxmap->GetXaxis()->GetBinLowEdge(i),fluxmap->GetXaxis()->GetBinUpEdge(i));
        
        for (int j=1; j<=nBinsTheta; j++)
        {
            pgen.SetThetaRange(PI -fluxmap->GetYaxis()->GetBinUpEdge(j), PI - fluxmap->GetYaxis()->GetBinLowEdge(j));
            
            //////////////////////////////////
            // randomize non-integer part of number of particles:
            // rounding up probability is proportional to the non-integer part
            
            double nparticles=fluxmap->GetBinContent(i,j)*SIM_TIME;
            double noninteger = nparticles - floor(nparticles);
            
            //cout<<"Nparticles="<<nparticles;
            double rndm=rng.Rndm();
            //cout<<" rndm="<<rndm;
            
            if ( rndm < noninteger )
            {
                nparticles = floor( nparticles + 1. );
                //cout<<"  rounded up: "<<nparticles<<endl;
            }
            else
            {
                nparticles = floor (nparticles);
                //cout<<"  rounded down: "<<nparticles<<endl;
            }
            
            
            for (int n=0; n<nparticles; n++)
            {
                cout<<"Wall 3: i="<<i<<" j="<<j<<" n="<<n<<"\r"<<flush;
                
                particle=pgen.GetRandomParticle();
                particle.SetPosition(wall3.RelativeToAbsolute(particle.GetPosition()));
                
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
    
    /////////////////////////////////////////////////////
    // Wall 4 - wallID=4
    
    wallID=4;
    
    
    flist.SetArea(64.0,PIover2,PI);
    flist.Print();
    flist.Recalculate();
    flist.Save("Wall4FluxMap");
    fluxmap=flist.GetNppsPhiTheta();
    
    nBinsPhi=fluxmap->GetNbinsX();
    nBinsTheta=fluxmap->GetNbinsY();
    
    for (int i=1; i<=nBinsPhi; i++)
    {
        pgen.SetPhiRange(fluxmap->GetXaxis()->GetBinLowEdge(i),fluxmap->GetXaxis()->GetBinUpEdge(i));
        
        for (int j=1; j<=nBinsTheta; j++)
        {
            pgen.SetThetaRange(PI -fluxmap->GetYaxis()->GetBinUpEdge(j), PI - fluxmap->GetYaxis()->GetBinLowEdge(j));
            
            //////////////////////////////////
            // randomize non-integer part of number of particles:
            // rounding up probability is proportional to the non-integer part
            
            double nparticles=fluxmap->GetBinContent(i,j)*SIM_TIME;
            double noninteger = nparticles - floor(nparticles);
            
            //cout<<"Nparticles="<<nparticles;
            double rndm=rng.Rndm();
            //cout<<" rndm="<<rndm;
            
            if ( rndm < noninteger )
            {
                nparticles = floor( nparticles + 1. );
                //cout<<"  rounded up: "<<nparticles<<endl;
            }
            else
            {
                nparticles = floor (nparticles);
                //cout<<"  rounded down: "<<nparticles<<endl;
            }
            
            
            for (int n=0; n<nparticles; n++)
            {
                cout<<"Wall 4: i="<<i<<" j="<<j<<" n="<<n<<"\r"<<flush;
                
                particle=pgen.GetRandomParticle();
                particle.SetPosition(wall4.RelativeToAbsolute(particle.GetPosition()));
                
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
    
    tree.Print();
    outFile.Write();
    outFile.Close();
    
    return 0;
}
