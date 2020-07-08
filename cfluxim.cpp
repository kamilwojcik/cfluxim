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


/////////////////////////////////////////////
// CUBE particle generator
//
// Cube size: 8x8x8 m
//
// UP:
//                      Y  ^ 
//                         | wall1
//  p1up(-4,4,8) __________|__________ p2up(4,4,8)
//              |          |          |
//              |          |          |
//        wall4 |  ceiling |          | wall2
//              |          |Z         |
//           ---|----------+----------|--->
//              |          |          |   X
//              |          |          |
//              |          |          |
//              |__________|__________|
// p4up(-4,-4,8)           | wall3     p3up(4,-4,8)
//                         |
//
//
// SIDE:
//                      Z  ^      
//                         | ceiling
//  p3up(4,-4,8) __________|__________ p2up(4,4,8)
//              |          |          |
//              |          |          |
//              |          |          |
//        wall3 |    wall2 |          | wall1
//              |          |          |
//              |          |          |
//              |          |          |
//          ____|__________|__________|_____> Y
//  p3down(4,-4,0)         X           p2down(4,4,0)
//
//

#define PItimes2 6.2831853
#define PIover2 1.5707963
#define PI 3.1415927

#define SIM_TIME 1000 //seconds

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
    
    Rectangle ceiling(p1up, p2up, p4up, p4up);
    Rectangle wall1(p2up, p1up, p1down, p2up);
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
    // Two MCORD modules, a detector bewteen them
    //
    //
    // SIDE:
    //                      Z  ^      
    //                         | ceiling
    //  p4up(2,-2,4) __________|__________ p1up(2,2,4)
    //              |   mcord1 |          |
    //              |   -------+-------   |
    //              |          |          |
    //        wall4 |          |          | wall2
    //              |   -------+-------   |
    //              |   mcord2 |          |
    //              |          |          |
    //          ____|__________|__________|_____> Y
    //  p4down(2,-2,0)         X           p1down(2,2,0)
    //
    //
    
    Coords m2up(-0.3375,0.872,6);     //mcord x: 0.675 m, y: 1.744 m
    Coords m4up(0.3357,-0.872,6);     //mcord1 z: 3 m
    
    Coords m2down(-0.3375,0.872,0);   //mcord2 z: 2 m
    Coords m4down(0.3375,-0.872,0);
    
    //Coords m2up(-0.5,0.5,0.2);     //mcord x: 0.675 m, y: 1.744 m
    //Coords m4up(0.5,-0.5,0.2);     //mcord1 z: 3 m
    
    //Coords m2down(-1,1,0);   //mcord2 z: 2 m
    //Coords m4down(1,-1,0);
    /*
    Rectangle mcord1(m2up, m4up);
    Rectangle mcord2(m2down, m4down);
    
    cout<<"\nMcord1:"<<endl;
    mcord1.Print();
    cout<<"\nMcord2:"<<endl;
    mcord2.Print();
    */
    Cylinder tpc(-1.5,0,6,1.5,0,6,1);
    tpc.Print();
    
    /////////////////////////////////////////////////////
    TFile outFile("cosmicCube.root", "RECREATE");
    
    /////////////////////////////////////////////////////
    // TTree setup
    
    // variables as an interface to populate the tree
    int PID, wallID;
    double posX, posY, posZ;
    double px, py, pz;
    double pr, ptheta, pphi;
    double m1hitx, m1hity, m1hitz, m2hitx, m2hity, m2hitz, hitrelx, hitrely;
    double t1x,t1y,t1z,t2x,t2y,t2z;
    bool hits1, hits2,tpchit1, tpchit2;
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
    /*tree.Branch("m1hitx",&m1hitx);    
    tree.Branch("m1hity",&m1hity);    
    tree.Branch("m1hitz",&m1hitz);    
    tree.Branch("m2hitx",&m2hitx);    
    tree.Branch("m2hity",&m2hity);    
    tree.Branch("m2hitz",&m2hitz);
    tree.Branch("hits1",&hits1);    
    tree.Branch("hits2",&hits2);  
    */
    tree.Branch("t1x",&t1x);
    tree.Branch("t1y",&t1y);
    tree.Branch("t1z",&t1z);
    tree.Branch("t2x",&t2x);
    tree.Branch("t2y",&t2y);
    tree.Branch("t2z",&t2z);
    tree.Branch("tpchit1",&tpchit1);
    tree.Branch("tpchit2",&tpchit2);
    
    
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
    
    
    double m1, m2, m12;
    m1=m2=m12=0;

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
                
                tpchit1=false;
                tpchit2=false;
                
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

                if (tpc.HitsCylinder(particle))
                {
                    tpchit1=true;
                    vector<Coords> hitpos=tpc.GetHitPositions();
                    Coords hit=hitpos[0];
                    t1x=hit[0];
                    t1y=hit[1];
                    t1z=hit[2];
                    if (hitpos.size()>1)
                    {
                        tpchit2=true;
                        hit=hitpos[1];
                        t2x=hit[0];
                        t2y=hit[1];
                        t2z=hit[2];
                    }
                }
                /*
                if (mcord1.HitsRectangle(particle))
                {
                    hits1=true;
                    Coords hitpos1=mcord1.GetHitPosition();
                    m1hitx=hitpos1[0];
                    m1hity=hitpos1[1];
                    m1hitz=hitpos1[2];
                    m1++;
                }
                
                if (mcord2.HitsRectangle(particle))
                {
                    hits2=true;
                    Coords hitpos2=mcord2.GetHitPosition();
                    m2hitx=hitpos2[0];
                    m2hity=hitpos2[1];
                    m2hitz=hitpos2[2];
                    m2++;
                }
                if (hits1 && hits2) m12++;
                */
                tree.Fill();
            }
            
        }
    }
    /*
    /////////////////////////////////////////////////////
    // Wall 1 - wallID=1
    
    wallID=1;
        
    flist.SetArea(64.0,PIover2,PI);
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
                
                hits1=false;
                hits2=false;
                
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
                
                if (mcord1.HitsRectangle(particle))
                {
                    hits1=true;
                    Coords hitpos1=mcord1.GetHitPosition();
                    m1hitx=hitpos1[0];
                    m1hity=hitpos1[1];
                    m1hitz=hitpos1[2];
                    m1++;
                }
                
                if (mcord2.HitsRectangle(particle))
                {
                    hits2=true;
                    Coords hitpos2=mcord2.GetHitPosition();
                    m2hitx=hitpos2[0];
                    m2hity=hitpos2[1];
                    m2hitz=hitpos2[2];
                    m2++;
                }
                if (hits1 && hits2) m12++;
                
                tree.Fill();
            }
            
        }
    }
    
    /////////////////////////////////////////////////////
    // Wall 2 - wallID=2
    
    wallID=2;
        
    flist.SetArea(64.0,PIover2,1.5*PI);
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
                
                hits1=false;
                hits2=false;
                
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
                
                PID=particle.GetPID();
                
                if (mcord1.HitsRectangle(particle))
                {
                    hits1=true;
                    Coords hitpos1=mcord1.GetHitPosition();
                    m1hitx=hitpos1[0];
                    m1hity=hitpos1[1];
                    m1hitz=hitpos1[2];
                    m1++;
                }
                
                if (mcord2.HitsRectangle(particle))
                {
                    hits2=true;
                    Coords hitpos2=mcord2.GetHitPosition();
                    m2hitx=hitpos2[0];
                    m2hity=hitpos2[1];
                    m2hitz=hitpos2[2];
                    m2++;
                }
                if (hits1 && hits2) m12++;
                
                tree.Fill();
            }
            
        }
    }
    
    /////////////////////////////////////////////////////
    // Wall 3 - wallID=3
    
    wallID=3;
        
    flist.SetArea(64.0,PIover2,0);
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
                
                hits1=false;
                hits2=false;

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
                
                if (mcord1.HitsRectangle(particle))
                {
                    hits1=true;
                    Coords hitpos1=mcord1.GetHitPosition();
                    m1hitx=hitpos1[0];
                    m1hity=hitpos1[1];
                    m1hitz=hitpos1[2];
                    m1++;
                }
                
                if (mcord2.HitsRectangle(particle))
                {
                    hits2=true;
                    Coords hitpos2=mcord2.GetHitPosition();
                    m2hitx=hitpos2[0];
                    m2hity=hitpos2[1];
                    m2hitz=hitpos2[2];
                    m2++;
                }
                if (hits1 && hits2) m12++;
                
                tree.Fill();
            }
            
        }
    }
    
    /////////////////////////////////////////////////////
    // Wall 4 - wallID=4
    
    wallID=4;
    
    
    flist.SetArea(64.0,PIover2,PIover2);
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
                
                hits1=false;
                hits2=false;

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
                
                if (mcord1.HitsRectangle(particle))
                {
                    hits1=true;
                    Coords hitpos1=mcord1.GetHitPosition();
                    m1hitx=hitpos1[0];
                    m1hity=hitpos1[1];
                    m1hitz=hitpos1[2];
                    m1++;
                }
                
                if (mcord2.HitsRectangle(particle))
                {
                    hits2=true;
                    Coords hitpos2=mcord2.GetHitPosition();
                    m2hitx=hitpos2[0];
                    m2hity=hitpos2[1];
                    m2hitz=hitpos2[2];
                    m2++;
                }
                if (hits1 && hits2) m12++;
                
                tree.Fill();
            }
            
        }
    }
    */
    tree.Print();
    outFile.Write();
    outFile.Close();
    
    //cout<<"M1 = "<<m1<<"  m2 = "<<m2<<"  m12 = "<<m12<<endl;
    
    return 0;
}
