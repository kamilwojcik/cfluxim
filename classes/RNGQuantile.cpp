#include <iostream>
#include <string>
#include "RNGQuantile.h"
#include <ctime>

using namespace std;


/////////////////////////////////////
//setup functions

void RNGQuantile::SetDescription(string descr)
{
    description=descr;

    return;
}


void RNGQuantile::SetMomentumQuantileHisto(TH1D * momQuantile)
{
    quantileHisto = momQuantile;
    distributionHisto=new TH1D("distributionHisto","distributionHisto",quantileHisto->GetNbinsX(), quantileHisto->GetXaxis()->GetXmin(),quantileHisto->GetXaxis()->GetXmax());
    ready = true;
    
    return;
}


void RNGQuantile::SaveDistribution(std::string filename)
{
    if (filename=="") filename= description+"_distribution.root";
    if (ready) distributionHisto->SaveAs(filename.data());
    else cout<<"RNGquantile not initialized! No distribution to save."<<endl;
    
    return;
}


void RNGQuantile::SaveDistributionPng(std::string filename)
{
    if (filename=="") filename = description+"_distribution.png";
    if (ready)
    {
        cnv = new TCanvas();
        cnv->cd();
        distributionHisto->Draw();
        cnv->SaveAs(filename.data());
        delete cnv;
    }
    else cout<<"RNGQuantile not initialized! No distribution to save."<<endl;
    
    return;
}


void RNGQuantile::ResetDistribution()
{
    distributionHisto->Reset();
    
    return;
}

//////////////////////////////////////
//get

double RNGQuantile::GetRandom()
{
    double ans=0;
    //if (ready) ans=quantileHisto->GetBinCenter(quantileHisto->FindLastBinAbove(rng->Rndm()));
    //else cout<<"RNGQuantile not initialized!"<<endl;
    double rand=rng->Rndm()*scale;
    if (rand < fitfun->Eval(500)) ans=500;
    else ans=fitfun->GetX(rand);
    distributionHisto->Fill(ans);
    
    return ans;
}


//////////////////////////////////////
//Print

void RNGQuantile::Print()
{
    cout<<"RNGQuantule description: "<<description<<endl;
    if (ready)
    {
        cout<<"Status: initialized"<<endl;
        //cout<<"Nbins: "<<(hQuantile->GetNbinsX())<<" Xmin: "<<(hQuantile->GetXaxis()->GetXmin())<<" Xmax: "<<(hQuantile->GetXaxis()->GetXmax())<<endl;
        //cout<<"Entries"<<(hDistribution->GetEntries())<<endl;
    }
    else cout<<"Status: not initialized."<<endl;
    
}

//////////////////////////////////////
//constructors

RNGQuantile::RNGQuantile()
{
    rng = new TRandom3(time(NULL));
    description="Blank_RNGQuantile";
    ready = false;
    
    fitfun = new TF1("fitfun", "0.102458*pow(1.+x/(2.01358*2.),-2.)", 0, 500);
    scale=fitfun->Eval(0);
}


RNGQuantile::RNGQuantile(TH1D * momQuantile, string descr)
{
    RNGQuantile();
    SetDescription(descr);
    SetMomentumQuantileHisto(momQuantile);
}


//////////////////////////////////////
//descructor

RNGQuantile::~RNGQuantile()
{
    if (ready)
    {
        SaveDistributionPng();
        SaveDistribution();
        delete quantileHisto;
        delete distributionHisto;
    }
    delete rng;
}
