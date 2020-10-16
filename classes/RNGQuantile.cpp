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


void RNGQuantile::SetMomentumQuantileFunction(TF1 * momQuantile)
{
    momentumQuantileFunction = momQuantile;
    scale = momentumQuantileFunction->Eval(0);
    ymin = momentumQuantileFunction->Eval(1000);
    
    distributionHisto=new TH1D("distributionHisto","distributionHisto",1000, 0, 1000);
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
    double ans = 0;
    double rand = rng->Rndm()*scale;
    if (rand > ymin) ans = momentumQuantileFunction->GetX(rand);
    else ans = 1000;
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
        cout<<"Status: initialized\nQuantile function:\n"<<endl;
        momentumQuantileFunction->Print();
        cout<<"Distribution histo entries"<<(distributionHisto->GetEntries())<<endl;
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
}


RNGQuantile::RNGQuantile(TF1 * momQuantile, string descr)
{
    RNGQuantile();
    SetDescription(descr);
    SetMomentumQuantileFunction(momQuantile);
}


//////////////////////////////////////
//descructor

RNGQuantile::~RNGQuantile()
{
    if (ready)
    {
        SaveDistributionPng();
        SaveDistribution();
        delete momentumQuantileFunction;
        delete distributionHisto;
    }
    delete rng;
}
