#include "classes/Coords.h"
#include "classes/Momentum.h"
#include "classes/Particle.h"
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
#include "TCanvas.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>


#define PItimes2 6.2831853
#define PIover2 1.5707963
#define PI 3.1415927

Coords rotx (Coords point, double angle)
{
    double x = point[0];
    double y = - point[1]*cos(angle) + point[2]*sin(angle);
    double z = point[1]*sin(angle) + point[2]*cos(angle);
    Coords ans(x,y,z);
    
    return ans;
}

int main (int argc, char * argv[])
{    
    
    TFile infile("cosmicCube.root");
    TTree* intree = (TTree*) infile.Get("CosmicCube");
    
    //intree->Print();
    
    int PID, wallID;
    float posX, posY, posZ;
    float px, py, pz;
    float pr, ptheta, pphi;
    
    Particle particle;
    Coords hitpos;
    vector<Coords> hitvec;
    
    intree->SetBranchAddress("PID", &PID);
    intree->SetBranchAddress("wallID", &wallID);
    intree->SetBranchAddress("posX", &posX);
    intree->SetBranchAddress("posY", &posY);
    intree->SetBranchAddress("posZ", &posZ);
    intree->SetBranchAddress("px", &px);
    intree->SetBranchAddress("py", &py);
    intree->SetBranchAddress("pz", &pz);
    intree->SetBranchAddress("pr", &pr);
    intree->SetBranchAddress("ptheta", &ptheta);
    intree->SetBranchAddress("pphi", &pphi);
    
    
    float module[28][3], tpc[2][3];
    bool hitmodule[28], hittpc[2];
 
    TFile outFile("detectors.root", "RECREATE");
    TTree outtree("detectors", "detectors");
    outtree.Branch("PID",&PID);
    outtree.Branch("wallID",&wallID);
    outtree.Branch("posX", &posX);
    outtree.Branch("posY", &posY);
    outtree.Branch("posZ", &posZ);
    outtree.Branch("px", &px);
    outtree.Branch("py", &py);
    outtree.Branch("pz", &pz);
    outtree.Branch("pr", &pr);
    outtree.Branch("ptheta", &ptheta);
    outtree.Branch("pphi", &pphi);
    
    outtree.Branch("t0x",&tpc[0][0]);
    outtree.Branch("t0y",&tpc[0][1]);
    outtree.Branch("t0z",&tpc[0][2]);
    outtree.Branch("t1x",&tpc[1][0]);
    outtree.Branch("t1y",&tpc[1][1]);
    outtree.Branch("t1z",&tpc[1][2]);
    
    outtree.Branch("t0",&hittpc[0]);
    outtree.Branch("t1",&hittpc[1]);
    
    string brnamexyz, brname;
    for (int moduleNumber=0; moduleNumber<28; moduleNumber++)
    {
        brname="m";
        brname+=to_string(moduleNumber);
        outtree.Branch(brname.data(), &hitmodule[moduleNumber]);
        
        brnamexyz=brname+"x";
        outtree.Branch(brnamexyz.data(),&module[moduleNumber][0]);
        brnamexyz=brname+"y";
        outtree.Branch(brnamexyz.data(),&module[moduleNumber][1]);
        brnamexyz=brname+"z";
        outtree.Branch(brnamexyz.data(),&module[moduleNumber][2]);
    }
    
    
    TH1D FluxTheta("FluxTheta","FluxTheta", 8,0,90);
        
    /////////////////////
    // tpc
    //
    // asis: parallel x: 3.4 m
    // axis elevation (z) = 4 m
    // r= 1.1 m
    //
    Coords s1(-1.7,0,4);
    Coords s2(1.7,0,4);
    double r=1.1;
    
    cout<<"TPC cylinder: "<<endl;
    Cylinder dettpc(s1,s2,r);
    dettpc.Print();
    cout<<endl;
    
    /////////////////////
    // modules
    //
    // 28 modules around the TPC
    // w = 4,784 m (2x 2.392)
    // l = 0.675 m (2x 0.3375)
    // radius = 3311.5 
    
    Rectangle mod[28];
    
    double x = 2.392;
    double y = 0.3375;
    double z = 3.3115;
    Coords v1(-x,y,z);
    Coords v4(-x,-y,z);
    Coords vec_x(2.*x, 0, 0);
    Coords z_elevation(0,0,4); //detector axis is elevated 4m over z=0 level
    Coords v1prim, v2prim, v3prim, v4prim;
    
    cout<<"Modules: "<<endl;
    for (int i=0; i<28; i++)
    {
        double angle = i*PI/14.;
        //rotating vertices over x axis
        v1prim = rotx(v1, angle);
        v2prim = v1prim + vec_x;
        v4prim = rotx(v4, angle);
        v3prim = v4prim + vec_x;
        
        //elevation in z
        v1prim = v1prim + z_elevation;
        v2prim = v2prim + z_elevation;
        v3prim = v3prim + z_elevation;
        v4prim = v4prim + z_elevation;

        mod[i].SetRectangle(v1prim, v2prim, v3prim, v4prim);
        cout<<"\nModule "<<i<<endl;
        mod[i].Print();
    }
    cout<<endl;
    


//////////////////////////////////////////////////////////////////
//
// Track analysis - loop over intree
//

    TRandom3 rng(time(NULL));
    ofstream textfile("hitpositions.txt", ofstream::trunc);
    string line;
    int N = intree->GetEntries();
    for (int n=0; n<N; n++)
    {
        //if (n%300!=0) continue; //- 300x smaller sample for tests and drawings
        
        cout<<"Event: "<<n<<"\r"<<flush;
        intree->GetEvent(n);
        
        particle.Set(posX, posY, posZ, pr, ptheta, pphi, PID);
        
        hittpc[0]=false;
        hittpc[1]=false;
        
        if (dettpc.HitsCylinder(particle))
        {
                
                hitvec=dettpc.GetHitPositions();
                for (int i=0; i<hitvec.size(); i++)
                {
                    hittpc[i]=true;
                    tpc[i][0]=0;
                    tpc[i][1]=0;
                    tpc[i][2]=0;
                    tpc[i][0]=hitvec[i][0];
                    tpc[i][1]=hitvec[i][1];
                    tpc[i][2]=hitvec[i][2];
                    
                    
                    line=to_string(hitvec[i][0]) + " " + to_string(hitvec[i][1]) + " " + to_string(hitvec[i][2]) + "\n";
                    textfile<<line;
                }
                hitvec.clear();
                
        }
        
        for (int i=0; i<28; i++) hitmodule[i]=false;
        
        
        double n_module_hits=0;
        for (int i=0; i<28; i++)
        {
            if (n_module_hits >= 2 ) break;
            
            
            if (mod[i].HitsRectangle(particle))
            {   
                if( rng.Rndm() > 0.9 ) continue; //efficiency of the module is about 90%
                n_module_hits++;
                hitmodule[i]=true;
                hitpos=mod[i].GetHitPosition();
                
                module[i][0]=0;
                module[i][1]=0;
                module[i][2]=0;
                module[i][0]=hitpos[0];
                module[i][1]=hitpos[1];
                module[i][2]=hitpos[2];
                
                if (module[i][2] < 0 ) cout<<"Warning z<0"<<endl;
                line=to_string(hitpos[0]) + " " + to_string(hitpos[1]) + " " + to_string(hitpos[2]) + "\n";
                textfile<<line;
            }
            
        }
        
        
        for (int f=0; f<8; f++)
        {
            if (hitmodule[f] && hitmodule[f+14]) FluxTheta.AddBinContent(f+1,1.);
        }
        
        
        outtree.Fill();
    }
    
    TCanvas cnv;
    cnv.cd();
    FluxTheta.Draw();
    cnv.SaveAs("FluxTheta.png");
    
    cout<<"Number of analyzed events/particles: "<<N<<endl;
    outFile.Write();
    outFile.Close();
    textfile.close();
    
    return 0;
}
