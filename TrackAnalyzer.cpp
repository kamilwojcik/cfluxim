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
    //cout<<"x = "<<x<<"   y = "<<y<<"   z = "<<z<<endl;
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
    
    
    float mcord[28][3], tpc[2][3];
    bool hitmcord[28], hittpc[2];
 
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

    outtree.Branch("m0x",&mcord[0][0]);
    outtree.Branch("m0y",&mcord[0][1]);
    outtree.Branch("m0z",&mcord[0][2]);
    
    outtree.Branch("m1x",&mcord[1][0]);
    outtree.Branch("m1y",&mcord[1][1]);
    outtree.Branch("m1z",&mcord[1][2]);
    
    outtree.Branch("m2x",&mcord[2][0]);
    outtree.Branch("m2y",&mcord[2][1]);
    outtree.Branch("m2z",&mcord[2][2]);
    
    outtree.Branch("m3x",&mcord[3][0]);
    outtree.Branch("m3y",&mcord[3][1]);
    outtree.Branch("m3z",&mcord[3][2]);
    
    outtree.Branch("m4x",&mcord[4][0]);
    outtree.Branch("m4y",&mcord[4][1]);
    outtree.Branch("m4z",&mcord[4][2]);
    
    outtree.Branch("m5x",&mcord[5][0]);
    outtree.Branch("m5y",&mcord[5][1]);
    outtree.Branch("m5z",&mcord[5][2]);
    
    outtree.Branch("m6x",&mcord[6][0]);
    outtree.Branch("m6y",&mcord[6][1]);
    outtree.Branch("m6z",&mcord[6][2]);
    
    outtree.Branch("m7x",&mcord[7][0]);
    outtree.Branch("m7y",&mcord[7][1]);
    outtree.Branch("m7z",&mcord[7][2]);
    
    outtree.Branch("m8x",&mcord[8][0]);
    outtree.Branch("m8y",&mcord[8][1]);
    outtree.Branch("m8z",&mcord[8][2]);
    
    outtree.Branch("m9x",&mcord[9][0]);
    outtree.Branch("m9y",&mcord[9][1]);
    outtree.Branch("m9z",&mcord[9][2]);
    
    outtree.Branch("m10x",&mcord[10][0]);
    outtree.Branch("m10y",&mcord[10][1]);
    outtree.Branch("m10z",&mcord[10][2]);
    
    outtree.Branch("m11x",&mcord[11][0]);
    outtree.Branch("m11y",&mcord[11][1]);
    outtree.Branch("m11z",&mcord[11][2]);
    
    outtree.Branch("m12x",&mcord[12][0]);
    outtree.Branch("m12y",&mcord[12][1]);
    outtree.Branch("m12z",&mcord[12][2]);
    
    outtree.Branch("m13x",&mcord[13][0]);
    outtree.Branch("m13y",&mcord[13][1]);
    outtree.Branch("m13z",&mcord[13][2]);
    
    outtree.Branch("m14x",&mcord[14][0]);
    outtree.Branch("m14y",&mcord[14][1]);
    outtree.Branch("m14z",&mcord[14][2]);
    
    outtree.Branch("m15x",&mcord[15][0]);
    outtree.Branch("m15y",&mcord[15][1]);
    outtree.Branch("m15z",&mcord[15][2]);
    
    outtree.Branch("m16x",&mcord[16][0]);
    outtree.Branch("m16y",&mcord[16][1]);
    outtree.Branch("m16z",&mcord[16][2]);
    
    outtree.Branch("m17x",&mcord[17][0]);
    outtree.Branch("m17y",&mcord[17][1]);
    outtree.Branch("m17z",&mcord[17][2]);
    
    outtree.Branch("m18x",&mcord[18][0]);
    outtree.Branch("m18y",&mcord[18][1]);
    outtree.Branch("m18z",&mcord[18][2]);
    
    outtree.Branch("m19x",&mcord[19][0]);
    outtree.Branch("m19y",&mcord[19][1]);
    outtree.Branch("m19z",&mcord[19][2]);
    
    outtree.Branch("m20x",&mcord[20][0]);
    outtree.Branch("m20y",&mcord[20][1]);
    outtree.Branch("m20z",&mcord[20][2]);
    
    outtree.Branch("m21x",&mcord[21][0]);
    outtree.Branch("m21y",&mcord[21][1]);
    outtree.Branch("m21z",&mcord[21][2]);
    
    outtree.Branch("m22x",&mcord[22][0]);
    outtree.Branch("m22y",&mcord[22][1]);
    outtree.Branch("m22z",&mcord[22][2]);
    
    outtree.Branch("m23x",&mcord[23][0]);
    outtree.Branch("m23y",&mcord[23][1]);
    outtree.Branch("m23z",&mcord[23][2]);
    
    outtree.Branch("m24x",&mcord[24][0]);
    outtree.Branch("m24y",&mcord[24][1]);
    outtree.Branch("m24z",&mcord[24][2]);
    
    outtree.Branch("m25x",&mcord[25][0]);
    outtree.Branch("m25y",&mcord[25][1]);
    outtree.Branch("m25z",&mcord[25][2]);
    
    outtree.Branch("m26x",&mcord[26][0]);
    outtree.Branch("m26y",&mcord[26][1]);
    outtree.Branch("m26z",&mcord[26][2]);
    
    outtree.Branch("m27x",&mcord[27][0]);
    outtree.Branch("m27y",&mcord[27][1]);
    outtree.Branch("m27z",&mcord[27][2]);
    
    outtree.Branch("t0",&hittpc[0]);
    outtree.Branch("t1",&hittpc[1]);
    
    outtree.Branch("m0",&hitmcord[0]);
    outtree.Branch("m1",&hitmcord[1]);
    outtree.Branch("m2",&hitmcord[2]);
    outtree.Branch("m3",&hitmcord[3]);
    outtree.Branch("m4",&hitmcord[4]);
    outtree.Branch("m5",&hitmcord[5]);
    outtree.Branch("m6",&hitmcord[6]);
    outtree.Branch("m7",&hitmcord[7]);
    outtree.Branch("m8",&hitmcord[8]);
    outtree.Branch("m9",&hitmcord[9]);
    outtree.Branch("m10",&hitmcord[10]);
    outtree.Branch("m11",&hitmcord[11]);
    outtree.Branch("m12",&hitmcord[12]);
    outtree.Branch("m13",&hitmcord[13]);
    outtree.Branch("m14",&hitmcord[14]);
    outtree.Branch("m15",&hitmcord[15]);
    outtree.Branch("m16",&hitmcord[16]);
    outtree.Branch("m17",&hitmcord[17]);
    outtree.Branch("m18",&hitmcord[18]);
    outtree.Branch("m19",&hitmcord[19]);
    outtree.Branch("m20",&hitmcord[20]);
    outtree.Branch("m21",&hitmcord[21]);
    outtree.Branch("m22",&hitmcord[22]);
    outtree.Branch("m23",&hitmcord[23]);
    outtree.Branch("m24",&hitmcord[24]);
    outtree.Branch("m25",&hitmcord[25]);
    outtree.Branch("m26",&hitmcord[26]);
    outtree.Branch("m27",&hitmcord[27]);
    
    TH1D FluxTheta("FluxTheta","FluxTheta", 8,0,90);
    
    //outtree.Print();
    
    /////////////////////
    // tpc
    //
    // asis: x: 3.4 m
    // r= (2.8 - 0.6) / 2 = 1.1 m
    //
    Coords s1(-1.7,0,4);
    Coords s2(1.7,0,4);
    double r=1.1;
    
    cout<<"TPC cylinder: "<<endl;
    Cylinder dettpc(s1,s2,r);
    dettpc.Print();
    cout<<endl;
    
    /////////////////////
    // mcord modules
    //
    // 28 modules around the magnet
    // w = 4,784 m (2x 2.392)
    // l = 0.675 m (2x 0.3375)
    // radius of magnet = z = 6623/2 = 3311.5 
    
    Rectangle module[28];
    
    double x = 2.392;
    double y = 0.3375;
    double z = 3.3115;
    Coords v1(-x,y,z);
    Coords v4(-x,-y,z);
    Coords vec_x(2.*x, 0, 0);
    Coords z_elevation(0,0,4); //detector axis is elevated 4m over z=0 level
    Coords v1prim, v2prim, v3prim, v4prim;
    
    cout<<"Mcord modules: "<<endl;
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

        module[i].SetRectangle(v1prim, v2prim, v3prim, v4prim);
        cout<<"\nMcord "<<i<<endl;
        module[i].Print();
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
        if (n%300!=0) continue; //- smaller sample for tests and drawings
        
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
        
        for (int i=0; i<28; i++) hitmcord[i]=false;
        
        
        double n_mcord_hits=0;
        for (int i=0; i<28; i++)
        {
            if (n_mcord_hits >= 2 ) break;
            
            
            if (module[i].HitsRectangle(particle))
            {   
                if( rng.Rndm() > 0.9 ) continue; //efficiency of the module is about 90%
                n_mcord_hits++;
                hitmcord[i]=true;
                hitpos=module[i].GetHitPosition();
                
                mcord[i][0]=0;
                mcord[i][1]=0;
                mcord[i][2]=0;
                mcord[i][0]=hitpos[0];
                mcord[i][1]=hitpos[1];
                mcord[i][2]=hitpos[2];
                
                if (mcord[i][2] < 0 ) cout<<"Warning z<0"<<endl;
                line=to_string(hitpos[0]) + " " + to_string(hitpos[1]) + " " + to_string(hitpos[2]) + "\n";
                textfile<<line;
            }
            
        }
        
        
        for (int f=0; f<8; f++)
        {
            if (hitmcord[f] && hitmcord[f+14] && wallID==0) FluxTheta.AddBinContent(f,1);
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
