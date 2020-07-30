#include "classes/Coords.h"
#include "classes/Momentum.h"
#include "classes/Particle.h"
#include "classes/ParticleGenerator.h"
#include "classes/FluxList.h"
#include "classes/Plane.h"
#include "classes/Rectangle.h"


#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"

#include <iostream>
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

    int PID, wallID;
    float posX, posY, posZ;
    float px, py, pz;
    float pr, ptheta, pphi;
    
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
    
    float square[18][3], floor[3];
    bool hitsquare[18], hitsfloor;
    
    TFile outFile("fluxCheck.root", "RECREATE");
    TTree outtree("fluxCheck", "fluxCheck");
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
    
    outtree.Branch("s0x",&square[0][0]);
    outtree.Branch("s0y",&square[0][1]);
    outtree.Branch("s0z",&square[0][2]);
    
    outtree.Branch("s1x",&square[1][0]);
    outtree.Branch("s1y",&square[1][1]);
    outtree.Branch("s1z",&square[1][2]);
    
    outtree.Branch("s2x",&square[2][0]);
    outtree.Branch("s2y",&square[2][1]);
    outtree.Branch("s2z",&square[2][2]);
    
    outtree.Branch("s3x",&square[3][0]);
    outtree.Branch("s3y",&square[3][1]);
    outtree.Branch("s3z",&square[3][2]);
    
    outtree.Branch("s4x",&square[4][0]);
    outtree.Branch("s4y",&square[4][1]);
    outtree.Branch("s4z",&square[4][2]);
    
    outtree.Branch("s5x",&square[5][0]);
    outtree.Branch("s5y",&square[5][1]);
    outtree.Branch("s5z",&square[5][2]);
    
    outtree.Branch("s6x",&square[6][0]);
    outtree.Branch("s6y",&square[6][1]);
    outtree.Branch("s6z",&square[6][2]);
    
    outtree.Branch("s7x",&square[7][0]);
    outtree.Branch("s7y",&square[7][1]);
    outtree.Branch("s7z",&square[7][2]);
    
    outtree.Branch("s8x",&square[8][0]);
    outtree.Branch("s8y",&square[8][1]);
    outtree.Branch("s8z",&square[8][2]);
    
    outtree.Branch("s9x",&square[9][0]);
    outtree.Branch("s9y",&square[9][1]);
    outtree.Branch("s9z",&square[9][2]);
    
    outtree.Branch("s10x",&square[10][0]);
    outtree.Branch("s10y",&square[10][1]);
    outtree.Branch("s10z",&square[10][2]);
    
    outtree.Branch("s11x",&square[11][0]);
    outtree.Branch("s11y",&square[11][1]);
    outtree.Branch("s11z",&square[11][2]);
    
    outtree.Branch("s12x",&square[12][0]);
    outtree.Branch("s12y",&square[12][1]);
    outtree.Branch("s12z",&square[12][2]);
    
    outtree.Branch("s13x",&square[13][0]);
    outtree.Branch("s13y",&square[13][1]);
    outtree.Branch("s13z",&square[13][2]);
    
    outtree.Branch("s14x",&square[14][0]);
    outtree.Branch("s14y",&square[14][1]);
    outtree.Branch("s14z",&square[14][2]);
    
    outtree.Branch("s15x",&square[15][0]);
    outtree.Branch("s15y",&square[15][1]);
    outtree.Branch("s15z",&square[15][2]);
    
    outtree.Branch("s16x",&square[16][0]);
    outtree.Branch("s16y",&square[16][1]);
    outtree.Branch("s16z",&square[16][2]);
    
    outtree.Branch("s17x",&square[17][0]);
    outtree.Branch("s17y",&square[17][1]);
    outtree.Branch("s17z",&square[17][2]);
    
    outtree.Branch("fx",&floor[0]);
    outtree.Branch("fy",&floor[1]);
    outtree.Branch("fz",&floor[2]);
    
    outtree.Branch("s0",&hitsquare[0]);
    outtree.Branch("s1",&hitsquare[1]);
    outtree.Branch("s2",&hitsquare[2]);
    outtree.Branch("s3",&hitsquare[3]);
    outtree.Branch("s4",&hitsquare[4]);
    outtree.Branch("s5",&hitsquare[5]);
    outtree.Branch("s6",&hitsquare[6]);
    outtree.Branch("s7",&hitsquare[7]);
    outtree.Branch("s8",&hitsquare[8]);
    outtree.Branch("s9",&hitsquare[9]);
    outtree.Branch("s10",&hitsquare[10]);
    outtree.Branch("s11",&hitsquare[11]);
    outtree.Branch("s12",&hitsquare[12]);
    outtree.Branch("s13",&hitsquare[13]);
    outtree.Branch("s14",&hitsquare[14]);
    outtree.Branch("s15",&hitsquare[15]);
    outtree.Branch("s16",&hitsquare[16]);
    outtree.Branch("s17",&hitsquare[17]);
    
    outtree.Branch("f",&hitsfloor);
    
    Particle particle;

    TH1D FluxAll("FluxAll","FluxAll",18,0,PIover2);
    TH1D FluxAllNormalized("FluxAllNormalized","FluxAllNormalized",18,0,PIover2);
    TH1D FluxMeasured("FluxMeasured","FluxMeasured",18,0,PIover2);
    TH1D FluxFloor("FluxFloor","FluxFloor",18,0,PIover2);
    TH1D FluxFloorNormalized("FluxFloorNormalized","FluxFloorNormalized",18,0,PIover2);
    TH1D FluxNormalized("FluxNormalized","FluxNormalized",18,0,PIover2);
    TH1D soAngle("soAngle","Solid angle",18,0,PIover2);
    TH2D ceilingMap("ceilingMap","ceilingMap",50,0,PI,50, 0, PIover2);
    TH2D wall1Map("wall1Map","wall1Map",50,PI,PItimes2,50, 0, PIover2);
    
    TCanvas cnv;
    cnv.cd();

    Rectangle detArea[18];
    
    double a = 2.;
    Coords v1(-a,a,0);
    Coords v4(-a,-a,0);
    Coords vec_x(2.*a, 0, 0);
    Coords z_elevation(0,0,4); //detector axis is elevated 4m over z=0 level
    Coords v1prim, v2prim, v3prim, v4prim;

    Coords fp1(-4,4,0);
    Coords fp2(4,4,0);
    Coords fp3(4,-4,0);
    Coords fp4(-4,-4,0);
    
    Rectangle detFloor(fp1,fp2,fp3,fp4);
    detFloor.Print();
    
    cout<<"probe squares: "<<endl;
    for (int i=0; i<18; i++)
    {
        double angle = -i*PIover2/18.;
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

        detArea[i].SetRectangle(v1prim, v2prim, v3prim, v4prim);
        cout<<"\nsquare "<<i<<endl;
        detArea[i].Print();
    }
    cout<<endl;

    
//////////////////////////////////////////////////////////////////
//
// Flux analysis - loop over intree
//
    double dTheta=PI/36.; //5 deg //0.0872667
    int N = intree->GetEntries();
    
    for (int n=0; n<N; n++)
    {
        if (n%40!=0) continue; //- smaller sample for tests and drawings
        
        cout<<"Event: "<<n<<"\r"<<flush;
        intree->GetEvent(n);
        
        particle.Set(posX, posY, posZ, pr, ptheta, pphi, PID);
        
        double thetaPrim=PI-ptheta;
        if (wallID==0) FluxAll.Fill(thetaPrim);
        hitsfloor=false;

        if (wallID==0) ceilingMap.Fill(pphi, thetaPrim);
        if (wallID==1) wall1Map.Fill(pphi, thetaPrim);
        
        for (int i=0; i<18; i++)
        {
            if (thetaPrim>=i*dTheta-dTheta/2. && thetaPrim<i*dTheta+dTheta/2.)
            {
                hitsquare[i]=false;
                
                if (detFloor.HitsRectangle(particle))
                {
                    hitsfloor=true;
                    Coords hitpos=detFloor.GetHitPosition();
                    floor[0]=hitpos[0];
                    floor[1]=hitpos[1];
                    floor[2]=hitpos[2];
                    FluxFloor.Fill(thetaPrim);
                }
                
                
                if (pphi<3.*PI/4. && pphi>PI/4. && detArea[i].HitsRectangle(particle))
                {
                    hitsquare[i]=true;
                    Coords hitpos=detArea[i].GetHitPosition();
                    square[i][0]=hitpos[0];
                    square[i][1]=hitpos[1];
                    square[i][2]=hitpos[2];
                    FluxMeasured.Fill(thetaPrim);
                }
            }
        }
        outtree.Fill();
    }
    
    double darea=16;
    double farea=64;
    double nSeconds=3600;
    
    for (int i=0; i<18; i++)
    {
        double sangle=SolidAngle(i*dTheta, (i+1)*dTheta, PIover2);
        soAngle.SetBinContent(i,1./sangle);
        FluxAllNormalized.SetBinContent(i+1, FluxAll.GetBinContent(i+1)/(sangle));
        FluxNormalized.SetBinContent(i+1, FluxMeasured.GetBinContent(i+1)/(sangle*darea*nSeconds));
        FluxFloorNormalized.SetBinContent(i+1, FluxFloor.GetBinContent(i+1)/(farea*nSeconds*cos(i*dTheta)*sangle*4.));
    }
    FluxAll.Draw();
    cnv.SaveAs("FluxAll.png");
    FluxAllNormalized.Draw();
    cnv.SaveAs("FluxAllNormalized.png");
    FluxMeasured.Draw();
    cnv.SaveAs("FluxMeasured.png");
    FluxNormalized.Draw();
    cnv.SaveAs("FluxNormalized.png");
    FluxFloor.Draw();
    cnv.SaveAs("FluxFloor.png");
    FluxFloorNormalized.Draw();
    cout<<"Integral: "<<FluxFloorNormalized.Integral()<<endl;
    cnv.SaveAs("FluxFloorNormalized.png");
    soAngle.Draw();
    cnv.SaveAs("soAngle.png");
    wall1Map.Draw("Colz");
    cnv.SaveAs("wall1Map.png");
    ceilingMap.Draw("Colz");
    cnv.SaveAs("ceilingMap.png");
    
    
    outFile.Write();
    outFile.Close();
    
    return 0;
}
