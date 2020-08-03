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
    
    string brnamexyz, brname;
    for (int moduleNumber=0; moduleNumber<28; moduleNumber++)
    {
        brname="s";
        brname+=to_string(moduleNumber);
        outtree.Branch(brname.data(), &hitsquare[moduleNumber]);
        
        brnamexyz=brname+"x";
        outtree.Branch(brnamexyz.data(),&square[moduleNumber][0]);
        brnamexyz=brname+"y";
        outtree.Branch(brnamexyz.data(),&square[moduleNumber][1]);
        brnamexyz=brname+"z";
        outtree.Branch(brnamexyz.data(),&square[moduleNumber][2]);
    }
    
    outtree.Branch("fx",&floor[0]);
    outtree.Branch("fy",&floor[1]);
    outtree.Branch("fz",&floor[2]);
    
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
