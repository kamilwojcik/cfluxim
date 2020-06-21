#include <iostream>
#include <string>
#include "TH1D.h"
#include "TFile.h"

#include "../RNGQuantile.h"

using namespace std;

int main (int argc, char *argv[])
{
    RNGQuantile qrng;
    qrng.Print();
    qrng.SetDescription("aaa");
    qrng.Print();
    
    TFile * file= TFile::Open("hQuantile.root");
    cout<<"OpenQuantileFile: "<<"hQuantile.root"<<endl;
    file->Print();
    
    TH1D * quantileHisto= (TH1D*)file->Get("hMuMom");
    
    qrng.SetMomentumQuantileHisto(quantileHisto);
    
    for (int i=0; i<500000; i++) qrng.GetRandom();
    qrng.SaveDistributionPng();
    qrng.SaveDistribution();
    
    
    return 0;
}
